package expression;

import expression.exceptions.DivisionByZeroException;
import expression.exceptions.EvaluateException;
import expression.exceptions.OverflowException;

import java.util.List;

public class CheckedDivide extends BinaryOperation {
    public CheckedDivide(List<CommonExpression> innerUnits) {
        super(innerUnits, "/");
    }

    public CheckedDivide(CommonExpression left, CommonExpression right) {
        super(left, right, "/");
    }

    @Override
    public int evaluate(int x) throws EvaluateException {
        return evaluate(x, 0, 0);
    }

    @Override
    public int evaluate(int x, int y, int z) throws EvaluateException {
        if (innerUnits.isEmpty()) {
            return 0;
        } else {
            int res = innerUnits.get(0).evaluate(x, y, z);
            for (int i = 1; i < innerUnits.size(); i++) {
                int denominator = innerUnits.get(i).evaluate(x, y, z);
                if (denominator == 0) {
                    throw new DivisionByZeroException("Division by zero");
                }
                if (res == Integer.MIN_VALUE && denominator == -1) {
                    throw new OverflowException("Overflowed: " + res + " / " + denominator);
                }
                res /= denominator;
            }
            return res;
        }
    }
}
