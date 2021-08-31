package info.kgeorgiy.ja.sofrygin.hello;

import info.kgeorgiy.java.advanced.hello.HelloClient;
import info.kgeorgiy.java.advanced.hello.HelloServer;

import java.io.UncheckedIOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.net.UnknownHostException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.TimeUnit;

public class HelloUtils {

    public static SocketAddress getServerAddress(final String host, final int port) {
        try {
            return new InetSocketAddress(InetAddress.getByName(host), port);
        } catch (final UnknownHostException e) {
            throw new UncheckedIOException("Could not find IP address for  the host", e);
        }
    }

    public static void checkAndRunClient(final String[] args, final HelloClient client) {
        if (args == null) {
            System.err.println("args must not be null");
            return;
        } else if (args.length != 5) {
            System.err.println("Wrong number of arguments. Expected 5, got " + args.length);
            return;
        } else {
            for (int i = 0; i < 5; i++) {
                if (args[i] == null) {
                    System.err.println("None of the arguments may be null");
                    return;
                }
            }
        }
        final String host, prefix;
        final int port, threads, requests;
        try {
            host = args[0];
            port = Integer.parseInt(args[1]);
            prefix = args[2];
            threads = Integer.parseInt(args[3]);
            requests = Integer.parseInt(args[4]);
        } catch (final IllegalArgumentException e) {
            System.err.println("Wrong arguments format: " + e.getMessage());
            return;
        }
        client.run(host, port, prefix, threads, requests);
    }

    public static void checkAndRunServer(final String[] args, final HelloServer server) {
        if (args == null) {
            System.err.println("args must not be null");
            return;
        } else if (args.length != 2) {
            System.err.println("Wrong number of arguments. Expected 2, got " + args.length);
            return;
        } else {
            for (int i = 0; i < 2; i++) {
                if (args[i] == null) {
                    System.err.println("None of the arguments may be null");
                    return;
                }
            }
        }

        final int port, threads;
        try {
            port = Integer.parseInt(args[0]);
            threads = Integer.parseInt(args[1]);
        } catch (final IllegalArgumentException e) {
            System.err.println("Wrong arguments format: " + e.getMessage());
            return;
        }

        try {
            System.out.println("Starting server");
            server.start(port, threads);
        } finally {
            System.out.println("Server shut down");
        }
    }

    public static void shutdownAndAwaitTermination(ExecutorService pool) {
        if (pool == null)
            return;

        pool.shutdownNow();
        try {
            if (!pool.awaitTermination(15, TimeUnit.SECONDS)) {
                System.err.println("Pool did not terminate");
            }
        } catch (final InterruptedException ie) {
            Thread.currentThread().interrupt();
        }
    }
}
