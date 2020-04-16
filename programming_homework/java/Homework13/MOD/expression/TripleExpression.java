package expression;

import expression.exceptions.EvaluateException;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public interface TripleExpression extends ToMiniString {
    int evaluate(int x, int y, int z) throws EvaluateException;
}