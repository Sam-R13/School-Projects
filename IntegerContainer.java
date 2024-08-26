
public class IntegerContainer implements ContainerInterface<Integer>{

	// Storage to store multiple integers
	private Integer [] data;
	// An integer index to indicate the first available location
	private int last;
	// The capacity of the container
	public static final int DEFAULT_CAPACITY = 10;
	
	public IntegerContainer() {
		// TODO Auto-generated constructor stub
		data = new Integer[DEFAULT_CAPACITY];
		last = 0;
	}

	@Override
	public int getCurrentSize() {
		// TODO Auto-generated method stub
		return last;
	}

	@Override
	public boolean isEmpty() {
		// TODO Auto-generated method stub
		return last == 0;
	}

	@Override
	public boolean add(Integer newObject) {

		if(last == data.length)
			return false;
		
		data[last] = newObject;
		last++;
		return true;
	}

	@Override
	public boolean remove(Integer anObject) {
		for(int i = 0; i < last; i++) {
			if( data[i].equals( anObject) ) {
				// remove it
				// Copy the last item to the i-th location
				data[i] = data[last-1];
				// remove the last 
				data[last-1] = null;
				// decrease the last by 1
				last--;
				// we want to remove just one occurrence of anObject
				return true;
			}
		}
		return false;
		
	}

	@Override
	public boolean contains(Integer anObject) {
		for(int i = 0; i < last; i++) {
			if( data[i].equals( anObject) )
				return true;
		}
		return false;
	}

}













