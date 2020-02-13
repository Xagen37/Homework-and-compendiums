package expression.parser;

import expression.exceptions.*;

import static expression.parser.BaseParser.Exceptions.*;

public abstract class BaseParser {
    private final Source source;
    protected char currentChar;

    public BaseParser(final Source source) {
        this.source = source;
    }

    protected void nextChar() {
        currentChar = (source.hasNext()) ? source.next() : '\0';
    }

    protected int pos() {
        return source.getPos();
    }

    protected void skipWhitespace() {
        while(Character.isWhitespace(currentChar)) {
            test(currentChar);
        }
    }

    protected boolean isOver() {
        return currentChar == '\0';
    }

    protected boolean test(char testValue) {
        if (currentChar == testValue) {
            nextChar();
            return true;
        }
        return false;
    }

    protected boolean test(String testValue) {
        for (int i = 0; i < testValue.length(); i++) {
            if (!test(testValue.charAt(i))) {
                return false;
            }
        }
        return true;
    }

    protected boolean between(char left, char right) {
        return left <= currentChar && currentChar <= right;
    }

    protected boolean isVariable() {
        return currentChar == 'x' || currentChar == 'y' || currentChar == 'z';
    }

    protected boolean isBasicOperation() {
        return currentChar == '+' || currentChar == '-' || currentChar == '/' || currentChar == '*';
    }

    protected enum Exceptions {
        GENERAL, BRACKETS, CONSTANT, SYNTAX, ARGUMENT
    }
    protected void throwParseException(Exceptions exception, String msg) throws ParseException {
        switch (exception) {
            case BRACKETS: throw new BracketsMismatchException(source + " | " + msg);
            case CONSTANT: throw new ConstantOverflowException(source + " | " + msg);
            case SYNTAX: throw new InvalidSyntaxException(source + " | " + msg);
            case ARGUMENT: throw new InvalidArgumentException(source + " | " + msg);
            default: throw new ParseException(source + " | " + msg);
        }
    }
}
