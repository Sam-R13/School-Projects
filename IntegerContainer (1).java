package com.Lab1WarmUp;

public class IntegerContainer implements ContainerInterface<Integer> {
	private Integer[] data;
	private int last;
	public static final int DEFAULT_CAPACITY = 10;
	
	public IntegerContainer() {
		data = new Integer[DEFAULT_CAPACITY];
		last = 0;
	}
	
	@Override
	public int getCurrentSize() {
		return last;
	}
	
	@Override
	public boolean isEmpty() {
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
	public boolean remove(Integer newObject) {
		for(int i = 0; i < last; i++) {
			if(data[i].equals(newObject)) {
				data[i] = data[last - 1];
				data[last - 1] = null;
				last--;
				return true;
			}
		}
		return false;
	}
	
	@Override
	public boolean contains(Integer anObject) {
		for(int i = 0; i < last; i++) {
			if(data[i].equals(anObject))
				return true;
		}
		return false;
	}
}