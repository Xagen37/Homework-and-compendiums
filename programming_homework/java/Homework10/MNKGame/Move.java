package MNKGame;

public class Move {
    private final int row;
    private final int column;
    private final CellType cell;

    public Move(int row, int column, CellType cell) {
        this.row = row;
        this.column = column;
        this.cell = cell;
    }

    public int getRow() {
        return row;
    }

    public int getColumn() {
        return column;
    }

    public CellType getCell() {
        return cell;
    }
}
