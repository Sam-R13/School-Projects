package recursion;

public class Tester {
	public static void main(String[] args) {
		System.out.println(sqRoot(64));
		System.out.println(dashInsert("James Bond", 0)); // Expected: J-a-m-e-s B-o-n-d
		int[] j = new int[] { 1, 4, 5, 6, 8, 10 };
		System.out.println(isSorted(j));
		System.out.println(countOP_PO("pop", 0, 0));
	}
	
	public static double sqRoot(double s) {
		return sqRoot(s, s / 2);
	}
	
	private static double sqRoot(double n, double guess) {
		double newGuess = n / guess;
		newGuess += guess;
		newGuess = newGuess / 2;
		if(newGuess == guess) return guess;
		return sqRoot(n, newGuess);
	}
	
	public static String dashInsert(String s, int index) {
		if(s.length() <= 1) return s;
		if(s.charAt(index) == ' ') return dashInsert(s, index++);
		if(s.length() > index + 1 && s.charAt(index + 1) != ' ') 
			return dashInsert((s.substring(0, index + 1) + "-" + s.substring(index + 1)), index + 2);
		else if(s.length() > index + 2 && s.charAt(index + 2) != ' ')
			return dashInsert(s, index + 2);
		return s;
	}
	
	public static boolean isSorted(int[] s) {
		return isSorted(s, 0);
	}
	
	private static boolean isSorted(int[] s, int index) {
		if(s.length <= index + 1) return true;
		if(s.length > index + 1 && s[index] <= s[index + 1])
			return isSorted(s, ++index);
		return false;
	}
	
	public static int countOP_PO(String s, int index, int currentCounter) {
		if(!(s.contains("po")) && !(s.contains("Po")) && !(s.contains("PO"))
				&& !(s.contains("pO")) && !(s.contains("op")) && !(s.contains("Op"))
				&& !(s.contains("oP")) && !(s.contains("OP"))) return 0;
		if(s.length() > index + 1 && (s.charAt(index) != 'p' && s.charAt(index) != 'o'
				&& s.charAt(index) != 'P' && s.charAt(index) != 'O')) 
			return countOP_PO(s, ++index, currentCounter);
		if(s.length() > index + 1 && (s.charAt(index) == 'p' || s.charAt(index) == 'P')
				&& (s.charAt(index + 1) == 'o' || s.charAt(index + 1) == 'O'))
				return countOP_PO(s, ++index, ++currentCounter);
		if(s.length() > index + 1 && ((s.charAt(index + 1) == 'p' || s.charAt(index + 1) == 'P')
				&& (s.charAt(index) == 'o' || s.charAt(index) == 'O')))
				return countOP_PO(s, ++index, ++currentCounter);
		if(s.length() > index + 1 && (!(s.charAt(index + 1) == 'p' || s.charAt(index + 1) == 'P')
				&& (s.charAt(index) == 'o' || s.charAt(index) == 'O')))
				return countOP_PO(s, ++index, currentCounter);
		if(s.length() > index + 1 && ((s.charAt(index) == 'p' || s.charAt(index) == 'P')
				&& !(s.charAt(index + 1) == 'o' || s.charAt(index + 1) == 'O')))
				return countOP_PO(s, ++index, currentCounter);
		return currentCounter;
	}
	
	public static int countOP(String s, int index, int currentCounter) {
		
	}
}
