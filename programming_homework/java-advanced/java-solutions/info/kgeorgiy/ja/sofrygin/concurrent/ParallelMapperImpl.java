package info.kgeorgiy.ja.sofrygin.concurrent;

import info.kgeorgiy.java.advanced.mapper.ParallelMapper;

import java.util.*;
import java.util.function.Function;

public class ParallelMapperImpl implements ParallelMapper {
    private final List<Thread> threads;
    private final TaskManager taskQueue;

    private static class TaskManager {
        private final Queue<Runnable> queue = new LinkedList<>();

        public synchronized void addTask(final Runnable task) {
            queue.add(task);
            notify();
        }

        public synchronized Runnable getTask() throws InterruptedException {
            while (queue.isEmpty()) {
                wait();
            }
            return queue.poll();
        }
    }

    public ParallelMapperImpl(final int threadsNum) {
        if (threadsNum <= 0)
            throw new IllegalArgumentException("Number of threads must be positive");

        threads = new ArrayList<>();
        taskQueue = new TaskManager();
        Runnable runFunction = () -> {
            try {
                while (!Thread.interrupted())
                    taskQueue.getTask().run();
            } catch (final InterruptedException e) {
                // do nothing
            } finally {
                Thread.currentThread().interrupt();
            }
        };
        for (int i = 0; i < threadsNum; i++) {
            Thread newWorker = new Thread(runFunction);
            threads.add(i, newWorker);
            newWorker.start();
        }
    }

    private static class ResultArray<R> {
        final List<R> results;
        final List<RuntimeException> exceptions;
        int cnt;

        ResultArray(final int size) {
            results = new ArrayList<>(Collections.nCopies(size, null));
            exceptions = new ArrayList<>();
            cnt = size;
        }

        public synchronized void set(final int id, final R val) {
            results.set(id, val);
            cnt--;
            if (cnt == 0)
                notify();
        }

        public synchronized void addException(final RuntimeException e) {
            exceptions.add(e);
            cnt--;
            if (cnt == 0)
                notify();
        }

        public synchronized List<R> getAll()  throws InterruptedException {
            while (cnt > 0) {
                wait();
            }
            return results;
        }

        public synchronized RuntimeException getExceptions() throws InterruptedException {
            while (cnt > 0) {
                wait();
            }

            RuntimeException collector = null;
            for (RuntimeException e : exceptions) {
                if (collector == null) {
                    collector = e;
                } else {
                    collector.addSuppressed(e);
                }
            }
            return collector;
        }
    }

    @Override
    public <T, R> List<R> map(final Function<? super T, ? extends R> f, final List<? extends T> args) throws InterruptedException {
        final ResultArray<R> results = new ResultArray<>(args.size());

        for (int i = 0; i < args.size(); i++) {
            final int idxCopy = i;
            taskQueue.addTask(() -> {
                try {
                    results.set(idxCopy, f.apply(args.get(idxCopy)));
                } catch (RuntimeException runtime) {
                    results.addException(runtime);
                }
            });
        }

        RuntimeException mapExceptions = results.getExceptions();
        if (mapExceptions != null) {
            throw mapExceptions;
        }
        return results.getAll();
    }

    @Override
    public void close() {
        for (final Thread thread : threads) {
            thread.interrupt();
        }
        for (final Thread thread : threads) {
            try {
                thread.join();
            } catch (final InterruptedException e) {
                // do nothing
            }
        }
    }
}
