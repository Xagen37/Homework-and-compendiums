package queue;

public class LinkedQueue extends AbstractQueue {
    private class Node {
        Object value;
        Node next;

        public Node(Object value) {
            this.value = value;
            this.next = null;
        }
    }


    private Node head;
    private Node tail;

    @Override
    public void enqueue(Object element) {
        checkEnqueue(element);
        if (head == null){
            head = new Node(element);
            tail = head;
        } else {
            tail.next = new Node(element);
            tail = tail.next;
        }
    }

    @Override
    public Object dequeue() {
        checkDequeue();
        Object value = head.value;
        head = head.next;
        if (head == null) {
            tail = null;
        }
        return value;
    }

    @Override
    public Object element() {
        checkElement();
        return head.value;
    }

    @Override
    public void clear() {
        nullifySize();
        head = null;
    }

    @Override
    public Object[] toArray() {
        Object[] toReturn = new Object[size];
        Node curr = head;
        for (int i = 0; i < size; i++, curr = curr.next) {
            toReturn[i] = curr.value;
        }
        return toReturn;
    }
}
