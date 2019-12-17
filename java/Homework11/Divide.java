package expression;

import java.util.List;

public class Divide extends AbstractOperation {
    public Divide(List<CommonExpression> innerUnits) {
        super(innerUnits, "/");
    }

    public Divide(CommonExpression left, CommonExpression right) {
        super(left, right, "/");
    }

    @Override
    public int evaluate(int x) {
        return evaluate(x, 0, 0);
    }

    @Override
    public int evaluate(int x, int y, int z) {
        if (innerUnits.isEmpty()) {
            return 0;
        } else {
            int res = innerUnits.get(0).evaluate(x, y, z);
            for (int i = 1; i < innerUnits.size(); i++) {
                res /= innerUnits.get(i).evaluate(x, y, z);
            }
            return res;
        }
    }

    @Override
    public double evaluate(double x) {
        if (innerUnits.isEmpty()) {
            return 0;
        } else {
            double res = innerUnits.get(0).evaluate(x);
            for (int i = 1; i < innerUnits.size(); i++) {
                res /= innerUnits.get(i).evaluate(x);
            }
            return res;
        }
    }
}
