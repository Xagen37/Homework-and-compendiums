package search;

public class BinarySearchMissing {


    /*  Pred:
     *  array[i] >= array[j], for any i < j
     */
    public static void main(String[] args) {
        int x = Integer.parseInt(args[0]);
        int[] array = new int[args.length - 1];
        for (int i = 1; i < args.length; i++) {
            array[i - 1] = Integer.parseInt(args[i]);
        }

        //System.out.println(recursive(array, x, -1, array.length));
        System.out.println(iterative(array, x));
    }
    /*  Post:
     *  array[i] >= array[j], for any i < j &&
     *  (R == array.length && x < array[array.length - 1] ||
     *  array[R] > x && (R == 0 || array[R - 1] < x)) ||
     *  array[R] == x && (R == 0 || array[R - 1] > x))
     */


    /*  Pred:
     *  array[i] >= array[j], for any i < j &&
     *  -1 <= left < array.length &&
     *  -1 < right <= array.length &&
     *  right - left >= 1
     */
    private static int recursive(int[] array, int x, int left, int right) {
        /*  -1 <= left < array.length &&
         *  -1 < right <= array.length &&
         *  right - left >= 1
         */
        if (right - left == 1) {
            /*  right - left == 1 &&
             *  -1 < right <= array.length &&
             *  (x < array[array.length - 1] && right == array.length ||
             *  array[right] <= x && (right - 1 < 0 || array[right - 1] > x))
             */
            if (right < array.length && array[right] == x) {
                /*
                 *  -1 < right < array.length &&
                 *  array[right] == x && (right - 1 < 0 || array[right - 1] > x)
                 */
                return right;
                //R == right
            } else {
                /*
                 *  -1 < right <= array.length &&
                 *  (right == array.length && x < array[array.length - 1] ||
                 *  array[right] > x && (right == 0 || array[right - 1] < x))
                 */
                return -right - 1;
                //R == -(right + 1)
            }
        }

        /*  -1 <= left < array.length &&
         *  -1 < right <= array.length &&
         *  right - left > 1
         */
        int mid = left + (right - left) / 2;
        /*  -1 <= left < array.length &&
         *  -1 < right <= array.length &&
         *  right - left > 1 &&
         *  -1 < mid < array.length && mid == |(left + right) / 2| (rounded to zero)
         */
        if (x >= array[mid]) {
            /*  -1 <= left < array.length &&
             *  right' == mid &&
             *  -1 < right' < array.length &&
             *  1 <= right' - left && right' < right &&
             *  array[i] >= array[j], for any i < j
             */
            return recursive(array, x, left, mid);
        } else {
            /*  left' == mid &&
             *  -1 < left' < array.length &&
             *  -1 < right <= array.length &&
             *  1 <= right - left' && left' > left &&
             *  array[i] >= array[j], for any i < j
             */
            return recursive(array, x, mid, right);
        }
    }
    /*  Post:
     *  array[i] >= array[j], for any i < j &&
     *  (R == array.length && x < array[array.length - 1] ||
     *  array[R] > x && (R == 0 || array[R - 1] < x)) ||
     *  array[R] == x && (R == 0 || array[R - 1] > x))
     */



    /*  Pred:
     *  array[i] >= array[j], for any i < j
     */
    private static int iterative(int[] array, int x) {
        int left = -1;
        int right = array.length;
        /* -1 == left < array.length &&
         *  -1 < right == array.length &&
         *  right - left >= 1
         */
        while (right - left > 1) {
            /* -1 <= left < array.length &&
             *  -1 < right <= array.length &&
             *  right - left > 1
             */
            int mid = left + (right - left) / 2;
            /* -1 <= left < array.length &&
             *  -1 < right <= array.length &&
             *  right - left > 1 &&
             *  -1 < mid < array.length && mid == |(left + right) / 2| (rounded to zero)
             */
            if (x >= array[mid]) {
                /*  -1 <= left < array.length &&
                 *  -1 < mid < array.length &&
                 *  1 <= mid - left && mid < right
                 */
                right = mid;
                /*  right' == mid &&
                 *  1 < right' < array.length &&
                 *  -1 <= left < array.length &&
                 *  right' - left >= 1;
                 */
            } else {
                /*  -1 < mid < array.length &&
                 *  -1 < right <= array.length &&
                 *  1 <= right - mid && mid > left
                 */
                left = mid;
                /*  left' == mid &&
                 *  1 < left' < array.length &&
                 *  -1 < right <= array.length &&
                 *  right - left' >= 1;
                 */
            }
            /*  -1 <= left' < array.length &&
             *  -1 < right' <= array.length &&
             *  right' - left' >= 1 && (left' > left || right' < right)
             */
        }
        /*  -1 <= left < array.length &&
         *  -1 < right <= array.length &&
         *  right - left == 1 &&
         *  (x < array[array.length - 1] && right == array.length ||
         *  array[right] <= x && (right - 1 < 0 || array[right - 1] > x))
         */
        if (right < array.length && array[right] == x) {
            /*
             *  -1 < right < array.length &&
             *  array[right] == x && (right - 1 < 0 || array[right - 1] > x)
             */
            return right;
            //R == right
        } else {
            /*
             *  -1 < right <= array.length &&
             *  (right == array.length && x < array[array.length - 1] ||
             *  array[right] > x && (right == 0 || array[right - 1] < x))
             */
            return -right - 1;
            //R == -(right + 1)
        }
    }
    /*  Post:
     *  array[i] >= array[j], for any i < j &&
     *  (R == array.length && x < array[array.length - 1] ||
     *  array[R] > x && (R == 0 || array[R - 1] < x)) ||
     *  array[R] == x && (R == 0 || array[R - 1] > x))
     */
}
