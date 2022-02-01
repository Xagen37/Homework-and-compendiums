import kotlinx.atomicfu.*
import java.util.*

private const val FC_SIZE = 32
class FCPriorityQueue<E : Comparable<E>> {
    private val q = PriorityQueue<E>()
    private val lock = atomic(false)

    private enum class OP {
        POLL, PEEK, ADD, DONE, PROGRESS
    }
    private class Node<E> (val op: OP, var elem: E?)
    private val fcArray = atomicArrayOfNulls<Node<E>>(FC_SIZE)

    /**
     * Retrieves the element with the highest priority
     * and returns it as the result of this function;
     * returns `null` if the queue is empty.
     */
    fun poll(): E? {
        while(true) {
            return if (lock.compareAndSet(expect = false, update = true)) {
                val retVal = q.poll()
                traverseFC()
                lock.getAndSet(false)
                retVal
            } else {
                val task = Node<E>(op = OP.POLL, elem = null)
                val answ = putTask(task) ?: continue
                answ.elem
            }
        }
    }

    /**
     * Returns the element with the highest priority
     * or `null` if the queue is empty.
     */
    fun peek(): E? {
        while(true) {
            return if (lock.compareAndSet(expect = false, update = true)) {
                val retVal = q.peek()
                traverseFC()
                lock.getAndSet(false)
                retVal
            } else {
                val task = Node<E>(op = OP.PEEK, elem = null)
                val answ = putTask(task) ?: continue
                answ.elem
            }
        }
    }

    /**
     * Adds the specified element to the queue.
     */
    fun add(element: E) {
        while(true) {
            if (lock.compareAndSet(expect = false, update = true)) {
                q.add(element)
                traverseFC()
                lock.getAndSet(false)
            } else {
                val task = Node(op = OP.ADD, elem = element)
                putTask(task) ?: continue
            }
            return
        }
    }

    private fun traverseFC() {
        for (i in 0 until FC_SIZE) {
            val task = fcArray[i].value?: continue
            if (task.op == OP.DONE)
                continue
            if (!fcArray[i].compareAndSet(task, Node(op = OP.PROGRESS, elem = null)))
                continue

            val answ = Node<E>(op = OP.DONE, elem = null)
            answ.elem = when(task.op) {
                OP.ADD -> { q.add(task.elem); null }
                OP.POLL -> q.poll()
                OP.PEEK -> q.peek()
                else -> continue // uncollected result or impossible
            }
            fcArray[i].getAndSet(answ)
        }
    }

    private fun putTask(task: Node<E>): Node<E>? {
        var id = -1
        while (true) {
            if (id == -1)
                for (i in 0 until FC_SIZE)
                    if (fcArray[i].value == null)
                        if (fcArray[i].compareAndSet(null, task)) {
                            id = i
                            break
                        }

            if (id != -1) {
                while (fcArray[id].value!!.op != OP.DONE && lock.value) {
                    for (i in 0 until 10000) {
                        /* wait */
                    }
                }

                if (!lock.value) {
                    if (fcArray[id].compareAndSet(task, null)) {
                        return null
                    }
                }

                if (fcArray[id].value!!.op == OP.DONE) {
                    val res = fcArray[id].value!!
                    fcArray[id].compareAndSet(res, null)
                    return res
                }
            }

            for (i in 0 until 10000) {
                /* wait */
            }
        }
    }
}