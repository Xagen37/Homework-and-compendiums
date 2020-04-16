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
                        throwParseException(Exceptions.BRACKETS, "Not enough opening parenthesises");
                    }
                    return wrap(operands, operators);
                } else if (currentChar == 'l' || currentChar == 'p') {
                    operands.add(parseUnaryOperation(operands, operators, balance));
                } else {
                    if (operands.size() <= operators.size()) {
                        if (test('-')) {
                            operands.add(parseMinus(operands, operators, balance));
                        } else {
                            if (isBasicOperation()) {
                                throwParseException(Exceptions.ARGUMENT, "Didn't expect operation at pos " + pos());
                            }
                            throwParseException(Exceptions.SYNTAX, "Cannot resolve symbol: " + currentChar);
                        }
                    } else {
                        if (isBasicOperation()) {
                            operators.add(currentChar);
                            nextChar();
                        } else {
                            throwParseException(Exceptions.SYNTAX, "Cannot resolve symbol: " + currentChar);
                        }
                    }
                }
                skipWhitespace();
            }
            if (operands.size() <= operators.size()) {
                throwParseException(Exceptions.ARGUMENT, "Not enough arguments");
            }
            if (balance != 0) {
                throwParseException(Exceptions.BRACKETS, "Not enough closing parenthesises");
            }
            return wrap(operands, operators);
        }

        private CommonExpression wrap(List<CommonExpression> operands, List<Character> operators) throws ParseException {
            if (operands.size() <= operators.size()) {
                throwParseException(Exceptions.ARGUMENT, "Not enough arguments");
            }
            List<CommonExpression> secondOrderOperands = new ArrayList<>();
            List<Character> secondOrderOperators = new ArrayList<>();
            secondOrderOperands.add(operands.get(0));
            for (int i = 0; i < operators.size(); i++) {
                switch (operators.get(i)) {
                    case '*': {
                        secondOrderOperands.set(secondOrderOperands.size() - 1,
                                new CheckedMultiply(
                                        secondOrderOperands.get(secondOrderOperands.size() - 1), operands.get(i + 1)
                                )
                        );
                    }
                    break;
                    case '/': {
                        secondOrderOperands.set(secondOrderOperands.size() - 1,
                                new CheckedDivide(
                                        secondOrderOperands.get(secondOrderOperands.size() - 1), operands.get(i + 1)
                                )
                        );
                    }
                    break;
                    default: {
                        secondOrderOperands.add(operands.get(i + 1));
                        secondOrderOperators.add(operators.get(i));
                    }
                    break;
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

        private CommonExpression parseMinus(List<CommonExpression> operands, List<Character> operators, int balance) throws ParseException {
            boolean isMinus = true;
            skipWhitespace();
            while (test('-')) {
                isMinus = !isMinus;
                skipWhitespace();
            }
            CommonExpression value;
            if (test('(')) {
                value = (isMinus) ? new CheckedNegate(parseExpression(balance + 1)) : parseExpression(balance + 1);
            } else if (between('0', '9') || isVariable()) {
                value = parseTerm(isMinus, operands.size() - operators.size());
            } else if (currentChar == 'l' || currentChar == 'p') {
                value = (isMinus) ? new CheckedNegate(parseUnaryOperation(operands,operators, balance)) : parseUnaryOperation(operands,operators, balance);
            } else {
                throwParseException(Exceptions.ARGUMENT, "Expected \'(\' or a term, got: " + currentChar);
                value = null; //unreachable
            }
            return value;
        }

        private CommonExpression parseTerm(boolean withMinus, int difference) throws ParseException {
            if (difference >= 1) {
                throwParseException(Exceptions.SYNTAX, "Illegal expression");
            }
            return between('0', '9') ? parseConst(withMinus) : parseVariable(withMinus);
        }

        private CommonExpression parseUnaryOperation(List<CommonExpression> operands, List<Character> operators, int balance) throws ParseException {
            boolean isLog = false;
            if (test("log2")) {
                isLog = true;
            } else if (test("pow2")) {
                isLog = false;
            } else {
                throwParseException(Exceptions.SYNTAX, "Unknown operation");
            }

            if(test('x')) {
                throwParseException(Exceptions.GENERAL, "I seriously can't understand why it is a mistake ¯\\_(ツ)_/¯\n" +
                                    "Throwing a table: (╯°□°）╯︵ ┻━┻\n" +
                                    "Then putting it back: ┬──┬◡ﾉ(° -°ﾉ)\n" +
                                    "Poor table, everyone hurts you");
            }
            skipWhitespace();
            CommonExpression value;
            if (test('(')) {
                value = parseExpression(balance + 1);
            } else if (test('-')) {
                value = parseMinus(operands, operators, balance);
            } else if (currentChar == 'l' || currentChar == 'p') {
                value = parseUnaryOperation(operands,operators, balance);
            } else if (between('0', '9') || isVariable()) {
                value = parseTerm(false, operands.size() - operators.size());
            } else {
                throwParseException(Exceptions.ARGUMENT, "Expected \'(\' or a term, got: " + currentChar);
                value = null; //unreachable
            }
            return isLog ? new Log2(value) : new Pow2(value);
        }

        private CommonExpression parseVariable(boolean withMinus) {
            char name = currentChar;
            nextChar();
            if (withMinus) {
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
                sb.append(currentChar);
                nextChar();
            }
            try {
                return new Const(Integer.parseInt(sb.toString()));
            } catch (NumberFormatException e) {
                throwParseException(Exceptions.CONSTANT, "Not parsable integer: " + sb);
                return null; //unreachable
            }
        }
    }
}


/*
──────▄▌▐▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀​▀▀▀▀▀▀▌
───▄▄██▌█ BEEP BEEP
▄▄▄▌▐██▌█ GAY PORN DELIVERY
███████▌█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄​▄▄▄▄▄▄▌
▀(@)▀▀▀▀▀▀▀(@)(@)▀▀▀▀▀▀▀▀▀▀▀▀▀​▀▀▀▀(@)▀
*/