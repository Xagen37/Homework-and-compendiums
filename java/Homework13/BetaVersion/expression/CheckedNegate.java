package expression;

import expression.exceptions.EvaluateException;
import expression.exceptions.OverflowException;

import java.util.List;

public class CheckedNegate extends AbstractOperation {
    public CheckedNegate(CommonExpression value) {
        super(value, new Const(Integer.MAX_VALUE), "-");
    }

    @Override
    public String toString() {
        StringBuilder toReturn = new StringBuilder();
        toReturn.append(type).append('(');
        toReturn.append(left.toString());
        toReturn.append(')');
        return toReturn.toString();
    }

    @Override
    public int evaluate(int x) throws EvaluateException {
        return evaluate(x, 0, 0);
    }

    @Override
    public int evaluate(int x, int y, int z) throws EvaluateException {
        int toAdd = left.evaluate(x, y, z);
        if (toAdd == Integer.MIN_VALUE) {
            throw new OverflowException("Overflowed: -" + toAdd);
        } else {
            return -toAdd;
        }
    }
}
