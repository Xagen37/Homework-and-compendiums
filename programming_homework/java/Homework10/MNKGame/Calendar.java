package MNKGame;

public class Calendar {
    static void make_Calendar(int[] left, int[] right, int number) {
        for (int i = 0; i < number / 2; i++) {
            left[i] = i;
            right[i] = number - i - 1;
        }
    }

    static void next_Calendar(int[] left, int[] right, int number) {
        for (int k = 0; k < number / 2; k++) {
            if (k == 0) {
                right[k] = (right[k] + 1) % number;
                if (right[k] == 0) {
                    right[k] = 1;
                }
            } else {
                left[k] = (left[k] + 1) % number;
                if (left[k] == 0) {
                    left[k] = 1;
                }
                right[k] = (right[k] + 1) % number;
                if (right[k] == 0) {
                    right[k] = 1;
                }
            }
        }
    }

    public static String toPrint(int[] left, int[] right, int number) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < number / 2; i++) {
            sb.append(left[i] + 1).append(' ');
            sb.append(right[i] + 1).append(' ');
        }
        return sb.toString();
    }
}
