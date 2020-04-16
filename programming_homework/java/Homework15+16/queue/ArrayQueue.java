package queue;

import java.util.Arrays;

public class ArrayQueue extends AbstractQueue {
    private int head = 0;
    private Object[] elements = new Object[10];


    public void enqueue(Object element) {
        checkEnqueue(element);//:NOTE: codestyle
        ensureCapacity(size);
        elements[(head + size - 1) % elements.length] = element;
    }


    private void ensureCapacity(int capacity) {
        if (capacity <= elements.length) {
            return;
        }
        Object[] newElements = new Object[2 * capacity];
        if (head + size > elements.length) {
            System.arraycopy(elements, head, newElements, 0, elements.length - head);
            System.arraycopy(elements, 0, newElements, elements.length - head, head);
        } else {
            System.arraycopy(elements, head, newElements, 0, size);
        }
        elements = newElements;
        head = 0;
    }
    //post: new_capacity = 2 * old_capacity && queue is immutable


    public Object dequeue() {
        checkDequeue();

        Object toReturn = elements[head];
        head = (head + 1) % elements.length;
        return toReturn;
    }



    public Object element() {
        checkElement();
        return elements[head];
    }

    public void clear() {
        nullifySize();
        head = size;
    }

    @Override
    public Object[] toArray() {
        Object[] toReturn = new Object[size];
        if (head + size >= elements.length) {
            System.arraycopy(elements, head, toReturn, 0, elements.length - head);
            System.arraycopy(elements, 0, toReturn, elements.length - head, size - (elements.length - head));
        } else {
            System.arraycopy(elements, head, toReturn, 0, size);
        }
        return toReturn;
    }

    public String toStr() {
       return Arrays.toString(toArray());
    }
    //post: R = "[" + a[0] + "," + … + "," +  a[size - 1] + "]"
}
