package info.kgeorgiy.ja.sofrygin.hello;

import info.kgeorgiy.java.advanced.hello.HelloClient;

import java.io.IOException;
import java.net.*;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.stream.IntStream;

import static info.kgeorgiy.ja.sofrygin.hello.HelloUtils.checkAndRunClient;
import static info.kgeorgiy.ja.sofrygin.hello.HelloUtils.getServerAddress;
import static java.util.concurrent.Executors.newFixedThreadPool;

public class HelloUDPClient implements HelloClient {
    private static final Charset CHARSET = StandardCharsets.UTF_8;
    private static final int TIMEOUT = 500;

    @Override
    public void run(final String host, final int port, final String prefix, final int threads, final int requests) {
        final SocketAddress serverAddress = getServerAddress(host, port);
        // :NOTE: null -> IOException

        final ExecutorService threadPool = newFixedThreadPool(threads);
        final CountDownLatch latch = new CountDownLatch(threads);
        // :NOTE: IntStream
        IntStream.range(0, threads).forEach(id -> {
            final String requestPrefix = prefix + id + '_';
            threadPool.submit(() -> {
                try (final DatagramSocket socket = new DatagramSocket()) {
                    socket.setSoTimeout(TIMEOUT);
                    final int buffSize = socket.getReceiveBufferSize();
                    final DatagramPacket received = new DatagramPacket(new byte[buffSize], buffSize);
                    final DatagramPacket toSend = new DatagramPacket(new byte[0], 0, serverAddress);

                    for (int requestId = 0; requestId < requests; requestId++) {
                        final String request = requestPrefix + requestId;
                        toSend.setData(request.getBytes(CHARSET));

                        while (!socket.isClosed()) {
                            try {
                                socket.send(toSend);
                                socket.receive(received);

                                final String response = new String(received.getData(),
                                        received.getOffset(), received.getLength(), CHARSET);
                                if (!response.contains(request)) {
                                    continue;
                                }
                                System.out.println("Request = \"" + request + "\"; Response = \"" + response + '\"');
                                break;
                            } catch (final SocketTimeoutException e) {
                                // repeat
                            }
                        }
                    }
                } catch (final SocketException e) {
                    System.err.println("Socket error occurred: " + e.getMessage());
                } catch (final IOException e) {
                    System.err.println("IO error occurred: " + e.getMessage());
                } finally {
                    latch.countDown();
                }
            });
        });

        try {
            latch.await();
        } catch (final InterruptedException ignored) {
            // ignore
        }
        threadPool.shutdownNow();
    }

    public static void main(final String[] args) {
        checkAndRunClient(args, new HelloUDPClient());
    }
}
