package expression;

import expression.exceptions.EvaluateException;
import expression.exceptions.ParseException;
import expression.parser.ExpressionParser;

public class Main {
    public static void main(String[] args) {

        CommonExpression expression;
        try {
            expression = new ExpressionParser().parse(args[0]);
        } catch (ParseException e) {
            System.out.println(e.getMessage());
            e.printStackTrace();
            return;
        }

        System.out.println(expression);

        for (int i = 0; i < 10; i++) {
            try {
                System.out.println(i + ": " + expression.evaluate(i));
            } catch (EvaluateException e) {
                System.out.println(i + ": " + e.getMessage());
            }
        }
        /*int value = Integer.parseInt(args[0]);
        System.out.println(
                new Add(
                        new Subtract(
                            new Multiply(
                                    new Variable("x"),
                                    new Variable("x")
                            ),
                            new Multiply(
                                    new Const(2),
                                    new Variable("x")
                            )
                        ),
                        new Const(1)
                ).evaluate(value)
        );*/
    }
}
