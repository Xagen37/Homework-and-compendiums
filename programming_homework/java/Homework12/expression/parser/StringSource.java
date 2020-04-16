package expression.parser;

public class StringSource implements Source {
    private final String line;
    private int it;

    public StringSource(String line) {
        this.line = line;
        it = 0;
    }

    @Override
    public boolean hasNext() {
        return it < line.length();
    }

    @Override
    public char next() {
        return line.charAt(it++);
    }
}
