package expression;

public interface CommonExpression extends Expression, DoubleExpression, TripleExpression {
    boolean equals(Object obj);
    String toString();
    int hashCode();
}
