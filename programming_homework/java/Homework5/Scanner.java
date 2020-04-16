import java.io.*;
import java.util.NoSuchElementException;
import java.util.Arrays;

public class Scanner {
	BufferedReader in;
	boolean isClosed = true;
	int readFrom = 0;
	int readTo = 0;
	String buffer = "";
	
	public Scanner(String fileName, String encoding) throws FileNotFoundException, IOException,
																	NullPointerException {
		if (fileName.isEmpty() || encoding.isEmpty()) {
			throw new NullPointerException("Argument is null");
		} 
		in = new BufferedReader(
				new InputStreamReader(
					new FileInputStream(
						new File(fileName)
					),
				encoding)
			);
		isClosed = false;
	}
	
	public Scanner(String lineName) {
		if (lineName == null) {
			throw new NullPointerException("Argument is null");
		}
		
		buffer = new String(lineName);
		readTo = buffer.length();
		
		isClosed = false;
	}
	
	public Scanner(InputStream in) {
		if (in == null) {
			throw new NullPointerException("Argument is null");
		}
		this.in = new BufferedReader(new InputStreamReader(in));
		isClosed = false;
	}

	public void close() {
		if (isClosed) {
			return;
		} else {
			isClosed = true;
			if (in != null) {
				try {
					in.close();
				} finally {
					return;
				}
			}
		}
	}
	
	private boolean fillBuffer() {
		if (in == null) {
			return false;
		}
		try {
			buffer = in.readLine();
		} catch(IOException e) {
			e.printStackTrace();
		}
		if (buffer == null) {
			return false;
		} else {
			readFrom = 0;
			readTo = buffer.length();
			return true;
		}
	}

	public boolean hasNextLine() {

		return hasNext();
	}

	public String nextLine() throws NoSuchElementException {
		if (isClosed) {
			throw new IllegalStateException("The scanner is closed");
		}
		if (readFrom < readTo) {
			return buffer.substring(readFrom);
		}
		String input = "";
		try {
			input = in.readLine();
			if (input == null) {
				throw new NoSuchElementException("Reached EOF without reading any character");
			}
		} catch(IOException e) {
			e.printStackTrace();
		}
		return input;
	}
	
	public boolean hasNext() {
		if (isClosed) {
			throw new IllegalStateException("The scanner is closed");
		}
		
		try {
			 if(readFrom < readTo || (in != null && in.ready())) {
				return true; 
			 }
		} catch(IOException e) {
			e.printStackTrace();
		}
		return false;
	}
	
	public String nextWord() {
		if (isClosed) {
			throw new IllegalStateException("The scanner is closed"); 
		}
		
		if (readFrom >= readTo) 
		{
			if(!fillBuffer()) {
				throw new NoSuchElementException("Reached EOF without reading any character");
			}
		}
		
		StringBuilder buildWord = new StringBuilder();
		while (readFrom < readTo && (Character.isLetter(buffer.charAt(readFrom)) || 
				Character.getType(buffer.charAt(readFrom)) == Character.DASH_PUNCTUATION ||
				buffer.charAt(readFrom) == '\''))
		{
			buildWord.append(buffer.charAt(readFrom));
			readFrom++;
		}
		readFrom++;
		return new String(buildWord);
	}
	
	public int nextInt() {
		if (isClosed) {
			throw new IllegalStateException("The scanner is closed"); 
		}
		
		if (readFrom >= readTo) 
		{
			if(!fillBuffer()) {
				throw new NoSuchElementException("Reached EOF without reading any character");
			}
		}
		
		while(readFrom < readTo && Character.isWhitespace(buffer.charAt(readFrom))) {
			readFrom++;
		}
		
		if(readFrom >= readTo) {
			return nextInt();
		}
		
		int buildInt = 0;
		boolean sign = true;	
			
		if (buffer.charAt(readFrom) == '-') {
			sign = false;
			readFrom++;
		} else {
			if (buffer.charAt(readFrom) == '+') {
				readFrom++;
			} else {
				if (!Character.isDigit(buffer.charAt(readFrom))) {
					throw new NumberFormatException("Expected digit or sign, got NaN");
				}
			}
		}
		while(readFrom < readTo && !Character.isWhitespace(buffer.charAt(readFrom))) {
			if (!Character.isDigit(buffer.charAt(readFrom))) {
					throw new NumberFormatException("Expected digit, got NaN");
			}
			buildInt = buildInt * 10 + Character.digit(buffer.charAt(readFrom), 10);
			readFrom++;
		}
		
		readFrom++;
		if (sign) {
			return buildInt;
		} else {
			return -buildInt;
		}
	}
}
