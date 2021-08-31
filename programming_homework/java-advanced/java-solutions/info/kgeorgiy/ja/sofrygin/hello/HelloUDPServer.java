package info.kgeorgiy.ja.sofrygin.hello;

import info.kgeorgiy.java.advanced.hello.HelloServer;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.ExecutorService;

import static info.kgeorgiy.ja.sofrygin.hello.HelloUtils.checkAndRunServer;
import static info.kgeorgiy.ja.sofrygin.hello.HelloUtils.shutdownAndAwaitTermination;
import static java.util.concurrent.Executors.newFixedThreadPool;

public class HelloUDPServer implements HelloServer {
    private final static Charset CHARSET = StandardCharsets.UTF_8;
    private ExecutorService threadPool;
    private DatagramSocket serverSocket;

    @Override
    public void start(final int port, final int threads) {
        if (serverSocket != null && !serverSocket.isClosed()) {
            close();
        }

        try {
            serverSocket = new DatagramSocket(port);
        } catch (final SocketException e) {
            System.err.println("An error occurred while opening a socket: " + e.getMessage());
            return;
        }
        threadPool = newFixedThreadPool(threads);

        final Runnable task = () -> {
            try {
                final int buffSize = serverSocket.getReceiveBufferSize();
                final DatagramPacket received = new DatagramPacket(new byte[buffSize], buffSize);
                final DatagramPacket response = new DatagramPacket(new byte[0], 0);
                while (!serverSocket.isClosed()) {
                    serverSocket.receive(received);
                    final String message = "Hello, " + new String(received.getData(),
                            received.getOffset(), received.getLength(), CHARSET);
                    final byte[] data = message.getBytes(CHARSET);
                    response.setData(data);
                    response.setSocketAddress(received.getSocketAddress());
                    serverSocket.send(response);
                }
            } catch (final SocketException e) {
                // ignore and end
            } catch (final IOException e) {
                System.err.println("IO error occurred: " + e.getMessage());
            }
        };
        for (int i = 0; i < threads; i++) {
            threadPool.submit(task);
        }
    }

    // :NOTE: Не дождались
    @Override
    public void close() {
        serverSocket.close();
        shutdownAndAwaitTermination(threadPool);
    }

    public static void main(final String[] args) {
        checkAndRunServer(args, new HelloUDPServer());
    }
}
