import kotlinx.atomicfu.*

class FAAQueue<T> {
    private val head: AtomicRef<Segment> // Head pointer, similarly to the Michael-Scott queue (but the first node is _not_ sentinel)
    private val tail: AtomicRef<Segment> // Tail pointer, similarly to the Michael-Scott queue

    init {
        val firstNode = Segment()
        head = atomic(firstNode)
        tail = atomic(firstNode)
    }

    /**
     * Adds the specified element [x] to the queue.
     */
    fun enqueue(x: T) {
        while (true) {
            val currTail = this.tail.value
            val enq = currTail.enqIdx.getAndIncrement()
            if (enq >= SEGMENT_SIZE) {
                val nextTail = Segment(x)
                if (currTail.next.compareAndSet(null, nextTail)) {
                    this.tail.compareAndSet(currTail, nextTail)
                    return
                } else {
                    val newTail = currTail.next.value ?: continue
                    this.tail.compareAndSet(currTail, newTail)
                }
            } else {
                if (currTail.elements[enq].compareAndSet(null, x)) { return }
            }
        }
    }

    /**
     * Retrieves the first element from the queue
     * and returns it; returns `null` if the queue
     * is empty.
     */
    fun dequeue(): T? {
        while (true) {
            val currHead = this.head.value
            val deq = currHead.deqIdx.getAndIncrement()
            if (deq >= SEGMENT_SIZE) {
                val nextHead = currHead.next.value ?: return null
                this.head.compareAndSet(currHead, nextHead)
                continue
            }
            val res = currHead.elements[deq].getAndSet(DONE) ?: continue
            return res as T?
        }
    }

    /**
     * Returns `true` if this queue is empty;
     * `false` otherwise.
     */
    val isEmpty: Boolean get() {
        while (true) {
            if (head.value.isEmpty) {
                if (head.value.next.value == null) return true
                head.value = head.value.next.value!!
                continue
            } else {
                return false
            }
        }
    }
}

private class Segment {
    val next: AtomicRef<Segment?> = atomic(null)
    val enqIdx = atomic(0) // index for the next enqueue operation
    val deqIdx = atomic(0) // index for the next dequeue operation
    val elements = atomicArrayOfNulls<Any>(SEGMENT_SIZE)

    constructor() // for the first segment creation

    constructor(x: Any?) { // each next new segment should be constructed with an element
        enqIdx.getAndSet(1)
        elements[0].value = x
    }

    val isEmpty: Boolean get() {
        val deq = deqIdx.value
        val enq = enqIdx.value
        return deq >= enq || deq >= SEGMENT_SIZE
    }

}

private val DONE = Any() // Marker for the "DONE" slot state; to avoid memory leaks
const val SEGMENT_SIZE = 2 // DO NOT CHANGE, IMPORTANT FOR TESTS

