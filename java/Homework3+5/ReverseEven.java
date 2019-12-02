import java.util.ArrayList;
import java.util.List;

public class ReverseEven {
	
	public static void main(String[] args) {
		Scanner scanInput = new Scanner(System.in);
		
		List<ArrayList<Integer>> input = new ArrayList<ArrayList<Integer>>();
		while (scanInput.hasNextLine()) {
			String line = scanInput.nextLine();
			String[] splitRes = line.split("\\s+");
			ArrayList <Integer> numsInLine = new ArrayList <Integer>(); 
		
			for (int i = 0; i < splitRes.length; i++) {
				if (!splitRes[i].isEmpty()) {
					numsInLine.add(Integer.parseInt(splitRes[i]));
				}
			}
			input.add(numsInLine);
		}
		
		scanInput.close();
		
		for (int i = input.size() - 1; i >= 0; i--) {
			for (int k = input.get(i).size() - 1; k >= 0; k--) {
				if (input.get(i).get(k) % 2 == 0) {
				    System.out.print(input.get(i).get(k) + " ");
				}
			}
			System.out.println();
		}
	}
}