package expression.parser;

import expression.*;
import expression.exceptions.ParseException;

import java.util.ArrayList;
import java.util.List;

public class ExpressionParser implements Parser {

    @Override
    public CommonExpression parse(String expression) throws ParseException {
        return new Parse(expression).parseExpression(0);
    }

    private static class Parse extends BaseParser {
        public Parse(Source source) {
            super(source);
            nextChar();
        }

        public Parse(String toSource) {
            super(new StringSource(toSource));
            nextChar();
        }

        public CommonExpression parseExpression(int balance) throws ParseException {
            List<CommonExpression> operands = new ArrayList<>();
            List<Character> operators = new ArrayList<>();
            while (!test('\0')) {
                skipWhitespace();
                if (between('0', '9') || isVariable()) {
                    operands.add(parseTerm(false, operands.size() - operators.size()));
                } else if (test('(')) {
                    operands.add(parseExpression(balance + 1));
                } else if (test(')')) {
                    if (balance == 0) {
                        throwException("Illegal expression");
                    }
                    return wrap(operands, operators);
                } else if (test('<')) {
                    if (test('<')) {
                        operators.add('<');
                    } else {
                        throwException("Expected <<, got: <" + c);
                    }
                } else if (test('>')) {
                    if (test('>')) {
                        operators.add('>');
                    } else {
                        throwException("Expected >>, got: >" + c);
                    }
                } else {
                    if (operands.size() <= operators.size()) {
                        boolean isMinus = false;
                        while (c == '-') {
                            isMinus = !isMinus;
                            nextChar();
                            skipWhitespace();
                        }
                        CommonExpression value;
                        if (test('(')) {
                            value = (isMinus) ? new CheckedNegate(parseExpression(balance + 1)) : parseExpression(balance + 1);
                        } else if (between('0', '9') || isVariable()) {
                            value = parseTerm(isMinus, operands.size() - operators.size());
                        } else {
                            throwException("Expected \'(\' or a term, got: " + c);
                            value = null; //unreachable
                        }
                        operands.add(value);
                    } else {
                        if (isBasicOperation()) {
                            operators.add(c);
                            nextChar();
                        } else {
                            throwException("Cannot resolve symbol: " + c);
                        }
                    }
                }
                skipWhitespace();
            }
            if (operands.size() <= operators.size() || balance != 0) {
                throwException("Illegal expression");
            }
            return wrap(operands, operators);
        }

        private CommonExpression wrap(List<CommonExpression> operands, List<Character> operators) throws ParseException {
            if (operands.size() <= operators.size()) {
                throwException("Illegal expression");
            }
            List<CommonExpression> secondOrderOperands = new ArrayList<>();
            List<Character> secondOrderOperators = new ArrayList<>();
            secondOrderOperands.add(operands.get(0));
            for (int i = 0; i < operators.size(); i++) {
                if (operators.get(i).equals('*') || operators.get(i).equals('/')) {
                    secondOrderOperands.set(secondOrderOperands.size() - 1, operators.get(i).equals('*') ?
                            new CheckedMultiply(
                                    secondOrderOperands.get(secondOrderOperands.size() - 1), operands.get(i + 1)
                            ) :
                            new CheckedDivide(
                                    secondOrderOperands.get(secondOrderOperands.size() - 1), operands.get(i + 1)
                            )
                    );
                } else {
                    secondOrderOperands.add(operands.get(i + 1));
                    secondOrderOperators.add(operators.get(i));
                }
            }

            CommonExpression res = secondOrderOperands.get(0);
            for (int i = 0; i < secondOrderOperators.size(); i++) {
                res = secondOrderOperators.get(i).equals('+') ?
                        new CheckedAdd(
                                res, secondOrderOperands.get(i + 1)
                        ) :
                        new CheckedSubtract(
                                res, secondOrderOperands.get(i + 1)
                        );
            }
            return res;
        }

        private CommonExpression parseTerm(boolean withMinus, int difference) throws ParseException {
            if (difference >= 1) {
                throwException("Illegal expression");
            }
            return between('0', '9') ? parseConst(withMinus) : parseVariable(withMinus);
        }

        private CommonExpression parseVariable(boolean withMinus) {
            char name = c;
            nextChar();
            if(withMinus) {
                return new CheckedNegate(
                        new Variable(
                                Character.toString(name)
                        )
                );
            }
            return new Variable(Character.toString(name));
        }

        private CommonExpression parseConst(boolean withMinus) throws ParseException {
            StringBuilder sb = new StringBuilder();
            if (withMinus) {
                sb.append('-');
            }
            while (between('0', '9')) {
                sb.append(c);
                nextChar();
            }
            try {
                return new Const(Integer.parseInt(sb.toString()));
            } catch (NumberFormatException e) {
                throwException("Not parsable integer: " + sb);
                return  null; //unreachable
            }
        }
    }
}
