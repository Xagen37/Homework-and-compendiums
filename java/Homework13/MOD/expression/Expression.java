package expression;

import expression.exceptions.EvaluateException;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public interface Expression extends ToMiniString {
    int evaluate(int x) throws EvaluateException;
}
