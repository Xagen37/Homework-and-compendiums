/**
 * @author Sofrygin Alexander
 */

public class Solution implements AtomicCounter {
    final Node root = new Node(0);
    final ThreadLocal<Node> last = ThreadLocal.withInitial(() -> root);
    final ThreadLocal<Integer> my = ThreadLocal.withInitial(() -> 0);

    public int getAndAdd(int x) {
        final Node next_node = new Node(x);
        final ThreadLocal<Integer> res = new ThreadLocal<>();
        while(last.get() != next_node) {
            last.set(last.get().next.decide(next_node));
            res.set(my.get());
            my.set(my.get() + last.get().val);
        }
        return res.get();
    }

    // вам наверняка потребуется дополнительный класс
    private static class Node {
        final int val;
        final Consensus<Node> next = new Consensus<>();

        Node(int arg) {
            val = arg;
        }
    }
}
