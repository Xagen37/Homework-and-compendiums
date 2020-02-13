package expression.exceptions;

public class BracketsMismatchException extends ParseException {
    public BracketsMismatchException(String message) {
        super(message);
    }

    public BracketsMismatchException(String message, Throwable cause) {
        super(message, cause);
    }
}
