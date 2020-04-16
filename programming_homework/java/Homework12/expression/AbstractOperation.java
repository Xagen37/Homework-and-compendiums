package expression;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public abstract class AbstractOperation implements CommonExpression {
    protected CommonExpression left;
    protected CommonExpression right;
    protected final String type;

    public AbstractOperation(CommonExpression left, CommonExpression right, String type) {
        this.type = type;
        this.left = left;
        this.right = right;
    }

    @Override
    public String toString() {
        StringBuilder toReturn = new StringBuilder();
        toReturn.append('(');
        toReturn.append(left.toString());
        toReturn.append(" ").append(type).append(" ");
        toReturn.append(right.toString());
        toReturn.append(')');
        return toReturn.toString();
    }


    @Override
    public boolean equals(Object obj) {
        if (obj != null && this.getClass().equals(obj.getClass())) {
            AbstractOperation other = (AbstractOperation) obj;
            return Objects.equals(this.left, other.left) && Objects.equals(this.right, other.right);
        }
        return false;
    }

    @Override
    public int hashCode() {
        int hash = left.hashCode();
        hash *= 239;
        hash += this.type.hashCode();
        hash *= 239;
        hash += right.hashCode();
        return hash;
    }

    protected int abs(int val) {
        if (val >= 0) {
            return val;
        } else {
            return -val;
        }
    }
}