package expression;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public abstract class AbstractOperation implements CommonExpression {
    protected List<CommonExpression> innerUnits = new ArrayList<>();
    protected final String type;

    public AbstractOperation(List<CommonExpression> innerUnits, String type) {
        this.innerUnits = List.copyOf(innerUnits);
        this.type = type;
    }

    public AbstractOperation(CommonExpression left, CommonExpression right, String type) {
        this.type = type;
        innerUnits = List.of(left, right);
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

    @Override
    public boolean equals(Object obj) {
        if (obj != null && this.getClass().equals(obj.getClass())) {
            AbstractOperation other = (AbstractOperation)obj;
            return Objects.deepEquals(this.innerUnits, other.innerUnits);
        }
        return false;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        for (CommonExpression unit: innerUnits) {
            hash *= 239;
            hash += unit.hashCode() * 239;
            hash += this.type.hashCode();
        }
        return hash;
    }
}