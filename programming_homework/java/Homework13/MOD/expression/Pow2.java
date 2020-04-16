package expression;

import expression.exceptions.EvaluateException;
import expression.exceptions.NegativeArgumentException;
import expression.exceptions.OverflowException;

import java.util.List;

public class Pow2 extends UnaryOperation {
    public Pow2(List<CommonExpression> innerUnits) {
        super(innerUnits, "pow2");
    }

    public Pow2(CommonExpression value) {
        super(value,  "pow2");
    }

    @Override
    public int evaluate(int x) throws EvaluateException {
        return evaluate(x, 0, 0);
    }

    @Override
    public int evaluate(int x, int y, int z) throws EvaluateException {
        if (innerUnits.size() == 0) {
            throw new NegativeArgumentException("Illegal operation: pow has no arguments");
        } else {
            int arg = innerUnits.get(0).evaluate(x, y, z);
            if (arg < 0) {
                throw new NegativeArgumentException("Illegal operation: pow can't have negative arguments");
            } else {
                int answer = 1;
                for (int i = 0; i < arg; i++) {
                    if (answer > Integer.MAX_VALUE / 2) {
                        throw new OverflowException("Overflowed: pow2 " + arg);
                    }
                    answer *= 2;
                }
                return answer;
            }
        }
    }
}
