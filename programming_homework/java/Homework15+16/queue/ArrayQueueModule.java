package queue;

import java.util.Arrays;

//inv: size >= 0
//     for any element in queue: element != null
public class ArrayQueueModule {
    private static int head = 0, size = 0;
    private static Object[] elements = new Object[10];

    //pred: elem != null
    public static void enqueue(Object element) {
        assert (element != null);
        ensureCapacity(size + 1);
        elements[(head + size) % elements.length] = element;
        size++;
    }
    //post: new_size = prev_size + 1 &&
    //      for any element in queue: new_element == prev_element &&
    //      a[prev_size] = elem

    private static void ensureCapacity(int capacity) {
        if (capacity <= elements.length) {
            return;
        }
        Object[] newElements = new Object[2 * capacity];
        if (head + size > elements.length) {
            System.arraycopy(elements, head, newElements, 0, elements.length - head );
            System.arraycopy(elements, 0, newElements, elements.length - head, head);
        } else {
            System.arraycopy(elements, head, newElements, 0, size);
        }
        elements = newElements;
        head = 0;
        /*Object[] newElements = new Object[2 * capacity];
        for (int i = 0; i < size; i++) {
            newElements[i] = elements[(head + i) % size];
        }
        elements = newElements;
        head = 0;*/
    }
    //post: new_capacity = 2 * old_capacity && queue is immutable

    //pred: size > 0
    public static Object dequeue() {
        assert size > 0;

        Object toReturn = elements[head];
        head = (head + 1) % elements.length;
        size--;
        return toReturn;
    }
    //post: R = a[0] && new_size = old_size - 1 &&
    //      for any element except a[0]: new_element == prev_element

    //pre: size > 0
    public static Object element() {
        assert size > 0;

        return elements[head];
    }
    //post: R = a[0] && queue is immutable

    public static int size() {
        return size;
    }
    //post: R = size && queue is immutable

    public static boolean isEmpty() {
        return size == 0;
    }
    //post: (R = true && size == 0 || R = false && size > 0) && queue is immutable

    public static void clear() {
        head = size = 0;
    }
    //post: new_size = 0

    public static Object[] toArray() {
        Object[] toReturn = new Object[size];
        if (head + size > elements.length) {
            System.arraycopy(elements, head, toReturn, 0, elements.length - head );
            System.arraycopy(elements, 0, toReturn, elements.length - head, size - (elements.length - head));
        } else {
            System.arraycopy(elements, head, toReturn, 0, size);
        }
        return toReturn;
    }

    public static String toStr() {
        return Arrays.toString(toArray());
    }
    //post: R = "[" + a[0] + "," + … + "," +  a[size - 1] + "]"
}
