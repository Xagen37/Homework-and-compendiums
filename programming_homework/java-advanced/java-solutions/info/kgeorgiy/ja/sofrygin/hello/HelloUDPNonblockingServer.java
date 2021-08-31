// Working, but not as it intended to
package info.kgeorgiy.ja.sofrygin.hello;

import info.kgeorgiy.java.advanced.hello.HelloServer;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.net.StandardSocketOptions;
import java.nio.ByteBuffer;
import java.nio.channels.DatagramChannel;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.util.Iterator;
import java.util.Queue;
import java.util.Set;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import static info.kgeorgiy.ja.sofrygin.hello.HelloUtils.checkAndRunServer;
import static info.kgeorgiy.ja.sofrygin.hello.HelloUtils.shutdownAndAwaitTermination;
import static java.util.concurrent.Executors.newFixedThreadPool;

public class HelloUDPNonblockingServer implements HelloServer {
    private final static Charset CHARSET = StandardCharsets.UTF_8;
    private static final int TIMEOUT = 250;
    private Selector selector;
    private ExecutorService listener;
    private ExecutorService workers;
    private Queue<Message> messageQueue;

    private static class Message {
        ByteBuffer data;
        SocketAddress address;
    }

    @Override
    public void start(final int port, final int threads) {
        if (selector != null && selector.isOpen()) {
            close();
        }
        try {
            selector = Selector.open();
        } catch (final IOException e) {
            System.err.println("Error while opening a selector: " + e.getMessage());
            return;
        }
        final DatagramChannel channel;
        try {
            channel = DatagramChannel.open();
            final SocketAddress address = new InetSocketAddress(port);
            channel.bind(address);
            channel.configureBlocking(false);
        } catch (final IOException e) {
            System.err.println("Could not open a channel or bind it: " + e.getMessage());
            return;
        }

        listener = Executors.newSingleThreadExecutor();
        if (threads == 1) {
            listener.submit(getSingleThreadTask(channel, port));
        } else {
            workers = newFixedThreadPool(threads - 1);
            messageQueue = new ConcurrentLinkedQueue<>();
            listener.submit(getMultiThreadTask(channel, port));
        }
    }

    private Runnable getMultiThreadTask(final DatagramChannel channel, final int port) {
        return () -> {
            try {
                final Message msg = new Message();
                msg.data = ByteBuffer.allocate(channel.getOption(StandardSocketOptions.SO_RCVBUF));
                channel.register(selector, SelectionKey.OP_READ, msg);
                while (selector.isOpen()) {
                    selector.select(TIMEOUT);

                    Set<SelectionKey> keys = selector.selectedKeys();
                    for (final Iterator<SelectionKey> it = keys.iterator(); it.hasNext(); ) {
                        final SelectionKey key = it.next();

                        if (key.isReadable()) {
                            final DatagramChannel readChan = (DatagramChannel) key.channel();
                            final Message attachment = (Message) key.attachment();
                            attachment.data.clear();
                            attachment.address = readChan.receive(attachment.data);
                            final ByteBuffer receivedData = attachment.data;
                            workers.submit(() -> {
                                final String answer = "Hello, " +
                                        new String(receivedData.array(), 0, receivedData.position(), CHARSET);
                                final Message message = new Message();
                                message.address = attachment.address;
                                message.data = ByteBuffer.wrap(answer.getBytes(CHARSET));
                                messageQueue.add(message);
                            });

                            key.interestOps(SelectionKey.OP_WRITE);
                        } else if (key.isWritable()) {
                            final DatagramChannel writeChan = (DatagramChannel) key.channel();
                            final Message toSend = messageQueue.poll();
                            if (toSend != null) {
                                writeChan.send(toSend.data, toSend.address);
                                key.interestOps(SelectionKey.OP_READ);
                            }
                        }
                        it.remove();
                    }
                }
            } catch (final IOException e) {
                System.err.println("Error while working: " + e.getMessage());
            }
        };
    }

    private Runnable getSingleThreadTask(final DatagramChannel channel, final int port) {
        return () -> {
            try {
                final Message msg = new Message();
                msg.data = ByteBuffer.allocate(channel.getOption(StandardSocketOptions.SO_RCVBUF));
                channel.register(selector, SelectionKey.OP_READ, msg);
                while (selector.isOpen()) {
                    selector.select(TIMEOUT);

                    final Set<SelectionKey> keys = selector.selectedKeys();
                    for (final Iterator<SelectionKey> it = keys.iterator(); it.hasNext(); ) {
                        final SelectionKey key = it.next();

                        if (key.isReadable()) {
                            final DatagramChannel readChan = (DatagramChannel) key.channel();
                            final Message attachment = (Message) key.attachment();
                            attachment.data.clear();
                            attachment.address = readChan.receive(attachment.data);
                            key.interestOps(SelectionKey.OP_WRITE);
                        } else if (key.isWritable()) {
                            final DatagramChannel writeChan = (DatagramChannel) key.channel();
                            final Message toSend = (Message) key.attachment();
                            final String answer = "Hello, " +
                                    new String(toSend.data.array(), 0, toSend.data.position(), CHARSET);
                            writeChan.send(ByteBuffer.wrap(answer.getBytes(CHARSET)), toSend.address);
                            key.interestOps(SelectionKey.OP_READ);
                        }
                        it.remove();
                    }
                }
            } catch (final IOException e) {
                System.err.println("Error while working: " + e.getMessage());
            }
        };
    }

    @Override
    public void close() {
        try {
            selector.close();
        } catch (final IOException e) {
            // ignore
        }
        shutdownAndAwaitTermination(listener);
        shutdownAndAwaitTermination(workers);
    }

    public static void main(final String[] args) {
        checkAndRunServer(args, new HelloUDPNonblockingServer());
    }
}