package MNKGame;

import java.io.PrintStream;
import java.util.Scanner;

public class GodlikeHumanPlayer implements Player {
    private final PrintStream out;
    private final Scanner in;

    public GodlikeHumanPlayer(PrintStream out, Scanner in) {
        this.out = out;
        this.in = in;
    }

    public GodlikeHumanPlayer() {
        this.out = System.out;
        this.in = new Scanner(System.in);
    }

    @Override
    public Move move(final Position pos, final CellType cell) {
        out.println("Current position:");
        out.print(pos);
        out.println("Now is the " + cell + "'s turn.");
        do {
            out.println("Please, enter row and column separated by a whitespace:");
            String[] input = in.nextLine().split("\\s+");
            if(input.length != 2) {
                out.println("Wrong number of arguments! Expected 2: row and column.");
                continue;
            }

            int row = -1;
            int column = -1;
            try{
                row = Integer.parseInt(input[0]);
                column = Integer.parseInt(input[1]);
                if (row <= 0 || column <= 0) {
                    throw new NumberFormatException();
                }
            } catch (NumberFormatException e) {
                out.println("Wrong input format. Expected positive integers.");
                continue;
            }
            row--;
            column--;

            Move move = new Move(row, column, cell);
            if (pos.isValid(move)) {
                return move;
            } else {
                out.print("Move {" + (row + 1) + ", " + (column + 1) + "} is invalid.");
            }
        } while(true);
    }
}
