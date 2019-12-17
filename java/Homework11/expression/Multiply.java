package expression;

import java.util.List;

public class Multiply extends AbstractOperation {
    public Multiply(List<CommonExpression> innerUnits) {
        super(innerUnits, "*");
    }

    public Multiply(CommonExpression left, CommonExpression right) {
        super(left, right, "*");
    }

    @Override
    public int evaluate(int x) {
        return evaluate(x, 0, 0);
    }

    @Override
    public int evaluate(int x, int y, int z) {
        int res = 1;
        for (CommonExpression unit: innerUnits) {
            res *= unit.evaluate(x, y, z);
        }
        return res;
    }

    @Override
    public double evaluate(double x) {
        double res = 1;
        for (CommonExpression unit: innerUnits) {
            res *= unit.evaluate(x);
        }
        return res;
    }
}
