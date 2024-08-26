/**
 * A class to represent a node object which stores an integer data and a reference to the next node object
 * @author rabesj
 */
public class Node {
	int data;
	Node next;
	
	public Node() {
		next = null;
	}
	public Node(int data) {
		this.data = data;
		next = null;
	}
	
	public String toString() {
		if(data == 0)
			return "";
		else
			return data + " ";
	}
}
