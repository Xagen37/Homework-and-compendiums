import java.util.ArrayList;
import java.util.List;

public class ReverseTranspose {
	
	public static void main(String[] args) {
		Scanner scanInput = new Scanner(System.in);
		
		List<ArrayList<Integer>> input = new ArrayList<ArrayList<Integer>>();
		while(scanInput.hasNextLine()) {
			String line = scanInput.nextLine();
			Scanner scanLine = new Scanner(line);
			ArrayList <Integer> numsInLine = new ArrayList <Integer>(); 
			while(scanLine.hasNext()) {
				numsInLine.add(scanLine.nextInt());
			}
			for (int i = 0; i < numsInLine.size(); i++) {
				if (i >= input.size()) {
					input.add(new ArrayList<Integer>());
				}
				input.get(i).add(numsInLine.get(i));
			}
			scanLine.close();
		}
		
		scanInput.close();
		
		for (var i : input) {
			for (var j : i) {
				System.out.print(j + " ");
			}
			if (i.size() < 1) {
				break;
			}
			System.out.println();
		}
	}
}