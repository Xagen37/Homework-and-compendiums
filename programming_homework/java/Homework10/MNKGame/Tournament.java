package MNKGame;

import java.util.*;

public class Tournament {
    public static void main(String[] args) {
        Scanner sc = new Scanner (System.in);
        int teamNumber = -1;
        System.out.println("Enter number of teams:");
        do {
            try {
                String input = sc.nextLine();
                teamNumber = Integer.parseInt(input);
                if (teamNumber <= 0) {
                    throw new NumberFormatException();
                }
            } catch(NumberFormatException e) {
                System.out.println("Expected positive integer.");
                continue;
            }
            break;
        } while(true);

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

        int[] leftSide = new int[teamNumber / 2];
        int[] rightSide = new int[teamNumber / 2];
        int[] scores = new int[teamNumber];
        Arrays.fill(scores, 0);
        Player[] players = new Player[teamNumber];
        Random random = new Random();
        for (int i = 0; i < teamNumber; i++) {
            if (random.nextBoolean()) {
                players[i] = new VirginSequentialPlayer();
                System.out.println((i + 1) + ": Sequential");
            } else {
                players[i] = new ChadRandomPlayer();
                System.out.println((i + 1) + ": Random");
            }
        }

        Calendar.make_Calendar(leftSide, rightSide, teamNumber);

        int turnNumber = teamNumber - 1;
        for (int i = 0; i < turnNumber; i++) {
            System.out.println("Turn " + (i + 1) + " starts.");

            for (int k = 0; k < teamNumber / 2; k++) {
                System.out.println("Player " + (leftSide[k] + 1) + " versus player " + (rightSide[k] + 1) + ":");
                Player player1 = players[leftSide[k]];
                Player player2 = players[rightSide[k]];
                int result = new Game(player1, player2).start(new MNKBoard(row, column, win));
                switch (result) {
                    case 1: {
                        scores[leftSide[k]] += 3;
                        System.out.println("Player " + (leftSide[k] + 1) + " won!");
                        break;
                    }
                    case 2: {
                        scores[rightSide[k]] += 3;
                        System.out.println("Player " + (rightSide[k] + 1) + " won!");
                        break;
                    }
                    case 0: {
                        scores[leftSide[k]]++;
                        scores[rightSide[k]]++;
                        System.out.println("It's a draw!");
                        break;
                    }
                }
            }

            Calendar.next_Calendar(leftSide, rightSide, teamNumber);
        }
        for (int i = 0; i < teamNumber; i++) {
            System.out.println("Player " + (i + 1) + " got " + scores[i] + " points.");
        }
    }
}