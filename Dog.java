package dog;

//Simple class for a Dog.  Dogs have names and breeds and can make noises
public class Dog {
	private String name;
	private String breed;

	//Default constructor
	public Dog() {
	}
	
	//Constructor that takes the dog's name.  It's breed must be set afterwards
	public Dog(String name) {
		this.name = name;
	}
	//Setter method for the breed
	public void setBreed (String breed) {
		this.breed = breed;
	}
	//Getter method for the breed
	public String getBreed () {
		return this.breed;
	}
	//Setter method for the name
	public void setName (String name) {
		this.name = name;
	}
	//Getter method for the name
	public String getName () {
		return this.name;
	}
	//Method for the dog to make its noise.  Most dogs bark so that's the default noise.
	public void makeNoise(int numTimes) {
		for (int i = 0; i < numTimes; i++) {
			System.out.println("Bark!");
		}
	}
}
