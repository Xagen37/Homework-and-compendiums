package expression;

import java.util.List;

public class UnaryMinus extends AbstractOperation {
    public UnaryMinus(CommonExpression value) {
        super(List.of(value), "-");
    }

    @Override
    public String toString() {
        if (innerUnits.isEmpty()) {
            return "";
        } else {
            StringBuilder toReturn = new StringBuilder();
            toReturn.append(type).append('(');
            for (CommonExpression innerUnit : innerUnits) {
                toReturn.append(innerUnit.toString());
            }
            toReturn.append(')');
            return toReturn.toString();
        }
    }

    @Override
    public int evaluate(int x) {
        return evaluate(x, 0, 0);
    }

    @Override
    public double evaluate(double x) {
        return -x;
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return -(innerUnits.get(0).evaluate(x, y, z));
    }
}
