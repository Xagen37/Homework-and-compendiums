package MNKGame;

import java.io.*;

public class Log {
    private final PrintStream out;

    public Log(PrintStream out) {
        this.out = out;
    }

    public Log() {
        PrintStream out1;
        try {
            out1 = new PrintStream(
                    new FileOutputStream(
                            new File("log.txt")
                    )
            );
        } catch (IOException e) {
            e.printStackTrace();
            out1 = new PrintStream(System.out);
        }
        out = out1;
    }

    public void log(String toLog) {
        out.println(toLog);
    }
}
