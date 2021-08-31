package info.kgeorgiy.ja.sofrygin.arrayset;

import java.util.*;

public class ArraySet<E> extends AbstractSet<E> implements SortedSet<E> {

    private final ArrayList<E> array;
    private final Comparator<? super E> comparator;

    @SuppressWarnings("unchecked")
    private int comparison(E left, E right) {
        return comparator == null
                ? ((Comparable<E>) left).compareTo(right)
                : comparator.compare(left, right);
    }

    public ArraySet(final Collection<? extends E> collection, final Comparator<? super E> comparator) {
        TreeSet<E> tempSet = new TreeSet<>(comparator);
        tempSet.addAll(collection);
        this.array = new ArrayList<>(tempSet);
        this.comparator = comparator;
    }

    public ArraySet() {
        this(Collections.emptyList(), null);
    }

    public ArraySet(final Comparator<? super E> comparator) {
        this(Collections.emptyList(), comparator);
    }

    public ArraySet(final Collection<? extends E> collection) {
        this(collection, null);
    }

    public ArraySet(SortedSet<E> set) {
        this(set, set.comparator());
    }

    @Override
    public Iterator<E> iterator() {
        return Collections.unmodifiableList(array).iterator();
    }

    @Override
    public int size() {
        return array.size();
    }

    @Override
    public Comparator<? super E> comparator() {
        return comparator;
    }

    private int getId(E elem) {
        int searchRes = Collections.binarySearch(array, elem, comparator);
        if (searchRes < 0) {
            searchRes = -(searchRes + 1);
        }
        return searchRes;
    }

    @Override
    public SortedSet<E> subSet(E fromElement, E toElement) {
        if (comparison(fromElement, toElement) > 0) {
            throw new IllegalArgumentException();
        }
        return tailSet(fromElement).headSet(toElement);
    }

    private SortedSet<E> subSetHelper(int fromId, int toId) {
        if (isEmpty()) {
            return this;
        } else if (fromId > toId) {
            return new ArraySet<>(comparator);
        }

        return new ArraySet<>(array.subList(fromId, toId), comparator);
    }

    @Override
    public SortedSet<E> headSet(E toElement) {
        return subSetHelper(0, getId(toElement));
    }

    @Override
    public SortedSet<E> tailSet(E fromElement) {
        return subSetHelper(getId(fromElement), array.size());
    }

    @Override
    public E first() {
        if (size() == 0) {
            throw new NoSuchElementException();
        }
        return array.get(0);
    }

    @Override
    public E last() {
        if (size() == 0) {
            throw new NoSuchElementException();
        }
        return array.get(size() - 1);
    }

    @Override
    @SuppressWarnings("unchecked")
    public boolean contains(Object o) {
        return Collections.binarySearch(array, (E) o, comparator) >= 0;
    }
}
