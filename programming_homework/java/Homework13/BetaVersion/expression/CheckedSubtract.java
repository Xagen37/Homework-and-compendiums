package expression;

import expression.exceptions.EvaluateException;
import expression.exceptions.OverflowException;

import java.util.List;

public class CheckedSubtract extends AbstractOperation {
    public CheckedSubtract(CommonExpression left, CommonExpression right) {
        super(left, right, "-");
    }

    @Override
    public int evaluate(int x) throws EvaluateException {
        return evaluate(x, 0, 0);
    }

    @Override
    public int evaluate(int x, int y, int z) throws EvaluateException {
        int res = left.evaluate(x, y, z);
        int toAdd = right.evaluate(x, y, z);
        if (toAdd >= 0 && (Integer.MIN_VALUE + toAdd <= res) ||
                toAdd < 0 && (Integer.MAX_VALUE + toAdd >= res)) {
            res -= toAdd;
        } else {
            throw new OverflowException("Overflowed: " + res + " - " + toAdd);
        }
        return res;
    }
}
