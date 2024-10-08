
import static org.junit.Assert.*;

import org.junit.Test;

public class StackApplicationTest {

	@Test
	public void testSum() {
		Stack<Integer> nums = new Stack<>();
		assertEquals(0, StackApplications.sum(nums));
		
		int randomSize = 50 + (int)(20 * Math.random());
		int sum = 0;
		
		for (int i = 0; i < randomSize; i++) {
			int num = (int)(25 * Math.random());
			sum += num;
			nums.push(num);
		}
		
		assertEquals(sum, StackApplications.sum(nums));
		assertTrue(nums.isEmpty());
	}
	
	@Test
	public void testAlternatingSum() {
		Stack<Integer> nums = new Stack<>();
		assertEquals(0, StackApplications.alternatingSum(nums));
		
		int sum = 0;
		
		nums.push(4); nums.push(1); nums.push(2); nums.push(7); nums.push(2); nums.push(8); nums.push(4);
		sum = 4 - 1 + 2 - 7 + 2 - 8 + 4;
		assertEquals(sum, StackApplications.alternatingSum(nums));
		assertTrue(nums.isEmpty());
	
		
		int randomSize = 0 + (int)(20 * Math.random());
		if(randomSize % 2 == 0)     // make sure always odd number of items in the stack
			randomSize++;
		int factor = 1;
		sum = 0;
		
		for (int i = 0; i < randomSize; i++) {
			int num = (int)(25 * Math.random());
			nums.push(num);
			sum += (num * factor);
			factor *= -1;
		}
		
		assertEquals(sum, StackApplications.alternatingSum(nums));
		assertTrue(nums.isEmpty());		
		
	}
	
	
	@Test
	public void testSumSkipDuplicates() {
		int[] data = {4, 1, 2, 2, 7, 2, 8, 8, 8, 4};
		Stack<Integer> stack = new Stack<>();
		for (int num : data) {
			stack.push(num);
		}		
		assertEquals(28, StackApplications.sumSkipDuplicates(stack));
		
		data = new int[] {1, 2, 3, 4, 5, 6};
		stack = new Stack<>();
		for (int num : data) {
			stack.push(num);
		}		
		assertEquals(21, StackApplications.sumSkipDuplicates(stack));
		
		data = new int[] {1, 1, 1, 1, 1};
		stack = new Stack<>();
		for (int num : data) {
			stack.push(num);
		}		
		assertEquals(1, StackApplications.sumSkipDuplicates(stack));
		
		data = new int[] {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6};
		stack = new Stack<>();
		for (int num : data) {
			stack.push(num);
		}		
		assertEquals(21, StackApplications.sumSkipDuplicates(stack));
		
		data = new int[] {};
		stack = new Stack<>();
		for (int num : data) {
			stack.push(num);
		}		
		assertEquals(0, StackApplications.sumSkipDuplicates(stack));
		
	}
	
	@Test
	public void testStringToStack() {
		String testString = "This is a test string.";
		Stack<Character> result = StackApplications.stringToStack(testString);
		
		String resultString = "";
		while (!result.isEmpty()) {
			resultString = result.pop() + resultString;
		}
		
		assertEquals(testString, resultString);				
	}
	
	@Test
	public void testIntegerToStack() {
		int testInteger = 123456;
		int resultForTestInteger = 654321;
		Stack<Integer> result = StackApplications.integerToStack(testInteger);

		int resultInteger = 0;
		int factor = 10;
		while (!result.isEmpty()) {
			resultInteger *= factor;
			resultInteger += result.pop();
		}
		
		assertEquals(resultForTestInteger, resultInteger);				
	}

	
	@Test
	public void testEmptyStringToStack() {
		String testString = "";
		Stack<Character> result = StackApplications.stringToStack(testString);
		assertTrue(result.isEmpty());
	}
	
	@Test
	public void testReverseStack() {
		int[] data = new int[50];		
		for (int i = 0; i < data.length; i++) {
			data[i] = (int)(10 * Math.random());
		}		
		
		Stack<Integer> start = new Stack<>();			
		for (int num : data) {
			start.push(num);
		}

		StackApplications.reverseStack(start);

		for (int num : data) {
			assertEquals(num, (int)start.pop());
		}
		
		assertTrue(start.isEmpty());		
	}
	
	@Test
	public void testIsPalindrome() {
		assertTrue(StackApplications.isPalindrome("a"));
		assertTrue(StackApplications.isPalindrome("BB"));
		assertTrue(StackApplications.isPalindrome("CCC"));
		assertTrue(StackApplications.isPalindrome("radar"));
		assertTrue(StackApplications.isPalindrome("racecar"));
		assertTrue(StackApplications.isPalindrome("tattarrattat"));
		
		assertFalse(StackApplications.isPalindrome("ab"));
		assertFalse(StackApplications.isPalindrome("abab"));
		assertFalse(StackApplications.isPalindrome("baaa"));		
	}
	
	

}
