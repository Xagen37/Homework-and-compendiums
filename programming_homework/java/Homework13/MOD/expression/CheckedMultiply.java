package expression;

import expression.exceptions.EvaluateException;
import expression.exceptions.OverflowException;

import java.util.List;

public class CheckedMultiply extends BinaryOperation {
    public CheckedMultiply(List<CommonExpression> innerUnits) {
        super(innerUnits, "*");
    }

    public CheckedMultiply(CommonExpression left, CommonExpression right) {
        super(left, right, "*");
    }

    @Override
    public int evaluate(int x) throws EvaluateException {
        return evaluate(x, 0, 0);
    }

    @Override
    public int evaluate(int x, int y, int z) throws EvaluateException {
        int res = 1;
        for (CommonExpression unit: innerUnits) {
            int toAdd = unit.evaluate(x, y, z);
            if (res == 0 || toAdd == 0 ||
               (res * toAdd / toAdd == res) &&
               !(res == Integer.MIN_VALUE && toAdd == -1) &&
               !(res == -1 && toAdd == Integer.MIN_VALUE)) {
                res *= toAdd;
            } else {
                throw new OverflowException("Overflowed: " + res + " * " + toAdd);
            }
        }
        return res;
    }
}
