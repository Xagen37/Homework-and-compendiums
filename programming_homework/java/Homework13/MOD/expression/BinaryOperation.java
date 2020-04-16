package expression;

import java.util.List;

public abstract class BinaryOperation extends AbstractOperation {
    public BinaryOperation(List<CommonExpression> innerUnits, String type) {
        super(innerUnits, type);
    }

    public BinaryOperation(CommonExpression left, CommonExpression right, String type) {
        super(left, right, type);
    }

    @Override
    public String toString() {
        if (innerUnits.isEmpty()) {
            return "";
        } else {
            StringBuilder toReturn = new StringBuilder();
            toReturn.append('(');
            toReturn.append(innerUnits.get(0).toString());
            for (int i = 1; i < innerUnits.size(); i++) {
                toReturn.append(" ").append(type).append(" ");
                toReturn.append(innerUnits.get(i).toString());
            }
            toReturn.append(')');
            return toReturn.toString();
        }
    }
}