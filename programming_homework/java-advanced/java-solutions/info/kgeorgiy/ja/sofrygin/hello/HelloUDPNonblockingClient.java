package info.kgeorgiy.ja.sofrygin.hello;

import info.kgeorgiy.java.advanced.hello.HelloClient;

import java.io.IOException;
import java.io.UncheckedIOException;
import java.net.SocketAddress;
import java.net.StandardSocketOptions;
import java.nio.ByteBuffer;
import java.nio.channels.DatagramChannel;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.util.AbstractMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.stream.IntStream;

import static info.kgeorgiy.ja.sofrygin.hello.HelloUtils.checkAndRunClient;
import static info.kgeorgiy.ja.sofrygin.hello.HelloUtils.getServerAddress;

public class HelloUDPNonblockingClient implements HelloClient {
    private static final int TIMEOUT = 250;
    private static final Charset CHARSET = StandardCharsets.UTF_8;

    @Override
    @SuppressWarnings("unchecked")
    public void run(final String host, final int port, final String prefix, final int threads, final int requests) {
        final SocketAddress serverAddress = getServerAddress(host, port);

        final int[] progress = new int[threads];
        final Selector selector;
        try {
            selector = Selector.open();
        } catch (final IOException e) {
            System.err.println("Error while opening a selector: " + e.getMessage());
            return;
        }

        IntStream.range(0, threads).forEach(i -> {
            try {
                final DatagramChannel channel = DatagramChannel.open();
                channel.configureBlocking(false);
                channel.connect(serverAddress);
                final int buffSize = channel.getOption(StandardSocketOptions.SO_RCVBUF);
                final ByteBuffer buffer = ByteBuffer.allocate(buffSize);
                // :NOTE: Map.Entry
                final Map.Entry<Integer, ByteBuffer> context = new AbstractMap.SimpleEntry<>(i, buffer);
                channel.register(selector, SelectionKey.OP_WRITE, context);
                // :NOTE: Гонки
            } catch (final IOException e) {
                throw new UncheckedIOException("Error while starting channels: " + e.getMessage(), e);
            }
        });

        try {
            while (!selector.keys().isEmpty()) {
                selector.select(TIMEOUT);
                final Set<SelectionKey> selected = selector.selectedKeys();
                // :NOTE: Плохая проверка
                if (selected.isEmpty()) {
                    selector.keys().forEach(key -> key.interestOps(SelectionKey.OP_WRITE));
                    continue;
                }
                for (final Iterator<SelectionKey> it = selected.iterator(); it.hasNext(); ) {
                    final SelectionKey key = it.next();
                    if (key.isWritable()) {
                        final DatagramChannel channel = (DatagramChannel) key.channel();
                        final Map.Entry<Integer, ByteBuffer> context = (Map.Entry<Integer, ByteBuffer>) key.attachment();
                        final int threadId = context.getKey();
                        final String request = prefix + threadId + '_' + progress[threadId];
                        final ByteBuffer data = ByteBuffer.wrap(request.getBytes(CHARSET));
                        channel.write(data);
                        key.interestOps(SelectionKey.OP_READ);
                    } else if (key.isReadable()) {
                        final DatagramChannel channel = (DatagramChannel) key.channel();
                        final Map.Entry<Integer, ByteBuffer> context = (Map.Entry<Integer, ByteBuffer>) key.attachment();
                        final ByteBuffer received = context.getValue();
                        received.clear();
                        final int threadId = context.getKey();

                        channel.receive(received);
                        final String response = new String(received.array(), 0, received.position(), CHARSET);
                        if (response.contains(prefix + threadId + '_' + progress[threadId])) {
                            System.out.println("Response = " + response);
                            if (++progress[threadId] == requests) {
                                channel.close();
                                it.remove();
                                continue;
                            }
                        }
                        key.interestOps(SelectionKey.OP_WRITE);
                    }
                    it.remove();
                }
            }
        } catch (final IOException e) {
            System.err.println("Error while selecting: " + e.getMessage());
        }

    }

    public static void main(final String[] args) {
        checkAndRunClient(args, new HelloUDPNonblockingClient());
    }
}
