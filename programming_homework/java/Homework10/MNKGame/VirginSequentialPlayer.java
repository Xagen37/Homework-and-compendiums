package MNKGame;

public class VirginSequentialPlayer implements Player{
    @Override
    public Move move(final Position pos, final CellType cell) {
        for (int row = 0; row < pos.getRowNumber(); row++) {
            for (int column = 0; column < pos.getColumnNumber(); column++) {
                final Move move = new Move(row, column, cell);
                if (pos.isValid(move)) {
                    return move;
                }
            }
        }
        throw new IllegalStateException("No valid moves");
    }
}
