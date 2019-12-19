package expression;

import java.util.List;

public class Divide extends AbstractOperation {
    public Divide(CommonExpression left, CommonExpression right) {
        super(left, right, "/");
    }

    @Override
    public int evaluate(int x) {
        return evaluate(x, 0, 0);
    }

    @Override
    public int evaluate(int x, int y, int z) {
            return left.evaluate(x, y, z) / right.evaluate(x, y, z);
    }

    @Override
    public double evaluate(double x) {
        return left.evaluate(x) / right.evaluate(x);
    }
}
