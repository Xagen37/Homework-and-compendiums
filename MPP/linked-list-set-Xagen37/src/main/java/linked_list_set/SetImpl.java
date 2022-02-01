package linked_list_set;

import kotlinx.atomicfu.*;

public class SetImpl implements Set {

    private interface Base {
        int getX();
        AtomicRef<Base> getNext();
    }

    private class Node implements Base{
        final AtomicRef<Base> next;     // getValue is instanceOf Removed if THIS node is deleted
        int x;

        Node(int x, Base next) {
            this.next = new AtomicRef<>(next);
            this.x = x;
        }

        @Override
        public int getX() {
            return x;
        }

        @Override
        public AtomicRef<Base> getNext() {
            return next;
        }
    }

    private class Removed implements Base{
        final Base wrapped;
        Removed (Base wrap) {
            wrapped = wrap;
        }

        @Override
        public int getX() {
            return wrapped.getX();
        }

        @Override
        public AtomicRef<Base> getNext() {
            return wrapped.getNext();
        }
    }

    private boolean removed (Base node) {
        return node.getNext().getValue() instanceof Removed;
    }

    private class Window {
        Base cur, next;
    }

    private final Node head = new Node(Integer.MIN_VALUE, new Node(Integer.MAX_VALUE, null));

    /**
     * Returns the {@link Window}, where cur.x < x <= next.x
     */
    private Window findWindow(int x) {
        Window w = new Window();
        retry: while (true) {
            w.cur = head;
            w.next = w.cur.getNext().getValue();
            while (w.next.getX() < x || removed(w.next)) {
                if (removed(w.cur)) {
                    continue retry;
                }

                if (removed(w.next)) {
                    Base node = ((Removed) w.next.getNext().getValue()).wrapped;
                    if (!w.cur.getNext().compareAndSet(w.next, node)) {
                        w.next = w.cur.getNext().getValue();
                        continue;
                    }
                    w.next = node;
                } else {
                    w.cur = w.next;
                    w.next = w.cur.getNext().getValue();
                }
            }

            if (removed(w.cur) || removed(w.next)) {
                continue;
            }
            return w;
        }
    }

    @Override
    public boolean add(int x) {
        while (true) {
            Window w = findWindow(x);
            if (w.next.getX() == x) {
                return false;
            }

            if (!removed(w.cur) && !removed(w.next) &&
                w.cur.getNext().compareAndSet(w.next, new Node(x, w.next))) {
                return true;
            }
        }
    }

    @Override
    public boolean remove(int x) {
        while (true) {
            Window w = findWindow(x);
            if (w.next.getX() != x) {
                return false;
            }

            Base next = w.next.getNext().getValue();
            Removed wrapped_next = new Removed(next);
            if (!removed(w.next) &&
                w.next.getNext().compareAndSet(next, wrapped_next)) {
                if (!removed(w.cur)) {
                    w.cur.getNext().compareAndSet(w.next, wrapped_next.wrapped);
                }
                return true;
            }
        }
    }

    @Override
    public boolean contains(int x) {
        Window w = findWindow(x);
        return w.next.getX() == x;
    }
}