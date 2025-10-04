package cw2b;

public class Cw2b extends BaseClass{
	
	private PGPText movement;
	private PGPText noises;
	
	public Cw2b() {
		this.movement = new PGPText();
		this.noises = new PGPText();
	}

	@Override
	public void createAnimals()
	{
		Animal bird1 = new Bird();
		storeAnimal(bird1);
		Animal bird2 = new Bird();
		storeAnimal(bird2);
		Animal fish1 = new Fish();
		storeAnimal(fish1);
		Animal lion1 = new Lion();
		storeAnimal(lion1);
		Animal mouse1 = new Mouse();
		storeAnimal(mouse1);
		Animal mouse2 = new Mouse();
		storeAnimal(mouse2);
	}
	
	@Override
	public void recordMoved( String str )
	{
		System.out.println(str);
		movement.addLine(str);
	}
	
	@Override
	public void recordMadeSound( String str )
	{
		System.out.println(str);
		noises.addLine(str);
	}
	
	@Override
	public void finish()
	{
		PGPFile file = new PGPFile();
		file.openWriteFile("output.txt");
		file.writeLine("List of noises made:");
		for (int i = 0; i < noises.getLineCount(); i++) 
		{ 
			file.writeLine(noises.getLine(i));
		}
		file.writeLine("List of movement made:");
		for (int i = 0; i < movement.getLineCount(); i++) 
		{ 
			file.writeLine(movement.getLine(i));
		}
		file.closeWriteFile();
	}
}
