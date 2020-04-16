package expression;

public class Const implements CommonExpression {
    private double doubleValue;
    private int intValue;
    private final boolean flag;

    public Const(double value) {
        this.doubleValue = value;
        flag = true;
    }

    public Const(int value) {
        this.intValue = value;
        flag = false;
    }



    @Override
    public int evaluate(int x) {
        return evaluate(x, 0, 0);
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return flag ? (int)doubleValue : intValue;
    }

   /* @Override
    public double evaluate(double x) {
        return flag ? doubleValue : intValue;
    }*/

    @Override
    public String toString() {
        if (flag) {
            return Double.toString(doubleValue);
        } else {
            return Integer.toString(intValue);
        }
    }

    @Override
    public int hashCode() {
        if (flag) {
            return (int)doubleValue;
        } else {
            return intValue;
        }
    }

    @Override
    public boolean equals(Object obj) {
        if (obj != null && this.getClass().equals(obj.getClass())) {
            Const other = (Const)obj;
            if (this.flag == other.flag) {
              return (flag) ? (this.doubleValue == other.doubleValue) : (this.intValue == other.intValue);
            } else {
                return false;
            }
        }
        return false;
    }
}
