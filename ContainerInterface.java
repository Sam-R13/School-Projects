
/**
 * An interface that describes the operations of a container of objects
 *
 * @author Md Osman Gani
 */
public interface ContainerInterface<T> {
	/**
	 * Gets the current number of entries in this container.
	 * 
	 * @return The integer number of entries currently in the container.
	 */
	public int getCurrentSize();

	/**
	 * Sees whether this container is empty.
	 * 
	 * @return True if the container is empty, or false if not.
	 */
	public boolean isEmpty();

	/**
	 * Adds a new object to this container.
	 * 
	 * @param newObject
	 *            The object to be added as a new object.
	 * @return True if the addition is successful, or false if not.
	 */
	public boolean add(T newObject);

	/**
	 * Removes one occurrence of a given object from this container.
	 * 
	 * @param anObject
	 *            The object to be removed.
	 * @return True if the removal was successful, or false if not.
	 */
	public boolean remove(T anObject);

	/**
	 * Tests whether this container contains a given object.
	 * 
	 * @param anObject
	 *            The object to locate.
	 * @return True if the container contains anObject, or false if not.
	 */
	public boolean contains(T anObject);
	
}
