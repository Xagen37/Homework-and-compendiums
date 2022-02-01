import kotlinx.atomicfu.*

class DynamicArrayImpl<E> : DynamicArray<E> {
    private val core = atomic(Core<E>(INITIAL_CAPACITY, 0))
    private val next: AtomicRef<Core<E>?> = atomic(null)

    override fun get(index: Int): E {
        val currCore = core.value
        val currSize = currCore.size()
        if (index >= currSize || index < 0) {
            throw IllegalArgumentException("Index $index out of bounds for array of size $currSize")
        }
        return currCore.array[index].value!!.elem
    }

    override fun put(index: Int, element: E) {
        val newNode = Core.Node(element)
        while (true) {
            val currCore = core.value
            val currSize = currCore.size()
            if (index >= currSize || index < 0) {
                throw IllegalArgumentException("Index $index out of bounds for array of size $currSize")
            }

            val currVal = currCore.array[index].value
            if (currVal !is Core.Removed) {
                if (currCore.array[index].compareAndSet(currVal, newNode))
                    return
            }
        }
    }

    override fun pushBack(element: E) {
        val newNode = Core.Node(element)
        while (true) {
            val currCore = core.value
            val currSize = currCore.size()
            if (currSize == currCore.capacity) {
                resize(currCore)
            } else {
                if (currCore.array[currSize].compareAndSet(null, newNode)) {
                    currCore.size.compareAndSet(currSize, currSize + 1)     // may fail if we've been helped
                    return
                } else {
                    currCore.size.compareAndSet(currSize, currSize + 1)
                }
            }
        }
    }

    private fun resize(prevCore: Core<E>) {
        val prevSize = prevCore.capacity
        val newCore = Core<E>(prevSize * 2, prevSize)
        if (next.compareAndSet(null, newCore)) {
            for (i in 0 until prevSize) {
                while(true) {
                    val currVal = prevCore.array[i].value!!
                    val removed = Core.Removed(currVal)
                    if (prevCore.array[i].compareAndSet(currVal, removed)) {
                        newCore.array[i].compareAndSet(null, Core.Node(currVal.elem))
                        break
                    }
                }
            }
            core.compareAndSet(prevCore, newCore)
            next.compareAndSet(newCore, null)
        }
    }

    override val size: Int
        get() {
            return core.value.size()
        }
}

private class Core<E>(
    val capacity: Int,
    currSize: Int,
) {
    val array = atomicArrayOfNulls<Node<E>>(capacity)
    val size = atomic(currSize)     // "tail", i.e. pointer to the next unused position

    fun size(): Int {
        return size.value
    }

    open class Node<E>(val elem: E) {
        constructor(node: Node<E>) : this(node.elem)
    }

    class Removed<E>(node: Node<E>) : Node<E>(node)
}

private const val INITIAL_CAPACITY = 1 // DO NOT CHANGE ME