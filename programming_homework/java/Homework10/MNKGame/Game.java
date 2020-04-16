package MNKGame;

public class Game {
    private final Player playerFirst;
    private final Player playerSecond;

    public Game(Player playerFirst, Player playerSecond) {
        this.playerFirst = playerFirst;
        this.playerSecond = playerSecond;
    }

    public int start(Board board) {
        Log log = new Log();
        do {
            final int result1 = move(board, playerFirst, 1);
            log.log(board.toString());
            if (result1 != -1) {
                return result1;
            }
            final int result2 = move(board, playerSecond, 2);
            log.log(board.toString());
            if (result2 != -1) {
                return result2;
            }
        } while(true);
    }

    private int move(Board board, Player player, int number) {
        final Move move = player.move(board.getPosition(), board.getTurn());
        Result result = board.makeMove(move);
        switch (result) {
            case WIN: return number;
            case DRAW: return 0;
            case CONTINUE: return -1;
            case LOSE: return 3 - number;
        }
        throw new IllegalStateException("Got an unexpected result\n");
    }
}