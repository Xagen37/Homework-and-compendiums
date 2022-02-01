import java.util.concurrent.locks.ReentrantLock;

/**
 * Bank implementation.
 *
 * @author Sofrygin Alexander
 */
public class BankImpl implements Bank {
    /**
     * An array of accounts by index.
     */
    private final Account[] accounts;

    /**
     * Creates new bank instance.
     * @param n the number of accounts (numbered from 0 to n-1).
     */
    public BankImpl(int n) {
        accounts = new Account[n];
        for (int i = 0; i < n; i++) {
            accounts[i] = new Account();
        }
    }

    @Override
    public int getNumberOfAccounts() {
        return accounts.length;
    }

    @Override
    public long getAmount(int index) {
        accounts[index].lock.lock();
        long returnValue = accounts[index].amount;
        accounts[index].lock.unlock();
        return returnValue;
    }

    @Override
    public long getTotalAmount() {
        long sum = 0;
        for (Account account : accounts)
            account.lock.lock();
        for (Account account : accounts)
            sum += account.amount;
        for (Account account : accounts)
            account.lock.unlock();
        return sum;
    }

    @Override
    public long deposit(int index, long amount) {
        if (amount <= 0)
            throw new IllegalArgumentException("Invalid amount: " + amount);
        Account account = accounts[index];
        account.lock.lock();
        if (amount > MAX_AMOUNT || account.amount + amount > MAX_AMOUNT) {
            account.lock.unlock();
            throw new IllegalStateException("Overflow");
        }
        account.amount += amount;
        long returnValue = account.amount;
        account.lock.unlock();
        return returnValue;
    }

    @Override
    public long withdraw(int index, long amount) {
        if (amount <= 0)
            throw new IllegalArgumentException("Invalid amount: " + amount);

        Account account = accounts[index];
        account.lock.lock();
        if (account.amount - amount < 0) {
            account.lock.unlock();
            throw new IllegalStateException("Underflow");
        }

        account.amount -= amount;
        long returnValue = account.amount;
        account.lock.unlock();
        return returnValue;
    }

    @Override
    public void transfer(int fromIndex, int toIndex, long amount) {
        if (amount <= 0)
            throw new IllegalArgumentException("Invalid amount: " + amount);
        if (fromIndex == toIndex)
            throw new IllegalArgumentException("fromIndex == toIndex");

        Account from = accounts[fromIndex];
        Account to = accounts[toIndex];
        int minIndex = Math.min(fromIndex, toIndex);
        int maxIndex = Math.max(fromIndex, toIndex);
        accounts[minIndex].lock.lock();
        accounts[maxIndex].lock.lock();

        try {
            if (amount > from.amount) {
                throw new IllegalStateException("Underflow");
            } else if (amount > MAX_AMOUNT || to.amount + amount > MAX_AMOUNT) {
                throw new IllegalStateException("Overflow");
            }

            from.amount -= amount;
            to.amount += amount;
        } finally {
            accounts[minIndex].lock.unlock();
            accounts[maxIndex].lock.unlock();
        }
    }

    /**
     * Private account data structure.
     */
    static class Account {
        /**
         * Amount of funds in this account.
         */
        long amount;
        /**
         * This account's lock
         */
        ReentrantLock lock = new ReentrantLock();
    }
}
