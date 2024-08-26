import java.awt.Point;
import java.util.Arrays;
/**
 * The purpose of this class is to create a Set object that is implemented with resizable arrays
 * @author rabesj
 */
public class ResizableArraySet implements SetInterface {
	private Point[] array;
	private int numEntries;
	/**
	 * public ResizableArraySet()
	 * The empty constructor creates the array with a default capacity of 10
	 */
	public ResizableArraySet() {
		array = new Point[10];
		numEntries = 0;
	}
	/**
	 * public ResizableArraySet(int capacity)
	 * This constructor creates the array with the user-specified capacity
	 * @param capacity the integer value of the array's initial capacity
	 */
	public ResizableArraySet(int capacity) {
		array = new Point[capacity];
		numEntries = 0;
	}
	/**
	 * public int getSize()
	 * This method calculates the number of entries in the Set
	 * @return the integer value of the number of entries in the Set
	 */
	@Override
	public int getSize() {
		return numEntries;
	}
	/**
	 * public boolean isEmpty()
	 * This method determines whether or not the Set is empty
	 * @return true if the Set is empty, false otherwise
	 */
	@Override
	public boolean isEmpty() {
		return numEntries == 0;
	}
	/**
	 * public boolean add(Point newValue)
	 * This method attempts to add a new Point to the Set
	 * @param newValue the reference value of the Point object to be added to the Set
	 * @return true if the object is succesfully added, false otherwise
	 */
	@Override
	public boolean add(Point newValue) {
		if(numEntries < array.length) {
			array[numEntries] = newValue;
			numEntries++;
			return true;
		}
		else if(numEntries >= array.length) {
			Point[] copy = Arrays.copyOf(array, array.length * 2);
			array = copy;
			array[numEntries] = newValue;
			numEntries++;
			return true;
		}
		return false;
	}
	/**
	 * public boolean remove(Point aValue)
	 * This method attempts to remove a specific Point object from the Set
	 * @param aValue the Point object to be removed from the Set
	 * @return true if the object is found and removed, false otherwise
	 */
	@Override
	public boolean remove(Point aValue) {
		int index = indexOf(aValue);
		if(index >= 0) {
			array[index] = array[numEntries];
			array[numEntries] = null;
			numEntries--;
			if(numEntries <= array.length / 3) {
				Point[] copy = Arrays.copyOf(array, array.length / 2);
				array = copy;
			}
			return true;
		}
		return false;
	}
	
	private int indexOf(Point aValue) {
		for(int i = 0; i < numEntries; i++) {
			if(array[i].equals(aValue)) {
				return i;
			}
		}
		return -1;
	}
	/**
	 * public Point remove()
	 * This method attempts to remove the last Point from the Set
	 * @return the reference value of the Point that was removed
	 */
	@Override
	public Point remove() {
		if(numEntries > 0) {
			Point ret = array[numEntries - 1];
			array[numEntries - 1] = null;
			numEntries--;
			if(numEntries <= array.length / 3) {
				Point[] copy = Arrays.copyOf(array, array.length / 2);
				array = copy;
			}
			return ret;
		}
		return null;
	}
	/**
	 * public void clear()
	 * This method removes all objects from the Set
	 */
	@Override
	public void clear() {
		for(int i = 0; i < numEntries; i++) {
			array[i] = null;
		}
		numEntries = 0;
	}
	/**
	 * public boolean contains(Point anEntry)
	 * This method determines whether a specific point is contained within the Set
	 * @param anEntry the reference value of the Point object we are searching for
	 * @return true if the object is found, false otherwise
	 */
	@Override
	public boolean contains(Point anEntry) {
		for(int i = 0; i < numEntries; i++) {
			if(array[i].equals(anEntry))
				return true;
		}
		return false;
	}
	/**
	 * public SetInterface union(SetInterface anotherSet)
	 * This method creates a new Set that represents the union of two other specific sets
	 * @param anotherSet the Set object to be unionized with the implicit parameter object
	 * @return the Set that results from the union of these two sets
	 */
	@Override
	public SetInterface union(SetInterface anotherSet) {
		if(anotherSet instanceof ResizableArraySet) {
			ResizableArraySet other = (ResizableArraySet) anotherSet;
			ResizableArraySet temp = new ResizableArraySet(this.array.length + other.array.length);
			for(int i = 0; i < this.numEntries; i++) {
				for(int j = 0; j < other.numEntries; j++) {
					temp.add(this.array[i]);
					if(!other.array[j].equals(null)) {
						temp.add(other.array[j]);
					}
				}
			}
			return temp;
		}
		return this;
	}
	/**
	 * public SetInterface intersection(SetInterface anotherSet)
	 * This method creates a new Set that represents the intersection of two specific sets
	 * @param anotherSet the Set object to be intersected with the implicit parameter object
	 * @return the Set that results from the intersection of these two Sets
	 */
	@Override
	public SetInterface intersection(SetInterface anotherSet) {
		if(anotherSet instanceof ResizableArraySet) {
			ResizableArraySet other = (ResizableArraySet) anotherSet;
			ResizableArraySet temp = new ResizableArraySet(this.array.length + other.array.length);
			for(int i = 0; i < this.numEntries; i++) {
				for(int j = 0; j < other.numEntries; j++) {
					if(this.array[i].equals(other.array[j])) {
						temp.add(this.array[i]);
					}
				}
			}
			return temp;
		}
		return null;
	}
	/**
	 * public setInterface difference(SetInterface anotherSet)
	 * This method creates a new Set that represents the difference of two specific sets
	 * @param anotherSet the Set object to be differentiated with the implicit parameter object
	 * @return the Set that results from the difference of these two sets
	 */
	@Override
	public SetInterface difference(SetInterface anotherSet) {
		if(anotherSet instanceof ResizableArraySet) {
			ResizableArraySet other = (ResizableArraySet) anotherSet;
			ResizableArraySet temp = new ResizableArraySet(this.array.length + other.array.length);
			for(Point p: this.array) {
				if(!other.contains(p) && p != null) {
					temp.add(p);
				}
			}
			return temp;
		}
		return null;
	}
	/**
	 * public Point[] toArray()
	 * This method creates an array with no null or empty references that holds all objects in the Set
	 * @return the neat array
	 */
	@Override
	public Point[] toArray() {
		Point[] ret = new Point[numEntries];
		for(int i = 0; i < numEntries; i++) {
			ret[i] = array[i];
		}
		return ret;
	}
	
}