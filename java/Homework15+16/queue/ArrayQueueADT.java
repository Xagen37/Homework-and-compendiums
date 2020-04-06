package queue;

import java.util.Arrays;

//inv: size >= 0
//     for any element in queue: element != null
public class ArrayQueueADT {
    private int head = 0, size = 0;
    private Object[] elements = new Object[10];

    //pred: elem != null && queue != null
    public static void enqueue(ArrayQueueADT queue, Object elem) {
        assert elem != null;
        assert queue != null;
        ensureCapacity(queue,queue.size + 1);
        queue.elements[(queue.head + queue.size) % queue.elements.length] = elem;
        queue.size++;
    }
    //post: new_size = prev_size + 1 &&
    //      for any element in queue: new_element == prev_element &&
    //      a[prev_size] = elem

    private static void ensureCapacity(ArrayQueueADT queue, int capacity) {
        if (capacity <= queue.elements.length) {
            return;
        }
        Object[] newElements = new Object[2 * capacity];
        if (queue.head + queue.size > queue.elements.length) {
            System.arraycopy(queue.elements, queue.head, newElements, 0, queue.elements.length - queue.head );
            System.arraycopy(queue.elements, 0, newElements, queue.elements.length - queue.head, queue.head);
        } else {
            System.arraycopy(queue.elements, queue.head, newElements, 0, queue.size);
        }
        queue.elements = newElements;
        queue.head = 0;
        /*Object[] newElements = new Object[2 * capacity];
        for (int i = 0; i < queue.size; i++) {
            newElements[i] = queue.elements[(queue.head + i) % queue.size];
        }
        queue.elements = newElements;
        queue.head = 0;*/
    }
    //post: new_capacity = 2 * old_capacity && queue is immutable

    //pred: size > 0 && queue != null
    public static Object dequeue(ArrayQueueADT queue) {
        assert queue.size > 0;
        assert queue != null;

        Object toReturn = queue.elements[queue.head];
        queue.head = (queue.head + 1) % queue.elements.length;
        queue.size--;
        return toReturn;
    }
    //post: R = a[0] && new_size = old_size - 1 &&
    //      for any element except a[0]: new_element == prev_element

    //pre: size > 0 && queue != null
    public static Object element(ArrayQueueADT queue) {
        assert queue.size > 0;
        assert queue != null;

        return queue.elements[queue.head];
    }
    //post: R = a[0] && queue is immutable

    //pre: queue != null
    public static int size(ArrayQueueADT queue) {
        assert queue != null;
        return queue.size;
    }
    //post: R = size && queue is immutable

    //pre: queue != null
    public static boolean isEmpty(ArrayQueueADT queue) {
        assert queue != null;
        return queue.size == 0;
    }
    //post: (R = true && size == 0 || R = false && size > 0) && queue is immutable

    //pre: queue != null
    public static void clear(ArrayQueueADT queue) {
        assert queue != null;
        queue.head = queue.size = 0;
    }
    //post: new_size = 0

    public static Object[] toArray(ArrayQueueADT queue) {
        Object[] toReturn = new Object[queue.size];
        if (queue.head + queue.size > queue.elements.length) {
            System.arraycopy(queue.elements, queue.head, toReturn, 0, queue.elements.length - queue.head );
            System.arraycopy(queue.elements, 0, toReturn, queue.elements.length - queue.head, queue.size - (queue.elements.length - queue.head));
        } else {
            System.arraycopy(queue.elements, queue.head, toReturn, 0, queue.size);
        }
        return toReturn;
    }

    //pre: queue != null
    public static String toStr(ArrayQueueADT queue) {
        return Arrays.toString(toArray(queue));
    }
    //post: R = "[" + a[0] + "," + … + "," +  a[size - 1] + "]"
}
