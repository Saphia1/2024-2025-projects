package cw2b;
public class Mouse extends Animal
{
	@Override
	public String getName() 
	{ 
		return "I am a mouse"; 
	}

	@Override
	public String getNoise()
	{
		return "The mouse squeeks";
	}
	
	@Override
	public String getMovement()
	{
		return "The mouse scurries";
	}
}
