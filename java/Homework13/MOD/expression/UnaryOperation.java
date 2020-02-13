package expression;

import java.util.List;

public abstract class UnaryOperation extends AbstractOperation {
    public UnaryOperation(List<CommonExpression> innerUnits, String type) {
        super(innerUnits, type);
    }

    public UnaryOperation(CommonExpression value, String type) {
        super(List.of(value), type);
    }

    protected CommonExpression front() {
        return (innerUnits.size() == 0) ? null : innerUnits.get(0);
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
}
