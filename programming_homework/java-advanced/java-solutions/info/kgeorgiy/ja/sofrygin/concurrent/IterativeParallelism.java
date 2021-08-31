package info.kgeorgiy.ja.sofrygin.concurrent;

import info.kgeorgiy.java.advanced.concurrent.AdvancedIP;
import info.kgeorgiy.java.advanced.mapper.ParallelMapper;

import java.util.*;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class IterativeParallelism implements AdvancedIP {

    private final ParallelMapper mapper;

    public IterativeParallelism() {
        mapper = null;
    }

    public IterativeParallelism(ParallelMapper mapper) {
        this.mapper = mapper;
    }

    private <T, R> R apply(int threads, final List<T> values, final Function<Stream<T>, R> mapFunction, final Function<Stream<R>, R> reduceFunction) throws InterruptedException {
        if (threads <= 0) {
            throw new IllegalArgumentException("Number of threads must be positive");
        }
        if (values == null) {
            throw new NullPointerException("Values list must not be null");
        }

        threads = Math.max(Math.min(threads, values.size()), 1);
        final int chunkSize = values.size() / threads;
        int remainder = values.size() - chunkSize * threads;
        // :NOTE: task += 1
        List<Stream<T>> chunks = new ArrayList<>();
        int prevRight = 0;
        for (int i = 0; i < threads; i++) {
            int right = prevRight + chunkSize;
            if (remainder > 0) {
                right++;
                remainder--;
            }
            chunks.add(values.subList(prevRight, right).stream());
            prevRight = right;
        }


        List<R> results;
        if (this.mapper == null) {
            results = new ArrayList<>(Collections.nCopies(threads, null));
            List<Thread> workers = new ArrayList<>();
            for (int i = 0; i < threads; i++) {
                int idxCopy = i;
                Thread worker = new Thread(() -> results.set(idxCopy, mapFunction.apply(chunks.get(idxCopy))));
                workers.add(worker);
                worker.start();
            }

            for (int i = 0; i < threads; i++) {
                workers.get(i).join();
            }
        } else {
            results = mapper.map(mapFunction, chunks);
        }
        return reduceFunction.apply(results.stream());
    }

    private <T> T maxFunction(Stream<? extends T> stream, Comparator<? super T> comparator) {
        return stream.max(comparator).orElseThrow();
    }

    @Override
    public <T> T maximum(final int threads, final List<? extends T> values, final Comparator<? super T> comparator) throws InterruptedException {
        return apply(threads, values,
                stream -> maxFunction(stream, comparator),
                stream -> maxFunction(stream, comparator));
    }

    @Override
    public <T> T minimum(final int threads, final List<? extends T> values, final Comparator<? super T> comparator) throws InterruptedException {
        return maximum(threads, values, comparator.reversed());
    }

    @Override
    public <T> boolean all(final int threads, final List<? extends T> values, final Predicate<? super T> predicate) throws InterruptedException {
        return apply(threads, values,
                stream -> stream.allMatch(predicate),
                booleanStream -> booleanStream.allMatch(val -> val));
    }

    @Override
    public <T> boolean any(final int threads, final List<? extends T> values, final Predicate<? super T> predicate) throws InterruptedException {
        return !all(threads, values, predicate.negate());
    }

    @Override
    public String join(int threads, List<?> values) throws InterruptedException {
        return apply(threads, values,
                stream -> stream.map(Object::toString).collect(Collectors.joining()),
                stream -> stream.collect(Collectors.joining()));
    }

    private <T> List<T> collectFunction(Stream<? extends Collection<T>> collectionStream) {
        return collectionStream.flatMap(Collection::stream).collect(Collectors.toList());
    }

    @Override
    public <T> List<T> filter(int threads, List<? extends T> values, Predicate<? super T> predicate) throws InterruptedException {
        return apply(threads, values,
                stream -> stream.filter(predicate).collect(Collectors.toList()),
                this::collectFunction);
    }

    @Override
    public <T, U> List<U> map(int threads, List<? extends T> values, Function<? super T, ? extends U> f) throws InterruptedException {
        return apply(threads, values,
                stream -> stream.map(f).collect(Collectors.toList()),
                this::collectFunction);
    }

    @Override
    public <T> T reduce(int threads, List<T> values, Monoid<T> monoid) throws InterruptedException {
        final Function<Stream<T>, T> monoidFunction = stream -> stream.reduce(monoid.getIdentity(), monoid.getOperator());
        return apply(threads, values,
                monoidFunction,
                monoidFunction);
    }

    @Override
    public <T, R> R mapReduce(int threads, List<T> values, Function<T, R> lift, Monoid<R> monoid) throws InterruptedException {
        return reduce(threads, map(threads, values, lift), monoid);
    }
}
