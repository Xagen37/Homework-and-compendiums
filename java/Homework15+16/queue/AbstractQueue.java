package queue;

public abstract class AbstractQueue implements Queue {
    protected int size = 0;

    protected void checkEnqueue(Object element) {
        assert element != null;
        size++;
    }

    protected void checkDequeue() {
        assert size > 0;
        size--;
    }

    protected void checkElement() {
        assert size > 0;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
    }

    protected void nullifySize() {
        size = 0;
    }
}
