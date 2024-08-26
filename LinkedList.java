import java.util.Random;
/**
 * The purpose of this class is to create and modify a LinkedList of Nodes
 * @author rabesj
 * Working methods: All but countNodes() as far as I can tell
 * Non-working method: countNodes(), works perfectly in every instance except when it has to count the list of ten random integers, at which point it is for some
 * reason one behind the actual count
 */
public class LinkedList {
	Node head;
	
	public LinkedList() {
		head = new Node();
	}
	
	public void addToHead(int value) {
		Node next = new Node(value); // Node to be added at the beginning
		next.next = head; // sets the next reference to the current head node
		head = next; // sets the current head node to the created node
	}
	
	public void addToTail(int value) {
		Node tail = new Node(value); // Node to be added at the end
		// if statement checks if the first node exists, then makes tail the first node if the first node doesn't exist
		if(head == null) {
			head = tail;
			return;
		}
		Node last = lastNode();
		last.next = tail; // set tail as the next node of the last node in the current list
		return;
	}
	
	public Node removeFirst() {
		// if there are no nodes in the list, return null
		if(head == null) {
			return null;
		}
		Node ret = head; // sets the old head as a returnable node
		head = head.next; // sets head to the old head's next reference(even if it's null)
		return ret; // returns the old head
	}
	
	public Node removeLast() {
		Node last = head;
		int counter = 0;
		while(last.next != null) {
			last = last.next;
			counter++;
		} // Creates a node and searches through the list to find the last node, setting the node to the last node reference
		  // also increments a counter for use in a for statement to find the second-to-last node
		Node newLast = head;
		for(int i = 0; i < counter - 1; i++) {
			newLast = newLast.next;
		} // sets the newLast Node to the value before the current Last Node
		newLast.next = null; // sets the next reference of the newLast value to null, effectively removing the last Node from the list
		return last; // returns the last Node from the list now that it has been removed
	}
	
	public boolean contains(int value) {
		Node check = head;
		while(check.next != null) { // creates a Node that references the start of the list, then cycles through the list using a while loop until
			if(check.data == value) // a Node no longer has a next reference. If any Node in the list has a data reference that matches value
				return true; 		// return true
			check = check.next;
		}
		if(check.data == value) // because the loop stops before it gets to the last value
			return true;
		return false; // if it successfully makes it through the while loop without finding a matching data, return false
	}
	
	public Node lastNode() {
		Node last = head;
		while(last.next != null) {
			last = last.next;
		}
		return last;
	}
	
	public int countNodes() {
		if(head != null) {
			Node last = head;
			int counter = 0;
			while(last.next != null) {
				last = last.next;
				counter++;
			}
			return counter;
		}
		else
			return 0;
	}
	
	public String toString() {
		String ret = "[ ";
		Node last = head;
		while(last.next != null) {
			ret += last;
			last = last.next;
		}
		ret += last + "]";
		return ret;
	}
	
	public void randomNodes(int n) {
		Random generator = new Random();
		head.data = generator.nextInt();
		Node last = head;
		for(int i = 1; i < n; i++) {
			Node next = new Node(generator.nextInt());
			last.next = next;
			last = next;
		}
	}
}