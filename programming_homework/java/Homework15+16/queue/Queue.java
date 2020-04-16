package queue;

//inv: size >= 0
//     for any element in queue: element != null
public interface Queue {

    //pred: elem != null
    public void enqueue(Object element);
    //post: new_size = prev_size + 1 &&
    //      for any element in queue: new_element == prev_element &&
    //      a[prev_size] = elem

    //pred: size > 0
    public Object dequeue();
    //post: R = a[0] && new_size = old_size - 1 &&
    //      for any element except a[0]: new_element == prev_element

    //pre: size > 0
    public Object element();
    //post: R = a[0] && queue is immutable

    public int size();
    //post: R = size && queue is immutable

    public boolean isEmpty();
    //post: (R = true && size == 0 || R = false && size > 0) && queue is immutable

    public void clear();
    //post: new_size = 0

    public Object[] toArray();
    //post: queue is immutable && R = [a[0], a[1], ... , a[size - 1]]
}
