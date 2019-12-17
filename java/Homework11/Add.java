package expression;

import java.util.List;

public class Add extends AbstractOperation {
    public Add(List<CommonExpression> innerUnits) {
        super(innerUnits, "+");
    }

    public Add(CommonExpression left, CommonExpression right) {
        super(left, right, "+");
    }

    @Override
    public int evaluate(int x) {
        return evaluate(x, 0, 0);
    }

    @Override
    public double evaluate(double x) {
        double res = 0;
        for(CommonExpression unit: innerUnits) {
            res += unit.evaluate(x);
        }
        return res;
    }

    @Override
    public int evaluate(int x, int y, int z) {
        int res = 0;
        for(CommonExpression unit: innerUnits) {
            res += unit.evaluate(x, y, z);
        }
        return res;
    }
}
