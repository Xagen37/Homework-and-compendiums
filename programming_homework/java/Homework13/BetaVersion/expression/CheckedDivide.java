package expression;

import expression.exceptions.DivisionByZeroException;
import expression.exceptions.EvaluateException;
import expression.exceptions.OverflowException;

import java.util.List;

public class CheckedDivide extends AbstractOperation {
    public CheckedDivide(CommonExpression left, CommonExpression right) {
        super(left, right, "/");
    }

    @Override
    public int evaluate(int x) throws EvaluateException {
        return evaluate(x, 0, 0);
    }

    @Override
    public int evaluate(int x, int y, int z) throws EvaluateException {
        int res = left.evaluate(x, y, z);
        int denominator = right.evaluate(x, y, z);
        if (denominator == 0) {
            throw new DivisionByZeroException("Division by zero:" + res + " / " + 0);
        }
        if (res == Integer.MIN_VALUE && denominator == -1) {
            throw new OverflowException("Overflowed: " + res + " / " + denominator);
        }
        res /= denominator;
        return res;
    }
}
