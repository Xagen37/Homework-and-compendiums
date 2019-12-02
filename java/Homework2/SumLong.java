public class SumLong {
    public static void main(String args[]) {
		long answer = 0;
		for (int i = 0; i < args.length; i++) {
		String splitResult[] = args[i].split("\t|\n|\u0020|\u2028|\u2029|\u2000|\u000B|\f|\r|\u00A0|\u2007|\u202F|\u001C|\u001D\u001E\u001F");
			for (int k = 0; k < splitResult.length; k++) {
				if (splitResult[k].length() != 0) {
					answer += Long.parseLong(splitResult[k]);	
				}
			}
		}
		System.out.println(answer);	
    }
}
