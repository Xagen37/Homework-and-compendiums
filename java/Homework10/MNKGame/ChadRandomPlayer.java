package MNKGame;

import java.util.Random;

public class ChadRandomPlayer implements Player {
    private final Random random;

    public ChadRandomPlayer(Random random) {
        this.random = random;
    }

    public ChadRandomPlayer() {
        random = new Random();
    }

    @Override
    public Move move(final Position pos, final CellType cell) {
        Move move;
        do {
            int row = random.nextInt(pos.getRowNumber());
            int column = random.nextInt(pos.getColumnNumber());
            move = new Move(row, column, cell);
        } while(!pos.isValid(move));
        return move;
    }
}
