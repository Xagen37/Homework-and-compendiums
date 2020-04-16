package expression;

import expression.exceptions.EvaluateException;
import expression.exceptions.OverflowException;

import java.util.List;

public class CheckedSubtract extends BinaryOperation {
    public CheckedSubtract(List<CommonExpression> innerUnits) {
        super(innerUnits, "-");
    }

    public CheckedSubtract(CommonExpression left, CommonExpression right) {
        super(left, right, "-");
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
                int toAdd = innerUnits.get(i).evaluate(x, y, z);
                if (toAdd >= 0 && (Integer.MIN_VALUE + toAdd <= res) ||
                    toAdd < 0 && (Integer.MAX_VALUE + toAdd >= res)) {
                    res -= toAdd;
                } else {
                    throw new OverflowException("Overflowed: " + res + " - " + toAdd);
                }
            }
            return res;
        }
    }
}
