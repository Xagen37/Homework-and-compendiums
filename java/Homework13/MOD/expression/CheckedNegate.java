package expression;

import expression.exceptions.EvaluateException;
import expression.exceptions.OverflowException;

import java.util.List;

public class CheckedNegate extends UnaryOperation {
    public CheckedNegate(CommonExpression value) {
        super(value, "-");
    }

    @Override
    public int evaluate(int x) throws EvaluateException {
        return evaluate(x, 0, 0);
    }

    @Override
    public int evaluate(int x, int y, int z) throws EvaluateException {
        int toAdd = innerUnits.get(0).evaluate(x, y, z);
        if (toAdd == Integer.MIN_VALUE) {
            throw new OverflowException("Overflowed: -" + toAdd);
        } else {
            return -toAdd;
        }
    }
}
