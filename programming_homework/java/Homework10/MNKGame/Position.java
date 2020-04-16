package MNKGame;

public interface Position {
    int getRowNumber();
    int getColumnNumber();
    boolean isValid(Move move);

    CellType getCell(int row, int column);
}
