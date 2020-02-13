package expression;

import expression.exceptions.EvaluateException;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public strictfp interface DoubleExpression extends ToMiniString {
    double evaluate(double x) throws EvaluateException;
}
