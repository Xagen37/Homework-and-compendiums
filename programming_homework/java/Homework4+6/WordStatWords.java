//import java.util.*;
import java.util.Map;
import java.util.TreeMap;
import java.util.List;
import java.util.ArrayList;
import java.io.*;

public class WordStatWords {
	
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
		Map<String, Integer> dictionary = new TreeMap<String, Integer>();
		List<String> order = new ArrayList<String>();
		
		while(in.hasNext()) {
			String word = in.nextWord();
			if (word.isEmpty()) {
				continue;
			}
			word = word.toLowerCase();
			if (dictionary.containsKey(word)) {
				dictionary.put(word, dictionary.get(word) + 1);
			} else {
				order.add(word);
				dictionary.put(word, 1);
			}
		}
		
		PrintWriter out = openPrintWriter(outputFile);
		if (out == null) {
			return;
		}
		
		for (Map.Entry e : dictionary.entrySet()) {
			out.println(e.getKey() + " " + e.getValue());
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