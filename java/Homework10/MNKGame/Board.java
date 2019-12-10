package MNKGame;

public interface Board {
    Position getPosition();
    CellType getTurn();
    Result makeMove(Move move);
}
