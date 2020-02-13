package expression;

import expression.exceptions.EvaluateException;

import java.util.List;

public class RightShift extends AbstractOperation {
    public RightShift(CommonExpression left, CommonExpression right) {
        super(left, right, ">>");
    }

    @Override
    public int evaluate(int x) throws EvaluateException {
        return evaluate(x, 0, 0);
    }

    @Override
    public int evaluate(int x, int y, int z) throws EvaluateException {
        return left.evaluate(x, y, z) >> right.evaluate(x, y, z);
    }
}

