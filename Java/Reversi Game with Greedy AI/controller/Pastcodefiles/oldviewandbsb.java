package reversi;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextArea;

public class GUIView implements IView {
	IModel model;
	IController controller;
	private BoardSquareButton[][] p1Buttons = new BoardSquareButton[8][8];
	private BoardSquareButton[][] p2Buttons = new BoardSquareButton[8][8];
	
	/**
	 * Constructor
	 */
	public GUIView()
	{
	}
	
	JLabel message1 = new JLabel();
	JLabel message2 = new JLabel();
	JTextArea board1 = new JTextArea();
	JTextArea board2 = new JTextArea();
	JFrame frame1 = new JFrame();
	JFrame frame2 = new JFrame();
	JPanel p2Panel = new JPanel();
	JPanel p1Panel = new JPanel();
	
	@Override
	public void initialise( IModel model, IController controller ){
		this.model = model;
		this.controller=controller;
		
	
		frame1.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame2.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		frame1.setTitle("Reversi Interface - white player");
		frame2.setTitle("Reversi Interface - black player");
		frame1.setLocationRelativeTo(null); // centre on screen
		frame2.setLocationRelativeTo(null);
		
		frame1.getContentPane().setLayout(new GridLayout(1,2));
		frame2.getContentPane().setLayout(new GridLayout(1,2));
		
		board1.setBorder(BorderFactory.createEmptyBorder(5, 5, 5, 5) );
		
		JPanel p1Panel = new JPanel();
		
		p1Panel.setBorder( BorderFactory.createLineBorder(Color.LIGHT_GRAY,3) );
		
		p1Panel.setLayout( new BorderLayout() );
		
		frame1.add(p1Panel);
		
		
		board2.setBorder(BorderFactory.createEmptyBorder(5, 5, 5, 5) );
		JPanel p2Panel = new JPanel();
		p2Panel.setBorder( BorderFactory.createLineBorder(Color.BLACK,3) );
		p2Panel.setLayout( new BorderLayout() );
		frame2.getContentPane().add(p2Panel);
		
		
		message1.setFont( new Font( "Arial", Font.BOLD, 20 ));
		message2.setFont( new Font( "Arial", Font.BOLD, 20 ));

		//board1.setFont( new Font( "Consolas", Font.BOLD, 20 ));
		//board2.setFont( new Font( "Consolas", Font.BOLD, 20 ));
		//board1.setPreferredSize(new Dimension(400,330));
		//board2.setPreferredSize(new Dimension(400,330));
		
		// Now we add the 'stuff' for each player to the panel for that player...
		message1.setText("Initial text goes here");
		p1Panel.add(message1,BorderLayout.NORTH);

		
		// AI button
		JButton butAI1 = new JButton("Greedy AI (play white)");
		butAI1.addActionListener( new ActionListener() 
					{ public void actionPerformed(ActionEvent e) { controller.doAutomatedMove(1); } } );
		
		//Restart button
		JButton butRESTART1 = new JButton("Restart");
		butRESTART1.addActionListener( new ActionListener() 
					{ public void actionPerformed(ActionEvent e) { controller.doAutomatedMove(1); } } );
		
		JPanel buttonPanel1 = new JPanel();
		buttonPanel1.setLayout( new GridLayout(2, 1) );
		buttonPanel1.add(butAI1);
		buttonPanel1.add(butRESTART1);
		p1Panel.add(buttonPanel1,BorderLayout.SOUTH);
		
		//Frame 2
		message2.setText("Initial text goes here");
		p2Panel.add(message2,BorderLayout.NORTH);
		
		// AI button
		JButton butAI2 = new JButton("Greedy AI (play black)");
		butAI2.addActionListener( new ActionListener() 
					{ public void actionPerformed(ActionEvent e) { controller.doAutomatedMove(2); } } );
		
		
		//Restart button
		JButton butRESTART2 = new JButton("Restart");
		butRESTART2.addActionListener( new ActionListener() 
					{ public void actionPerformed(ActionEvent e) { controller.doAutomatedMove(1); } } );
				
		JPanel buttonPanel2 = new JPanel();
		buttonPanel2.setLayout( new GridLayout(2, 1) );
		buttonPanel2.add(butAI2);
		buttonPanel2.add(butRESTART2);
		p2Panel.add(buttonPanel2,BorderLayout.SOUTH);

		JPanel p1gridPanel = new JPanel(new GridLayout(8, 8));
		JPanel p2gridPanel = new JPanel(new GridLayout(8, 8));

	    //WHITE
		for (int y=0;y<8;y++) {
	     for (int x = 0; x < 8; x++) {
	         BoardSquareButton button = new BoardSquareButton(x, y,50,50,model,controller, Color.green,1,Color.black);
	         p1Buttons[x][y]=button;
	         p1gridPanel.add(button);
	       }
		}
			
		p1Panel.add(p1gridPanel, BorderLayout.CENTER);
		
		//BLACK
		for (int y=7;y>=0;y--) {
		     for (int x = 7; x>= 0; x--) {
		         BoardSquareButton button = new BoardSquareButton(x, y,50,50,model,controller, Color.green,1,Color.black);
		         p2Buttons[x][y]=button;
		         p2gridPanel.add(button);
		       }
			}
	     // Add grid to center
	     p2Panel.add(p2gridPanel, BorderLayout.CENTER);

	 	frame1.pack();
		frame2.pack();
		frame1.setVisible(true);
		frame2.setVisible(true);   

		
	}
	
