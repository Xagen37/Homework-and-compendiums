package expression.exceptions;

public class NegativeArgumentException extends EvaluateException {
    public NegativeArgumentException(String message) {
        super(message);
    }

    public NegativeArgumentException(String message, Throwable cause) {
        super(message, cause);
    }
}
