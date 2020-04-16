package MNKGame;

import org.w3c.dom.ls.LSOutput;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int row = -1;
        int column = -1;
        int win = -1;
        do {
            System.out.println("Enter number of rows, columns and winning number separated by a whitespace:");
            String[] input = sc.nextLine().split("\\s+");
            if (input.length != 3) {
                System.out.println("Wrong number of arguments.");
                continue;
            }

            try{
                row = Integer.parseInt(input[0]);
                column = Integer.parseInt(input[1]);
                win = Integer.parseInt(input[2]);
                if (row <= 0 || column <= 0 || win <= 0) {
                    throw new NumberFormatException();
                }
            } catch (NumberFormatException e) {
                System.out.println("Wrong input format. Expected positive integers.");
                continue;
            }
            break;
        } while(true);

        Player playerOne = null;
        System.out.println("Who will be the first player?");
        do {
            System.out.println("1 - SequentialPlayer, 2 - RandomPlayer, 3 - Human");
            String input = sc.next();
            if (input.equals("1")) {
                playerOne = new VirginSequentialPlayer();
            } else if (input.equals("2")) {
                playerOne = new ChadRandomPlayer();
            } else if (input.equals("3")) {
                playerOne = new GodlikeHumanPlayer();
            } else {
                System.out.println("No such player! Try again!");
            }
        } while (playerOne == null);

        Player playerTwo = null;
        System.out.println("Who will be the second player?");
        do {
            System.out.println("1 - SequentialPlayer, 2 - RandomPlayer, 3 - Human");
            String input = sc.next();
            if (input.equals("1")) {
                playerTwo = new VirginSequentialPlayer();
            } else if (input.equals("2")) {
                playerTwo = new ChadRandomPlayer();
            } else if (input.equals("3")) {
                playerTwo = new GodlikeHumanPlayer();
            } else {
                System.out.println("No such player! Try again!");
            }
        } while (playerTwo == null);

        final Game game = new Game(playerOne, playerTwo);
        int result = game.start(new MNKBoard(row, column, win));
        if (result != 0) {
            System.out.println("Player " + result + " won! Congratulations!");
        } else {
            System.out.println("It's a draw!");
        }


        sc.close();
    }
}