	/**
	 * Refresh the display
	 */
	@Override
	public void refreshView() {
		for (int y=0;y<8;y++) {
		     for (int x = 0; x < 8; x++) {
		         p1Buttons[y][x].repaint();
		         p2Buttons[7-y][7-x].repaint();
		       }
			}

	}
	
	/**
	 * Display a feedback message to the user
	 * @param player Which player to tell, 1 (white) or 2 (black).
	 * @param message The message to display.
	 */
	@Override
	public void feedbackToUser( int player, String message ){
		if (player==1) {
			message1.setText(message);
			p1Panel.add(message1,BorderLayout.NORTH);
			//message1.setText("White player – choose where\r\n"
			//		+ "to put your piece");
			//p1Panel.add(message1,BorderLayout.NORTH);
			//message2.setText("Black player – not your\r\n"
			//		+ "turn");
			//p2Panel.add(message1,BorderLayout.NORTH);
		}
		else {
			message2.setText(message);
			p2Panel.add(message2,BorderLayout.NORTH);
			
		}
		//else {
		//	message1.setText("White player – not your\r\n"
		//			+ "turn");
		//	p1Panel.add(message1,BorderLayout.NORTH);
		//	message2.setText("Black player – choose where to\r\n"
		//			+ "put your piece");
		//	p2Panel.add(message1,BorderLayout.NORTH);
		//	
		//}
		
		
	}

}

package reversi;


import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
//You will need to draw a green square, a black border, and white/black circle with a border around the circle in the opposite colour.
public class BoardSquareButton extends JButton implements ActionListener
{
	Color drawColor; 
	Color borderColor;
	int borderSize;
	int x,y;
	IModel model;
	IController controller;

	
	public BoardSquareButton(int x, int y, int width, int height, IModel model,IController controller, Color color,
			int borderWidth, Color borderCol )
	{
		this.x =x;
		this.y =y;
		this.model=model;
		this.controller=controller;
		borderSize = borderWidth;
		addActionListener(this);
		drawColor = color;
		borderColor = Color.black;
		setMinimumSize( new Dimension(width, height) );
		setPreferredSize( new Dimension(width, height) );
	}

	public BoardSquareButton( int width, int height, Color color )
	{
		// Call the other constructor with some default values
		this(-1,-1,width, height,null,null, color, 0, null );
	}

	public Color getDrawColor()
	{
		return drawColor;
	}

	public void setDrawColor(Color drawColor)
	{
		this.drawColor = drawColor;
	}

	public Color getBorderColor()
	{
		return borderColor;
	}

	public void setBorderColor(Color borderColor)
	{
		this.borderColor = borderColor;
	}

	public int getBorderSize()
	{
		return borderSize;
	}

	public void setBorderSize(int borderSize)
	{
		this.borderSize = borderSize;
	}

	protected void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		if ( borderColor != null )
		{
			g.setColor(borderColor);
			g.fillRect(0, 0, getWidth(), getHeight());
		}
		if ( drawColor != null )
		{
			g.setColor(drawColor);
			g.fillRect(borderSize, borderSize, getWidth()-borderSize*2, getHeight()-borderSize*2);
		}
		if(model !=null) {
			int piece= model.getBoardContents(x, y);
			if (piece == 1) {
				g.setColor(Color.white);
				g.drawOval(2, 2, 46, 46);
				g.setColor(Color.black);
				g.fillOval(2, 2, 46, 46);
			}
			else if (piece == 2) {
				g.setColor(Color.black);
				g.drawOval(2,2, 46, 46);
				g.setColor(Color.white);
				g.fillOval(2,2, 46, 46);
			}
		}
		
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		controller.squareSelected(model.getPlayer(), x, y);
	}
	

}