package expression.exceptions;

public class ConstantOverflowException extends ParseException {
    public ConstantOverflowException(String message) {
        super(message);
    }

    public ConstantOverflowException(String message, Throwable cause) {
        super(message, cause);
    }
}
