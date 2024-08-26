/**
 * The purpose of this class is to create array-based Bag objects that hold Fruit objects
 * @author rabesj
 */
public class FruitBag implements BagInterface<Fruit> {
	private Fruit[] bag;
	private int numEntries;
	private static final int DEFAULT_CAPACITY = 25;
	/**
	 * FruitBag()
	 * This constructor creates a fruit bag object and sets the array's length to the default capacity variable
	 */
	public FruitBag() {
		bag = new Fruit[DEFAULT_CAPACITY];
		numEntries = 0;
	}
	/**
	 * FruitBag(int capacity)
	 * This constructor creates a fruit bag object and sets the array's length to the user's choice
	 * @param capacity the integer value of the user's requested length of the array
	 */
	public FruitBag(int capacity) {
		bag = new Fruit[capacity];
		numEntries = 0;
	}
	/**
	 * int getCurrentSize()
	 * This method tells the user how many entries are currently in the fruit bag
	 * @return the integer value of the number of entries in the fruit bag
	 */
	@Override
	public int getCurrentSize() {
		return numEntries;
	}
	/**
	 * boolean isEmpty()
	 * This method determines whether or not the fruit bag is empty
	 * @return true if numEntries is zero, false otherwise
	 */
	@Override
	public boolean isEmpty() {
		return numEntries == 0;
	}
	/**
	 * boolean add(Fruit newEntry)
	 * This method adds a new Fruit to the FruitBag object
	 * @param newEntry the Fruit object to be added to the bag
	 * @return true if the object is added successfully, false otherwise
	 */
	@Override
	public boolean add(Fruit newEntry) {
		boolean result = true;
		if(numEntries >= bag.length)
			result = false;
		else {
			bag[numEntries] = newEntry;
			numEntries++;
		}
		return result;
	}
	/**
	 * Fruit remove()
	 * This method removes the last Fruit object in the bag
	 * @return the Fruit object removed from the bag
	 */
	@Override
	public Fruit remove() {
		Fruit result = null;
		if(numEntries > 0) {
			result = bag[numEntries - 1];
			bag[numEntries - 1] = null;
			numEntries--;
		}
		return result;
	}
	/**
	 * boolean remove(Fruit anEntry)
	 * This method removes a specific Fruit object from the bag
	 * @param anEntry the Fruit object to be removed from the bag
	 * @return true if the object is found and removed, false otherwise
	 */
	@Override
	public boolean remove(Fruit anEntry) {
		int index = getIndexOf(anEntry);
		Fruit result = removeEntry(index);
		return anEntry.equals(result);
	}
	/**
	 * int getIndexOf(Fruit anEntry)
	 * This helper method finds the index of a particular Fruit object within the FruitBag object
	 * @param anEntry the Fruit object we are finding the index of
	 * @return the integer value of the Fruit object's index
	 */
	private int getIndexOf(Fruit anEntry) {
		int where = -1;
		boolean found = false;
		int index = 0;
		while(!found && (index < numEntries)) {
			if(anEntry.equals(bag[index])) {
				found = true;
				where = index;
			}
			index++;
		}
		return where;
	}
	/**
	 * Fruit removeEntry(int index)
	 * This helper method removes the Fruit object at a particular index in the FruitBag object
	 * @param index the integer value of the object's index
	 * @return the Fruit object that this method removed from the FruitBag object
	 */
	private Fruit removeEntry(int index) {
		Fruit result = null;
		if(!isEmpty() && index >= 0) {
			result = bag[index];
			bag[index] = bag[numEntries - 1];
			bag[numEntries - 1] = null;
			numEntries--;
		}
		return result;
	}
	/**
	 * clear()
	 * This method removes all Fruit objects from the FruitBag
	 */
	@Override
	public void clear() {
		while(!isEmpty())
			remove();
	}
	/**
	 * int getFrequencyOf(Fruit anEntry)
	 * This method calculates the frequency of a particular fruit object within the fruit bag
	 * @param anEntry the Fruit object we are calculating the frequency of
	 * @return the integer value of the frequency of the Fruit object
	 */
	@Override
	public int getFrequencyOf(Fruit anEntry) {
		int counter = 0;
		for(int i = 0; i < numEntries; i++) {
			if(bag[i].equals(anEntry))
				counter++;
		}
		return counter;
	}
	/**
	 * boolean contains(Fruit anEntry)
	 * This method determines whether a certain fruit object is contained within the FruitBag
	 * @param anEntry the Fruit object that we are looking for in the FruitBag
	 * @return true if the object is found, false otherwise
	 */
	@Override
	public boolean contains(Fruit anEntry) {
		boolean found = false;
		int index = 0;
		while(!found && (index < numEntries)) {
			if(anEntry.equals(bag[index]))
				found = true;
			index++;
		}
		return found;
	}
	/**
	 * Fruit[] toArray()
	 * This method creates an array based on the objects currently in the FruitBag
	 * @return an array containing each object currently in the FruitBag
	 */
	@Override
	public Fruit[] toArray() {
		Fruit[] result = new Fruit[numEntries];
		for(int i = 0; i < numEntries; i++) {
			result[i] = bag[i];
		}
		return result;
	}
}