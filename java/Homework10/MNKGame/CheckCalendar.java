package MNKGame;

import java.util.Scanner;

public class CheckCalendar {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int numOfTeams = sc.nextInt();
        int[] left = new int[numOfTeams / 2];
        int[] right = new int[numOfTeams / 2];

        Calendar.make_Calendar(left, right, numOfTeams);
        for (int i = 0; i < numOfTeams - 1; i++) {
            System.out.println(Calendar.toPrint(left, right, numOfTeams));
            Calendar.next_Calendar(left, right, numOfTeams);
        }
    }
}
