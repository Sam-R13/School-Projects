/**
 * A linked-node implementation of the Set ADT in which elements of the set
 * are always sorted (in this case, lexicographically, which is a fancy
 * way of saying "alphabetically").  Note that the String class has a compareTo
 * method which you should be using to assist you in keeping the set sorted.
 * 
 */
public class SortedSet implements SetInterface<String> {
	private class Node {
		String data;
		Node next, prev;
		
		public Node() {
			data = null;
			next = null;
			prev = null;
		}
		
		public Node(String data) {
			this.data = data;
			next = null;
			prev = null;
		}
	}
	
	private Node head;
	private int numEntries;
	
	public SortedSet() {
		head = null;
		numEntries = 0;
	}

	@Override
	public int getCurrentSize() {
		return numEntries;
	}

	@Override
	public boolean isEmpty() {
		return numEntries == 0;
	}

	@Override
	public boolean add(String newEntry) {
		Node entry = new Node(newEntry);
		if(isEmpty()) {
			head = entry;
			numEntries++;
			return true;
		}
		Node last = head;
		while(last.next != null) {
			if(last.data.compareTo(newEntry) <= 0)
				last = last.next;
			else {
				entry.prev = last.prev;
				last.prev = entry;
				entry.next = last;
				if(entry.next != null)
					entry.next.prev = entry;
				numEntries++;
				return true;
			}
		}
		if(last.data.compareTo(newEntry) <= 0) {
			last.next = entry;
			entry.prev = last;
			numEntries++;
			return true;
		}	
		else {
			entry.prev = last.prev;
			last.prev = entry;
			entry.next = last;
			numEntries++;
			return true;
		}
	}

	@Override
	public boolean remove(String anEntry) {
		if(isEmpty() || !contains(anEntry))
			return false;
		Node last = head;
		while(last.next != null) {
			if(last.data.equals(anEntry)) {
				if(last.prev != null) {
					last.prev.next = last.next;
					last.next.prev = last.prev;
					numEntries--;
					return true;
				}
				else if(head == last) {
					head = last.next;
					head.prev = null;
					numEntries--;
				}
				return true;
			}
			last = last.next;
		}
		head = null;
		numEntries--;
		return true;
	}

	@Override
	public String remove() {
		if(isEmpty()) {
			return null;
		}
		if(numEntries == 1) {
			String ret = head.data;
			head = null;
			numEntries--;
			return ret;
		}
		if(numEntries >= 2) {
			String ret = head.data;
			head = head.next;
			head.prev = null;
			numEntries--;
			return ret;
		}
		return null;
	}
	
	@Override
	public String removeLast() {
		if(isEmpty())
			return null;
		if(numEntries == 1) {
			String ret = head.data;
			head = null;
			return ret;
		}
		Node last = head;
		while(last.next != null) {
			last = last.next;
		}
		String ret = last.data;
		last.prev.next = null;
		numEntries--;
		return ret;
	}

	@Override
	public void clear() {
		head = null;
		numEntries = 0;
	}

	@Override
	public boolean contains(String anEntry) {
		if(isEmpty())
			return false;
		Node last = head;
		while(last.next != null) {
			if(last.data.equals(anEntry))
				return true;
			last = last.next;
		}
		if(last.data.equals(anEntry))
			return true;
		return false;
	}
	
	/*
	 * returns a string representation of the items in the set,
	 * specifically a space separated list of the strings, enclosed
	 * in square brackets [].  For example, if the set contained
	 * cat, dog, then this should return "[cat dog]".  If the
	 * set were empty, then this should return "[]".
	 */
	@Override
	public String toString() {
		String ret = "[";
		Node last = head;
		while(last.next != null) {
			ret += last.data + " ";
			last = last.next;
		}
		ret += last.data + "]";
		return ret;
	}
	
	@Override
	public String[] toArray() {
		String[] arr = new String[numEntries];
		int i = 0;
		Node last = head;
		while(last.next != null) {
			arr[i] = last.data;
			last = last.next;
			i++;
		}
		arr[i] = last.data;
		return arr;
	}
}