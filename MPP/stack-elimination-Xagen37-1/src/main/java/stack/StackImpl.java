package stack;

import kotlinx.atomicfu.AtomicInt;
import kotlinx.atomicfu.AtomicIntArray;
import kotlinx.atomicfu.AtomicRef;

import java.util.concurrent.ThreadLocalRandom;

public class StackImpl implements Stack {
    private static class Node {
        final AtomicRef<Node> next;
        final int x;

        Node(int x, Node next) {
            this.next = new AtomicRef<>(next);
            this.x = x;
        }
    }

    // head pointer
    private final AtomicRef<Node> head = new AtomicRef<>(null);

    private final static int ARRAYSIZE = 128;   // elimination array size
    private final static int DONEMARK = Integer.MIN_VALUE + 1;  // value for successful pop from array
    private final static int VOIDMARK = Integer.MIN_VALUE;  // default null value
    private final static int SPINTIME = 500;    // how many loop iterations will push wait
    private final static int POS_TRIES = 8;     // how many positions we will try
    private final AtomicIntArray eliminationArray = new AtomicIntArray(ARRAYSIZE);

    public StackImpl() {
        for (int i = 0; i < ARRAYSIZE; i++) {
            eliminationArray.get(i).setValue(VOIDMARK);
        }
    }

    @Override
    public void push(final int x) {
        if (x != DONEMARK && tryPushElimination(x)) {
            return;
        }
        while (true) {
            Node oldHead = head.getValue();
            Node newHead = new Node(x, oldHead);
            if (head.compareAndSet(oldHead, newHead)) {
                return;
            }
        }
    }

    // Generate array positions push or pop are going to try
    private int[] generatePositions() {
        final int[] positions = new int[POS_TRIES];
        positions[0] = ThreadLocalRandom.current().nextInt(ARRAYSIZE);
        for (int i = 1; i < POS_TRIES; i++) {
            positions[i] = (positions[i - 1] + 1) % ARRAYSIZE;
        }
        return positions;
    }

    // Try to put value into elimination array
    private boolean tryPushElimination(final int x) {
        final int[] positions = generatePositions();
        for (int i = 0; i < POS_TRIES; i++) {
            if (eliminationArray.get(positions[i]).compareAndSet(VOIDMARK, x)) {
                return pushWaiting(positions[i], x);
            }
        }
        return false;
    }

    // Wait for pop to collect our value or for iterations threshold
    private boolean pushWaiting(final int pos, final int x) {
        for (int i = 0; i < SPINTIME; i++) {
            if (eliminationArray.get(pos).compareAndSet(DONEMARK, VOIDMARK)) {
                return true;
            }
        }
        return !eliminationArray.get(pos).compareAndSet(x, VOIDMARK);
    }

    @Override
    public int pop() {
        final int[] positions = generatePositions();
        int res;
        for (int i = 1; i < POS_TRIES; i++) {
            if ((res = tryPop(positions[i])) != VOIDMARK) {
                return res;
            }
        }

        while (true) {
            Node oldHead = head.getValue();
            if (oldHead == null) {
                return Integer.MIN_VALUE;
            }
            if (head.compareAndSet(oldHead, oldHead.next.getValue())) {
                return oldHead.x;
            }
        }
    }

    // Check, if the given position in elimination array contains a value, and try to get the value, if any
    private int tryPop(final int pos) {
        final AtomicInt copy = eliminationArray.get(pos);
        final int res = copy.getValue();
        if (res != VOIDMARK &&
            res != DONEMARK &&
            copy.compareAndSet(res, DONEMARK)) {
            return res;
        }
        return VOIDMARK;
    }
}
