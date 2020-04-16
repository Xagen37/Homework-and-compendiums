import java.util.Map;
import java.util.TreeMap;
import java.util.List;
import java.util.ArrayList;
import java.io.*;

public class WordStatLineIndex {

    public static void main(String[] args) {
        String inputFile = args[0];
        String outputFile = args[1];

        Scanner in = null;
        try {
            in = new Scanner(inputFile, "utf8");
        } catch(FileNotFoundException e) {
            System.err.println("Couldn't find the file: " + inputFile);
        } catch(IOException e) {
            System.err.println("ERROR!ERROR!ERROR!: " + e.getMessage());
        }

        Map<String, List<Pair>> dictionary = new TreeMap<String, List<Pair>>();
        //List<String> order = new ArrayList<String>();

        int stringCounter = 0;
        int columnCounter = 0;
        while(in.hasNextLine()) {
            stringCounter++;
            String line = in.nextLine();
            Scanner scanLine = new Scanner(line);
            while (scanLine.hasNext()) {
                String word = scanLine.nextWord();
                if (word.isEmpty()) {
                    continue;
                }
                columnCounter++;
                word = word.toLowerCase();
                if (dictionary.containsKey(word)) {
                    List<Pair> change = dictionary.get(word);
                    //change.counter++;
                    change.add(new Pair(stringCounter, columnCounter));
                    dictionary.put(word, change);
                } else {
                    //order.add(word);
                    List<Pair> toAdd = new ArrayList<Pair>();
                    //toAdd.counter++;
                    toAdd.add(new Pair(stringCounter, columnCounter));
                    dictionary.put(word, toAdd);
                }
            }
            columnCounter = 0;
        }

        PrintWriter out = openPrintWriter(outputFile);
        if (out == null) {
            return;
        }

        for (Map.Entry<String, List<Pair>> e : dictionary.entrySet()) {
            out.print(e.getKey() + " ");
            List<Pair> toPrint = e.getValue();
            out.print(toPrint.size());
            for(int i = 0; i < toPrint.size(); i++) {
                out.print(" " + toPrint.get(i).a + ":" + toPrint.get(i).b);
            }
            out.println();
        }

        in.close();
        out.close();
    }

    private static PrintWriter openPrintWriter(String outputFileName) {
        PrintWriter out;
        try {
            out = new PrintWriter(
                    new OutputStreamWriter(
                            new FileOutputStream(
                                    new File(outputFileName)
                            ),
                            "utf8")
            );
        } catch(IOException e) {
            System.err.println("IO error ocurred: " + e.getMessage());
            return null;
        }
        return out;
    }
}
