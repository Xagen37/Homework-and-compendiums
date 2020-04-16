package expression.parser;

import expression.exceptions.ParseException;

public abstract class BaseParser {
    private final Source source;
    protected char c;

    public BaseParser(final Source source) {
        this.source = source;
    }

    protected void nextChar() {
        c = (source.hasNext()) ? source.next() : '\0';
    }

    protected void skipWhitespace() {
        while(Character.isWhitespace(c)) {
            test(c);
        }
    }

    protected boolean isOver() {
        return c == '\0';
    }

    protected boolean test(char testValue) {
        if (c == testValue) {
            nextChar();
            return true;
        }
        return false;
    }

    protected boolean between(char left, char right) {
        return left <= c && c <= right;
    }

    protected boolean isVariable() {
        return c == 'x' || c == 'y' || c == 'z';
    }

    protected boolean isBasicOperation() {
        return c == '+' || c == '-' || c == '/' || c == '*';
    }

    protected void throwException(String msg) throws ParseException {
        throw new ParseException(msg);
    }
}
