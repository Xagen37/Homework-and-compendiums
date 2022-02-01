import org.jetbrains.annotations.NotNull;

/**
 * В теле класса решения разрешено использовать только финальные переменные типа RegularInt.
 * Нельзя volatile, нельзя другие типы, нельзя блокировки, нельзя лазить в глобальные переменные.
 *
 * @author : Sofrygin Alexander
 */
public class Solution implements MonotonicClock {
    private final RegularInt c1_d1 = new RegularInt(0);
    private final RegularInt c1_d2 = new RegularInt(0);
    private final RegularInt d3 = new RegularInt(0);    // last digit optimization
    private final RegularInt c2_d2 = new RegularInt(0);
    private final RegularInt c2_d1 = new RegularInt(0);

    @Override
    public void write(@NotNull Time time) {
        // write to the second clock left-to-right
        c2_d1.setValue(time.getD1());
        c2_d2.setValue(time.getD2());

        d3.setValue(time.getD3());

        // write to the first clock right-to-left
        c1_d2.setValue(c2_d2.getValue());
        c1_d1.setValue(c2_d1.getValue());
    }

    @NotNull
    @Override
    public Time read() {
        // read from the first clock left-to-right
        final RegularInt r1_d1 = new RegularInt(c1_d1.getValue());
        final RegularInt r1_d2 = new RegularInt(c1_d2.getValue());

        final RegularInt r_d3 = new RegularInt(d3.getValue());

        // read from the second clock right-to-left
        final RegularInt r2_d2 = new RegularInt(c2_d2.getValue());
        final RegularInt r2_d1 = new RegularInt(c2_d1.getValue());

        if (r1_d1.getValue() == r2_d1.getValue()) {
            if (r1_d2.getValue() == r2_d2.getValue()) {
                // Clocks are equal or p = 2
                return new Time(r2_d1.getValue(), r2_d2.getValue(), r_d3.getValue());
            } else {
                // p = 1
                return new Time(r2_d1.getValue(), r2_d2.getValue(), 0);
            }
        } else {
            // p = 0
            return new Time(r2_d1.getValue(), 0, 0);
        }
    }
}
