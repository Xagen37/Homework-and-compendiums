import kotlinx.atomicfu.AtomicRef
import kotlinx.atomicfu.atomic
import kotlin.coroutines.Continuation
import kotlin.coroutines.resume
import kotlin.coroutines.suspendCoroutine

class SynchronousQueueMS<E> : SynchronousQueue<E> {
    private val head: AtomicRef<Node<E>>
    private val tail: AtomicRef<Node<E>>

    init {
        val dummy = Node<E>(null, null)
        head = atomic(dummy)
        tail = atomic(dummy)
    }

    override suspend fun send(element: E) {
        loop@ while (true) {
            val currHead = head.value
            val currTail = tail.value
            if (currHead == currTail ||
                currTail.elem!!.inside != null
            ) {                                    // enqueue and suspend
                val res = suspendCoroutine<Any> sc@{ cont ->
                    val offer = Node(cont, Elem(element))
                    if (currTail.next.compareAndSet(null, offer)) {
                        tail.compareAndSet(currTail, offer)
                    } else {
                        tail.compareAndSet(currTail, currTail.next.value!!)
                        cont.resume(RETRY)
                        return@sc
                    }
                }
                if (res === RETRY) continue
                else return
            } else {                               // dequeue and resume
                val currNext = currHead.next.value!!
                if (head.compareAndSet(currHead, currNext)) {
                    currNext.cont!!.resume(element!!)
                    return
                }
            }
        }
    }

    override suspend fun receive(): E {
        loop@ while (true) {
            val currHead = head.value
            val currTail = tail.value
            if (currHead == currTail ||
                currTail.elem!!.inside == null
            ) {                                    // enqueue and suspend
                val res = suspendCoroutine<Any> sc@{ cont ->
                    val offer = Node(cont, Elem<E>(null))
                    if (currTail.next.compareAndSet(null, offer)) {
                        tail.compareAndSet(currTail, offer)
                    } else {
                        tail.compareAndSet(currTail, currTail.next.value!!)
                        cont.resume(RETRY)
                        return@sc
                    }
                }
                if (res === RETRY) continue
                else return res as E
            } else {                               // dequeue and resume
                val currNext = currHead.next.value!!
                if (head.compareAndSet(currHead, currNext)) {
                    val sender = currNext.cont!!
                    val elem = currNext.elem!!.inside!!
                    sender.resume(Unit)
                    return elem
                }
            }
        }
    }

    private class Elem<E>(val inside: E?)  // elem if sender or null if receiver
    private class Node<E>(
        val cont: Continuation<Any>?,      // null only if init
        val elem: Elem<E>?                 // null only if init
    ) {
        val next: AtomicRef<Node<E>?> = atomic(null)
    }

    private class RETRY_

    private val RETRY = RETRY_()
}
