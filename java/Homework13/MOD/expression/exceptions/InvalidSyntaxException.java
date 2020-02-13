package expression.exceptions;

public class InvalidSyntaxException extends ParseException {
    public InvalidSyntaxException(String message) {
        super(message);
    }

    public InvalidSyntaxException(String message, Throwable cause) {
        super(message, cause);
    }
}
