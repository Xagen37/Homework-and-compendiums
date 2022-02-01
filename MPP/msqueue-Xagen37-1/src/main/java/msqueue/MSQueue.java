package msqueue;

import kotlinx.atomicfu.*;

public class MSQueue implements Queue {
    private final AtomicRef<Node> head;
    private final AtomicRef<Node> tail;

    public MSQueue() {
        final Node dummy = new Node(0);
        this.head = new AtomicRef<>(dummy);
        this.tail = new AtomicRef<>(dummy);
    }

    @Override
    public void enqueue(final int x) {
        final Node newTail = new Node(x);
        Node oldTail;
        while (true) {
            oldTail = tail.getValue();
            if (oldTail.next.compareAndSet(null, newTail)) {
                tail.compareAndSet(oldTail, newTail);
                return;
            } else {
                tail.compareAndSet(oldTail, oldTail.next.getValue());
            }
        }
    }

    @Override
    public int dequeue() {
        Node oldHead, oldNext, oldTail;
        while (true) {
            oldHead = head.getValue();
            oldTail = tail.getValue();
            oldNext = oldHead.next.getValue();
            if (head.getValue() == oldHead) {
                if (oldHead == oldTail) {
                    if (oldNext == null) {
                        return Integer.MIN_VALUE;
                    }
                    tail.compareAndSet(oldTail, oldNext);
                } else {
                    if (head.compareAndSet(oldHead, oldNext)) {
                        return oldNext.x;
                    }
                }
            }
        }
    }

    @Override
    public int peek() {
        final Node curHead = head.getValue();
        final Node next = head.getValue().next.getValue();
        if (curHead == tail.getValue() || next == null)
            return Integer.MIN_VALUE;
        return next.x;
    }

    private class Node {
        final int x;
        private final AtomicRef<Node> next;

        Node(int x) {
            this.x = x;
            this.next = new AtomicRef<>(null);
        }
    }
}