package info.kgeorgiy.ja.sofrygin.crawler;

import info.kgeorgiy.java.advanced.crawler.*;

import java.io.IOException;
import java.net.MalformedURLException;
import java.nio.file.Path;
import java.util.*;
import java.util.concurrent.*;

import static java.util.concurrent.Executors.newFixedThreadPool;

public class WebCrawler implements Crawler {
    private final Downloader downloader;
    private final ExecutorService downloaders;
    private final ExecutorService extractors;
    private final int perHost;
    private final Map<String, HostQueue> hostMap;

    private class HostQueue {
        private final Queue<Runnable> taskQueue;
        private int taskCounter;

        public HostQueue() {
            taskQueue = new ConcurrentLinkedQueue<>();
            taskCounter = 0;
        }

        public synchronized void addTask(final Runnable task) {
            if (taskCounter < perHost) {
                taskCounter++;
                downloaders.submit(task);
            } else {
                taskQueue.add(task);
            }
        }

        public synchronized void nextTask() {
            if (taskQueue.isEmpty()) {
                taskCounter--;
            } else {
                downloaders.submit(taskQueue.poll());
            }
        }
    }

    private static int parseIntOrDefault(String arg, int byDefault) {
        int toReturn;
        try {
            toReturn = Integer.parseInt(arg);
        } catch (final NumberFormatException e) {
            toReturn = byDefault;
        }
        return toReturn;
    }

    public static void main(String[] args) {
        if (args == null)
            throw new NullPointerException("Received null instead of arguments.");
        else {
            for (String arg : args) {
                if (arg == null) {
                    throw new NullPointerException("Arguments must not be null");
                }
            }
        }

        final int length = args.length;
        if (length == 0 || length > 5) {
            System.out.println("Wrong usage. Expected from 1 to 5 arguments, got " + args.length);
            System.out.println("Usage: \"WebCrawler url [depth [downloads [extractors [perHost]]]]\"");
            return;
        }

        String url = args[0];
        int depth = parseIntOrDefault((length >= 2) ? args[1] : "", 1);
        int downloads = parseIntOrDefault((length >= 3) ? args[2] : "", 8);
        int extractors = parseIntOrDefault((length >= 4) ? args[3] : "", 8);
        int perHost = parseIntOrDefault((length >= 5) ? args[4] : "", 8);

        try (Crawler crawler = new WebCrawler(new CachingDownloader(Path.of("Cawler")),
                downloads, extractors, perHost)) {
            final Result result = crawler.download(url, depth);
            final List<String> downloaded = result.getDownloaded();
            final Map<String, IOException> errors = result.getErrors();
            System.out.println("Downloaded:");
            downloaded.stream().map(page -> "\t" + page).forEach(System.out::println);
            System.out.println("Failed: ");
            errors.forEach
                    ((string, exception) -> System.out.println("\t" + string + "\n\t\twith exception " + exception));
        } catch (final IOException e) {
            System.out.println("IOException while crawling: " + e.getMessage());
        }
    }

    public WebCrawler(final Downloader downloader, final int downloaders, final int extractors, final int perHost) {
        this.downloader = downloader;
        this.downloaders = newFixedThreadPool(downloaders);
        this.extractors = newFixedThreadPool(extractors);
        this.perHost = perHost;
        this.hostMap = new ConcurrentHashMap<>();
    }

    private boolean tryAwaitForQueue(final Phaser phaser, final Queue<String> queue) {
        phaser.arriveAndAwaitAdvance();
        return !queue.isEmpty();
    }

    private void downloadHelper(final String url, final int depth, final Phaser phaser,
                                final Set<String> successful, final Map<String, Integer> alreadyVisited,
                                final Map<String, IOException> errors) {
        final Queue<String> urlQueue = new ConcurrentLinkedQueue<>();
        urlQueue.add(url);
        alreadyVisited.put(url, 1);
        int currLayer = 1;

        while (!urlQueue.isEmpty() || tryAwaitForQueue(phaser, urlQueue)) {
            final String currUrl = urlQueue.poll();
            final int urlDepth = alreadyVisited.get(currUrl);
            if (urlDepth > currLayer) {
                phaser.arriveAndAwaitAdvance();
                currLayer++;
            }

            final String host;
            try {
                host = URLUtils.getHost(currUrl);
            } catch (final MalformedURLException e) {
                errors.put(currUrl, e);
                continue;
            }
            final HostQueue hostQueue = hostMap.computeIfAbsent(host, key -> new HostQueue());
            phaser.register();
            hostQueue.addTask(() -> {
                try {
                    final Document page = downloader.download(currUrl);
                    successful.add(currUrl);
                    if (urlDepth < depth) {
                        phaser.register();
                        extractors.submit(() -> {
                            try {
                                final List<String> links = page.extractLinks();
                                for (final String link : links) {
                                    // :NOTE: you could have used computeIfAbsent
                                    synchronized (alreadyVisited) {
                                        if (!alreadyVisited.containsKey(link)) {
                                            alreadyVisited.put(link, urlDepth + 1);
                                            urlQueue.add(link);
                                        }
                                    }
                                }
                            } catch (IOException e) {
                                System.err.println("Extraction error on URL: " + currUrl);
                            } finally {
                                phaser.arriveAndDeregister();
                            }
                        });
                    }
                } catch (final IOException e) {
                    errors.put(currUrl, e);
                } finally {
                    phaser.arriveAndDeregister();
                    hostQueue.nextTask();
                }
            });
        }
    }

    @Override
    public Result download(final String url, final int depth) {
        if (url == null)
            throw new NullPointerException("URL string must not be null.");
        if (depth < 1)
            throw new IllegalArgumentException("Download depth must be at least 1");

        final Phaser phaser = new Phaser(1);
        final Set<String> successful = ConcurrentHashMap.newKeySet();
        final Map<String, Integer> alreadyVisited = new ConcurrentHashMap<>();
        final Map<String, IOException> errors = new ConcurrentHashMap<>();

        downloadHelper(url, depth, phaser, successful, alreadyVisited, errors);
        return new Result(new ArrayList<>(successful), errors);
    }

    @Override
    public void close() {
        shutdownAndAwaitTermination(downloaders);
        shutdownAndAwaitTermination(extractors);
    }

    // Copied from javadoc
    private void shutdownAndAwaitTermination(ExecutorService pool) {
        pool.shutdown(); // Disable new tasks from being submitted
        try {
            // Wait a while for existing tasks to terminate
            if (!pool.awaitTermination(60, TimeUnit.SECONDS)) {
                pool.shutdownNow(); // Cancel currently executing tasks
                // Wait a while for tasks to respond to being cancelled
                if (!pool.awaitTermination(60, TimeUnit.SECONDS))
                    System.err.println("Pool did not terminate");
            }
        } catch (InterruptedException ie) {
            // (Re-)Cancel if current thread also interrupted
            pool.shutdownNow();
            // Preserve interrupt status
            Thread.currentThread().interrupt();
        }
    }
}
