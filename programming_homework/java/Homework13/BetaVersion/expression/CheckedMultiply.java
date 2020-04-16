package expression;

import expression.exceptions.EvaluateException;
import expression.exceptions.OverflowException;

import java.util.List;

public class CheckedMultiply extends AbstractOperation {
    public CheckedMultiply(CommonExpression left, CommonExpression right) {
        super(left, right, "*");
    }

    @Override
    public int evaluate(int x) throws EvaluateException {
        return evaluate(x, 0, 0);
    }

    @Override
    public int evaluate(int x, int y, int z) throws EvaluateException {
        int res = left.evaluate(x, y, z);
        int toAdd = right.evaluate(x, y, z);
        if (res == 0 || toAdd == 0 ||
                (res * toAdd / toAdd == res) &&
                !(res == Integer.MIN_VALUE && toAdd == -1) &&
                !(res == -1 && toAdd == Integer.MIN_VALUE)) {
            res *= toAdd;
        } else {
            throw new OverflowException("Overflowed: " + res + " * " + toAdd);
        }
        return res;
    }

    private int sign(int val) {
        if (val == 0) {
            return 0;
        } else if (val > 0) {
            return 1;
        } else {
            return -1;
        }
    }

    /*@Override
    public double evaluate(double x) throws EvaluateException {
        double res = 1;
        for (CommonExpression unit: innerUnits) {
            double tryRes = res * unit.evaluate(x);
            res = checkDoubleOverflow(tryRes);
        }
        return res;
    }*/
}
