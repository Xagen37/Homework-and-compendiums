import kotlinx.atomicfu.*

class AtomicArray<E>(size: Int, initialValue: E) {
    private val a = Array(size) { Ref(initialValue) }

    fun get(index: Int) =
        a[index].value

    fun set(index: Int, value: E) {
        a[index].value = value
    }

    fun cas(index: Int, expected: E, update: E): Boolean {
        while (true) {
            if (a[index].value != expected)
                return false
            if (a[index].v.compareAndSet(expected, update))
                return true
        }
    }

    fun cas2(
        index1: Int, expected1: E, update1: E,
        index2: Int, expected2: E, update2: E
    ): Boolean {
        if (index1 == index2)
            return if (expected1 == expected2)
                cas(index1, expected1, update2)
            else
                false

        val minRef: Ref<E>; val maxRef: Ref<E>
        val minExpected: E; val maxExpected: E
        val minUpdate:   E; val maxUpdate: E
        if (index1 <= index2) {
            minRef = a[index1]
            maxRef = a[index2]
            minExpected = expected1
            maxExpected = expected2
            minUpdate = update1
            maxUpdate = update2
        } else {
            minRef = a[index2]
            maxRef = a[index1]
            minExpected = expected2
            maxExpected = expected1
            minUpdate = update2
            maxUpdate = update1
        }

        while (true) {
            val desc = CAS2Descriptor(minRef, minExpected, minUpdate, maxRef, maxExpected, maxUpdate, maxRef.value)
            if (minRef.v.compareAndSet(minExpected, desc)) {
                desc.complete()

                return desc.result() == Descriptor.Outcome.SUCCESS
            } else {
                if (minRef.value != minExpected)
                    return false
            }
        }
    }
}

abstract class Descriptor {
    abstract fun complete()
    abstract fun result(): Outcome

    enum class Outcome {
        UNDECIDED, SUCCESS, FAIL
    }
}

class Ref<T>(initial: T) {
    val v = atomic<Any?>(initial)

    var value: T
        get() {
            while (true) {
                when (val curr = v.value) {
                    is Descriptor -> curr.complete()
                    else -> return curr as T
                }
            }
        }
        set(newVal) {
            while (true) {
                when (val curr = v.value) {
                    is Descriptor -> curr.complete()
                    else -> if (v.compareAndSet(curr, newVal)) return
                }
            }
        }
}

class RDCSSDescriptor<A, B>(
    private val a: Ref<A>, private val expectA: A, private val updateA: Any?,
    private val b: Ref<B>, private val expectB: B
) : Descriptor() {
    private val outcome = atomic(Outcome.UNDECIDED)

    override fun result(): Outcome {
        return outcome.value
    }

    override fun complete() {
        val currOutcome = outcome.value
        if (currOutcome == Outcome.UNDECIDED) {
            if (b.value === expectB) {
                outcome.compareAndSet(currOutcome, Outcome.SUCCESS)
            } else {
                outcome.compareAndSet(currOutcome, Outcome.FAIL)
            }
        }
        when (outcome.value) {
            Outcome.SUCCESS -> {
                a.v.compareAndSet(this, updateA)
            }
            Outcome.FAIL -> {
                a.v.compareAndSet(this, expectA)
            }
            else -> {
                assert(false) { "CAS2 outcome = undefined" }
            }
        }
    }


}

class CAS2Descriptor<A, B>(
    private val a: Ref<A>, private val expectA: A, private val updateA: A,
    private val b: Ref<B>, private val expectB: B, private val updateB: B, private val prevB: B
) : Descriptor() {

    private val outcome = Ref(Outcome.UNDECIDED)

    override fun result(): Outcome {
        return outcome.value
    }

    override fun complete() {
        while (outcome.value == Outcome.UNDECIDED) {
            val moveB = RDCSSDescriptor(b, expectB, this, outcome, Outcome.UNDECIDED)
            if (b.v.compareAndSet(expectB, moveB)) {
                moveB.complete()
                outcome.v.compareAndSet(Outcome.UNDECIDED, Outcome.SUCCESS)
            } else {
                val prev = b.v.value
                if (prev is Descriptor) {
                    if (prev != this) {
                        b.value
                        continue
                    }
                    outcome.v.compareAndSet(Outcome.UNDECIDED, Outcome.SUCCESS)
                } else if (prev != expectB) {
                    outcome.v.compareAndSet(Outcome.UNDECIDED, Outcome.FAIL)
                }
            }
        }
        when (outcome.value) {
            Outcome.SUCCESS -> {
                a.v.compareAndSet(this, updateA)
                b.v.compareAndSet(this, updateB)
            }
            Outcome.FAIL -> {
                a.v.compareAndSet(this, expectA)
                b.v.compareAndSet(this, prevB)
            }
            else -> {
                assert(false) { "CAS2 outcome = undefined" }
            }
        }
    }
}