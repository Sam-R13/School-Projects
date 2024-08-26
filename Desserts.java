/**
 * 
 */
package enumerations;

/**
 * @author ferrenam
 *
 */
public enum Desserts {
	//For each member of the enumeration there's a display name defined along with the number of calories per serving
	//This is clarified in the constructor below
	ICE_CREAM("Ice Cream",200),
	PARFAIT("Parfait",300),
	CREME_BRULEE("Crème brûlée",600),
	BANANA_SPLIT("Banana split",1000);

	//Instance variables in this class
	private String name;
	private int cals;

	//A constructor to define the values in the enum
	Desserts(String prettyName, int calories) {
		this.name = prettyName;
		this.cals = calories;
	}

	//Method to get the display string
	public String showName() {
		return this.name;
	}
	//Method to get the number of calories
	public int showCals() {
		  return this.cals;
	  }
}