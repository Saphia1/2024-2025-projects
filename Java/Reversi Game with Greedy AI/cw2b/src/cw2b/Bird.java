package cw2b;
public class Bird extends Animal
{
	@Override
	public String getName() 
	{ 
		return "I am a bird"; 
	}

	@Override
	public String getNoise()
	{
		return "The bird squarks";
	}
	
	@Override
	public String getMovement()
	{
		return "The bird flies";
	}
}
