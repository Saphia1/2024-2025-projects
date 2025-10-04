package cw2b;
public class PGPTextFile extends PGPText 
{
	public static void main( String[] args )
	{
		PGPTextFile textfile = new PGPTextFile();
		textfile.load( "input.txt" );
		textfile.save( "output.txt");
	}
	
	// We will use this for reading and writing
	// This is a member variable/attribute - we are using aggregation 
	PGPFile file = new PGPFile();
	
	void load( String filename )
	{
		file.openReadFile(filename);
		String strLine;
		while ( (strLine = file.readNextLine()) != null )
			this.addLine(strLine);
		file.closeReadFile();
	}
	
	void save( String filename )
	{
		file.openWriteFile(filename);
		for ( int i = 0 ; i < this.getLineCount() ; i++ )
			file.writeLine( this.getLine(i) );
		file.closeWriteFile();		
	}
}
