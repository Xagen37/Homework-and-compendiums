package MNKGame;

import java.util.Arrays;
import java.util.Map;

public final class MNKBoard implements Board, Position {
    private static final Map<CellType, Character> DISPLAY = Map.of(
            CellType.X, 'X',
            CellType.O, 'O',
            CellType.B, '_'
    );
    private final CellType[][] field;
    private int emptyCells;
    private CellType turn;
    private int rowNumber;
    private int columnNumber;
    private int winNumber;

    public MNKBoard(int rowNumber, int columnNumber, int winNumber) {
        this.rowNumber = rowNumber;
        this.columnNumber = columnNumber;
        this.winNumber = winNumber;
        field = new CellType[rowNumber][columnNumber];
        for (CellType[] row : field) {
            Arrays.fill(row, CellType.B);
        }
        emptyCells = rowNumber * columnNumber;
        turn = CellType.X;
    }

    @Override
    public int getRowNumber() {
        return rowNumber;
    }

    @Override
    public int getColumnNumber() {
        return columnNumber;
    }

    @Override
    public Position getPosition() {
        return this;
    }

    @Override
    public CellType getTurn() {
        return turn;
    }

    @Override
    public CellType getCell(int row, int column) {
        return field[row][column];
    }

    @Override
    public boolean isValid(Move move) {
        return (0 <= move.getRow() && move.getRow() < rowNumber &&
                0 <= move.getColumn() && move.getColumn() < columnNumber &&
                field[move.getRow()][move.getColumn()] == CellType.B &&
                move.getCell() == turn);
    }

    @Override
    public Result makeMove(Move move) {
        if (!isValid(move)) {
            return Result.LOSE;
        }

        int row = move.getRow();
        int column = move.getColumn();
        CellType cell = move.getCell();
        field[row][column] = cell;
        emptyCells--;
        int leftDiag = check(row - 1, column - 1, -1, -1, cell) +
                        check(row + 1, column + 1, 1, 1, cell) + 1;
        int rightDiag = check(row - 1, column + 1, -1, 1, cell) +
                        check(row + 1, column - 1, 1, -1, cell) + 1;
        int horizontal = check(row, column - 1, 0, -1, cell) +
                        check(row, column + 1, 0, 1, cell) + 1;
        int vertical = check(row - 1, column, -1, 0, cell) +
                        check(row + 1, column, 1, 0, cell) + 1;
        if (leftDiag >= winNumber ||
            rightDiag >= winNumber ||
            horizontal >= winNumber ||
            vertical >= winNumber) {
            return Result.WIN;
        } else {
            if (emptyCells == 0) {
                return Result.DRAW;
            } else {
                turn = (turn == CellType.X) ? (CellType.O) : (CellType.X);
                return Result.CONTINUE;
            }
        }

    }

    private int check(int currentRow, int currentColumn, int rowChange, int columnChange, CellType cell) {
        if (0 <= currentRow && currentRow < rowNumber &&
            0 <= currentColumn && currentColumn < columnNumber &&
            field[currentRow][currentColumn] == cell) {
            return check(currentRow + rowChange, currentColumn + columnChange,
                            rowChange, columnChange, cell) + 1;
        }
        else {
            return 0;
        }
    }

    @Override
    public String toString() {
        StringBuilder toOut = new StringBuilder(" ");
        for (int i = 1; i <= columnNumber; i++) {
            toOut.append(Integer.toString(i));
        }
        for (int i = 0; i < rowNumber; i++) {
            toOut.append("\n" + Integer.toString(i + 1));
            for (int j = 0; j < columnNumber; j++) {
                toOut.append(DISPLAY.get(field[i][j]));
            }
        }
        toOut.append('\n');
        return toOut.toString();
    }
}
