package cw2b;
public class Fish extends Animal
{
	@Override
	public String getName() 
	{ 
		return "I am a fish"; 
	}

	@Override
	public String getNoise()
	{
		return "The fish \"glugs\"";
	}

	@Override
	public String getMovement()
	{
		return "The fish swims";
	}
}
