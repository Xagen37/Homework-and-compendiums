package expression;

import expression.exceptions.*;

import java.util.List;

public class Log2 extends UnaryOperation {
    public Log2(List<CommonExpression> innerUnits) {
        super(innerUnits, "log2");
    }

    public Log2(CommonExpression value) {
        super(value, "log2");
    }

    @Override
    public int evaluate(int x) throws EvaluateException {
        return evaluate(x, 0, 0);
    }

    @Override
    public int evaluate(int x, int y, int z) throws EvaluateException {
        if (front() == null) {
            throw new NegativeArgumentException("Illegal operation: log has no arguments");
        } else {
            int arg = front().evaluate(x, y, z);
            if (arg <= 0) {
                throw new NegativeArgumentException("Illegal operation: log can't have negative argument");
            } else {
                int answer = 0;
                int multiplyResult = 1;
                while (multiplyResult <= arg) {
                    if (multiplyResult > Integer.MAX_VALUE / 2) {
                        answer++;
                        break;
                    }
                    answer++;
                    multiplyResult *= 2;
                }
                return answer - 1;
            }
        }
    }
}