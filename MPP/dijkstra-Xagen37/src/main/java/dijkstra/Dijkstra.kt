package dijkstra

import java.util.*
import java.util.concurrent.Phaser
import java.util.concurrent.atomic.AtomicInteger
import java.util.concurrent.locks.ReentrantLock
import kotlin.Comparator
import kotlin.concurrent.thread
import kotlin.random.Random

private val NODE_DISTANCE_COMPARATOR = Comparator<Node> { o1, o2 -> Integer.compare(o1!!.distance, o2!!.distance) }

// Returns `Integer.MAX_VALUE` if a path has not been found.
fun shortestPathParallel(start: Node) {
    val workers = Runtime.getRuntime().availableProcessors()
    // The distance to the start node is `0`
    start.distance = 0
    // Create a priority (by distance) queue and add the start node into it
    val q = PriorityMultiQueue(workers, NODE_DISTANCE_COMPARATOR)
    q.add(start)
    // Run worker threads and wait until the total work is done
    val onFinish = Phaser(workers + 1) // `arrive()` should be invoked at the end by each worker
    val activeNodes = AtomicInteger(1)
    repeat(workers) {
        thread {
            while (activeNodes.get() > 0) {
                val cur: Node = q.poll() ?: continue
                for (e in cur.outgoingEdges) {
                    while (true) {
                        val new = cur.distance + e.weight
                        val prev = e.to.distance
                        if (new >= prev) {
                            break
                        } else if (e.to.casDistance(prev, new)) {
                            q.add(e.to)
                            activeNodes.incrementAndGet()
                            break
                        }
                    }
                }
                activeNodes.decrementAndGet()
            }
            onFinish.arrive()
        }
    }
    onFinish.arriveAndAwaitAdvance()
}

class PriorityMultiQueue<E>(workers: Int, private val comparator: java.util.Comparator<in E>) {
    class QueueWithLock<E>(comparator: java.util.Comparator<in E>) {
        val queue = PriorityQueue(comparator)
        val lock = ReentrantLock()
    }
    private val queues = Array(2 * if (workers == 0) 1 else workers) { QueueWithLock(comparator) }
    private var size = 0

    fun size(): Int {
        return size
    }

    val isEmpty: Boolean
        get() = size == 0

    fun add(e: E) {
        var q: Int
        do {
            q = Random.nextInt(queues.size)
        } while (!queues[q].lock.tryLock())

        queues[q].queue.add(e)
        size++
        queues[q].lock.unlock()
    }

    fun poll(): E? {
        var q1: Int
        var q2: Int
        while (true) {
            var n1: Int
            var n2: Int
            do {
                n1 = Random.nextInt(queues.size)
                n2 = Random.nextInt(queues.size)
            } while (n1 == n2)

            if (n1 < n2) {
                q1 = n1.also { q2 = n2 }
            } else {
                q1 = n2.also { q2 = n1 }
            }

            if (queues[q1].lock.tryLock()) {
                if (queues[q2].lock.tryLock()) {
                    break
                } else {
                    queues[q1].lock.unlock()
                }
            }
        }

        val first = queues[q1]
        val second = queues[q2]
        val e1 = first.queue.peek()
        val e2 = second.queue.peek()
        val ret: E = if (e1 != null && (e2 == null || comparator.compare(e1, e2) < 0)) {
            first.queue.poll()
        } else {
            second.queue.poll()
        }
        if (ret != null)
            size--

        queues[q1].lock.unlock()
        queues[q2].lock.unlock()
        return ret
    }
}