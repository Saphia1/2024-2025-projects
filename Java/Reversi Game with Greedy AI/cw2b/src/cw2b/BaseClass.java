package cw2b;
// Note: ctrl-shift-o for import every standard thing needed
import java.util.ArrayList;

public class BaseClass
{
	public void createAnimals()
	{
		System.err.println("You need to override the createAnimals() function to create and store animals (your Cw2b class)");
	}
	
	public void recordMadeSound( String str )
	{
		System.err.println("You need to implement the recordMadeSound() method in your subclass (your Cw2b class)");
	}
	
	public void recordMoved( String str )
	{
		System.err.println("You need to implement the recordMoved() method in your subclass (your Cw2b class)");
	}
	
	public void finish()
	{
		System.err.println("You need to implement the finish() method in your subclass to output the noises and movement lists (your Cw2b class)");
	}

	

	// Don't override or change this!
	public final void doStuff()
	{
		//System.out.println("Using class " + this.getClass().getName() );
		if ( this.getClass().getName().compareTo("cw2b.Cw2b" ) != 0 )
			System.err.println("You need to create your own class called Cw2b in the package cw2b, and create the object in MainProgram.\n\tYour subclass will change the behaviour by implementing functions.");
		
		createAnimals();
		for ( Animal an : myAnimals )
		{
			recordMoved( an.getMovement() );
			recordMadeSound( an.getNoise() );
			recordMoved( an.getMovement() );
		}
		finish();
	}

	// I hid this inside by making it private
	// List of animals to 'do stuff with'
	// Your sub-class will deliberately not be able to access this and will have to add to it by using storeAnimal().
	private ArrayList<Animal> myAnimals = new ArrayList<Animal>();
	
	// Don't override or change this function!
	// Store an animal in the list - will be used later
	public final void storeAnimal( Animal animalToStore )
	{
		myAnimals.add(animalToStore);
	}
}
