package reversi;

public class ReversiController implements IController {

	IModel model;
	IView view;

	@Override
	public void initialise(IModel model,IView view)
	{
		this.model = model;
		this.view = view;
	}
	
	public void startup() {
		for (int y=0;y<8;y++) {
		     for (int x = 0; x < 8; x++) {
		    	model.setBoardContents(x,y,0);   	     	 
		     }
		}
		
		model.setBoardContents(3,3,1);
		model.setBoardContents(4,4,1);
		model.setBoardContents(3,4,2);
		model.setBoardContents(4,3,2);
		
		model.setPlayer(1);
		model.setFinished(false);
		view.refreshView();
	}
	
	public void update() {
		boolean whiteplay = canPlay(1);
		boolean blackplay = canPlay(2);
		
		if (!whiteplay && !blackplay) {
			model.setFinished(true);
			int white=0;
			int black=0;
			
			for (int y=0;y<8;y++) {
				for (int x=0;x<8;x++) {
					if (model.getBoardContents(x,y)==1) {
						white++;
					}
					else if (model.getBoardContents(x,y)==2) {
						black++;
					}
				}
			}
			
			if (white>black) {
				view.feedbackToUser(1,"White won. White " + white + " to Black " + black + ". Reset game to replay.");
				view.feedbackToUser(2,"White won. White " + white + " to Black " + black + ". Reset game to replay.");	
			}
			else if (black>white) {
				view.feedbackToUser(1,"Black won. Black " + black + " to White " + white + ". Reset game to replay.");
				view.feedbackToUser(2,"Black won. Black " + black + " to White " + white + ". Reset game to replay.");
			}
			else {
				view.feedbackToUser(1,"Draw. Both players ended with " + black + " pieces. Reset game to replay.");
				view.feedbackToUser(2,"Draw. Both players ended with " + black + " pieces. Reset game to replay.");
			}
			
			return;
		}
		
		model.setFinished(false);
		
		/*else if (model.hasFinished() == true && (whiteplay && blackplay) != false) {
			model.setFinished(false);
		}*/
		
		int currentPlayer=model.getPlayer();
		if(!canPlay(currentPlayer)) {
			model.setPlayer(otherPlayer(currentPlayer));
		}

		if (model.getPlayer() == 1) {//WHITE P1
			view.feedbackToUser(1,"White player – choose where to put your piece");
			view.feedbackToUser(2,"Black player – not your turn");
		}
		else {//BLACK P2
			view.feedbackToUser(2,"Black player – choose where to put your piece");
			view.feedbackToUser(1,"White player – not your turn");		
		}
		view.refreshView();//refresh the board now with the updates
		
	}
	
	@Override
	public void squareSelected( int player,int x,int y ) {
		//System.out.println("Player: " + player);
		//System.out.println("Actual: " + model.getPlayer());
		
		int other=otherPlayer(player);//gets other player
		if(model.hasFinished()==true) {
			return;
		}
		if ((model.getPlayer())!=player) {//IS NOT CORRECT PLAYER
			view.feedbackToUser(player,"It is not your turn!");
			return;
		}
		else if (canPlay(player)==false) {
			model.setPlayer(other);//switch player
			update();
			return;
		}
		else {//IS CORRECT PLAYER

			//IS THE MOVE VALID?
			if (isMoveValid(x,y,player)>0) {//MOVE VALID
				
				model.setBoardContents(x,y,player);//update board
				setCaptured(x,y,player);
				model.setPlayer(other);//switch player
				update();
				return;
			}
			
			else {//MOVE INVALID
				view.feedbackToUser(player,"Invalid location to play a piece.");
				view.refreshView();
			}
						
		}

	
	}
	
	public boolean canPlay(int player) {
		for (int y = 0;y< 8;y++) {
			for (int x = 0;x< 8;x++) {
				if ((model.getBoardContents(x,y)==0)&&(isMoveValid(x,y,player)>0)) {
					return true;
				}
			}
		}
		return false;
	}
	
	public int otherPlayer(int player) {
		int other = 0;//opposite player
		
		//setting other player based on who current player is
		if (player==1) {
			other = 2;
		}
		else {
			other = 1;
		}
		return other;
	}
	
	public int isMoveValid(int x,int y,int player) {
		if (model.getBoardContents(x,y)!=0) {//if tile is alreay_direction filled then not valid
			return 0;
		}
		int other = otherPlayer(player);
		int totalTiles = 0;

	    for (int x_offset = -1;x_offset <= 1;x_offset++) {//for every tile on right or left
	        for (int y_offset = -1;y_offset <= 1;y_offset++) {//for every tile above or below   	
	            if (x_offset == 0 && y_offset == 0) {//up by 0 and left/right by 0 is staying still so same tile
	            	continue; //skip current tile
	            }
	            
	            //getting tile coords for tile to check
	            int current_x_direction = x + x_offset;//add horizontal movement to tile
	            int current_y_direction = y + y_offset;//add vertical movement to tile
	            
	            boolean opponent = false;//boolean to register if we have encountered other player tile
	            
	            int tiles= 0;//how many tiles moved in current direction
	            
	            while (current_x_direction >= 0 && current_x_direction < 8 && current_y_direction >= 0 && current_y_direction < 8) {//keep moving in this direction until end of board
	                int piece = model.getBoardContents(current_x_direction,current_y_direction);//current tile contents
	                
	                if (piece == other) {//detected opponent tile
	                    opponent = true;
	                    tiles++;
	                } 
	                
	                else if (piece == player) {//if tile is player's own
	                    
	                	if (opponent) {//if detected opponent tile before
	                    	totalTiles += tiles;//valid
	                    }
	                    else {//if not detected opponent tile before
	                    	break; 
	                    }
	                } 
	                
	                else {//if empty square - stop checking direction 
	                    break;
	                }
	                
	                //increment
	                current_x_direction += x_offset;
	                current_y_direction += y_offset;
	            }
	        }
	    }
	    return totalTiles;//no valid possible directions
	}
	
	public void setCaptured(int x,int y,int player) {
		int other=otherPlayer(player);

	    for (int x_offset = -1;x_offset <= 1;x_offset++) {//for every tile on right or left
	        for (int y_offset = -1;y_offset <= 1;y_offset++) {//for every tile above or below   	
	            if (x_offset == 0 && y_offset == 0) {//up by 0 and left/right by 0 is staying still so same tile
	            	continue; //skip current tile
	            }
	            
	            //getting tile coords for tile to check
	            int current_x_direction = x + x_offset;//add horizontal movement to tile
	            int current_y_direction = y + y_offset;//add vertical movement to tile
	            
	            boolean opponent = false;//boolean to register if we have encountered other player tile
	            
	            int tiles= 0;//how many tiles moved in current direction
	            
	            while (current_x_direction >= 0 && current_x_direction < 8 && current_y_direction >= 0 && current_y_direction < 8) {//keep moving in this direction until end of board
	                int piece = model.getBoardContents(current_x_direction,current_y_direction);//current tile contents
	                
	                if (piece == other) {//detected opponent tile
	                    opponent = true;
		                //increment
		                current_x_direction += x_offset;
		                current_y_direction += y_offset;
	                    tiles++;
	                } 
	                
	                else if (piece == player && opponent==true) {//valid move found
	                    
	                	for (int i = 1;i <= tiles;i++) {
	                		int new_x = x + x_offset*i;
	                		int new_y = y + y_offset*i;
	                		model.setBoardContents(new_x,new_y,player);
	                	}
	                	break;  
	                } 
	                
	                else {//if empty square - stop checking direction 
	                    break;
	                }	         
	            }
	        }
	    }
	}
	

	public void doAutomatedMove( int player ) {//greedy ai 
		int bestmove = 0;
		int movex = -1;
		int movey = -1;
		int other = otherPlayer(player);
		if (model.hasFinished() == false){
			for (int y = -1;y< 8;y++) {
				for (int x = -1;x< 8;x++) {				
					//if empty tile and move takes more than prev move stored
					if ((model.getBoardContents(x,y)==0)&&(isMoveValid(x,y,player)>bestmove)) {
						bestmove=isMoveValid(x,y,player);
						movex=x;//store the coords
						movey=y;
					}
				}
			}
			model.setBoardContents(movex,movey,player);//update board
			setCaptured(movex,movey,player);
			model.setPlayer(other);//switch player
			update();
			return;
		}
		else {
			return;//if game has finished make sure button doesnt work
		}
		
	}


}

//comments
//System.out.print("Valid\n");
//System.out.print("Clicked tile\n");
//System.out.print("Clicked\n");
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
		frame1.setLocation(290,100); // centre on screen
		frame2.setLocation(700,100);
		
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
		
		
		message1.setFont( new Font( "Arial", Font.BOLD, 10 ));
		message2.setFont( new Font( "Arial", Font.BOLD, 10 ));
		
		// Now we add the 'stuff' for each player to the panel for that player...
		message1.setText("White player – choose where to put your piece");
		p1Panel.add(message1,BorderLayout.NORTH);

		
		// AI button
		JButton butAI1 = new JButton("Greedy AI (play white)");
		butAI1.addActionListener( new ActionListener() 
					{ public void actionPerformed(ActionEvent e) { controller.doAutomatedMove(1); } } );
		
		//Restart button
		JButton butRESTART1 = new JButton("Restart");
		butRESTART1.addActionListener( new ActionListener() 
					{ public void actionPerformed(ActionEvent e) { controller.startup(); } } );
		
		JPanel buttonPanel1 = new JPanel();
		buttonPanel1.setLayout( new GridLayout(2, 1) );
		buttonPanel1.add(butAI1);
		buttonPanel1.add(butRESTART1);
		p1Panel.add(buttonPanel1,BorderLayout.SOUTH);
		
		//Frame 2
		message2.setText("Black player – not your turn");
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
	         BoardSquareButton button = new BoardSquareButton(x, y,50,50,model,controller, Color.green,1,1,Color.black);
	         p1Buttons[x][y]=button;
	         p1gridPanel.add(button);
	       }
		}
			
		p1Panel.add(p1gridPanel, BorderLayout.CENTER);
		
		//BLACK
		for (int y=7;y>=0;y--) {
		     for (int x = 7; x>= 0; x--) {
		         BoardSquareButton button = new BoardSquareButton(x, y,50,50,model,controller, Color.green,1,2,Color.black);
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
		if ( player == 1 )
			message1.setText(message);
		else if ( player == 2 )
			message2.setText(message);	
	}

}






/*		if (player==1) {
			message1.setText(message);
			p1Panel.add(message1,BorderLayout.NORTH);

		}
		else {
			message2.setText(message);
			p2Panel.add(message2,BorderLayout.NORTH);
			
		}*/

//message1.setText("White player – choose where\r\n"
//		+ "to put your piece");
//p1Panel.add(message1,BorderLayout.NORTH);
//message2.setText("Black player – not your\r\n"
//		+ "turn");
//p2Panel.add(message1,BorderLayout.NORTH);

//else {
//	message1.setText("White player – not your\r\n"
//			+ "turn");
//	p1Panel.add(message1,BorderLayout.NORTH);
//	message2.setText("Black player – choose where to\r\n"
//			+ "put your piece");
//	p2Panel.add(message1,BorderLayout.NORTH);
//	
//}


//board1.setFont( new Font( "Consolas", Font.BOLD, 20 ));
//board2.setFont( new Font( "Consolas", Font.BOLD, 20 ));
//board1.setPreferredSize(new Dimension(400,330));
//board2.setPreferredSize(new Dimension(400,330));package reversi;


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
	int x,y,playerBoard;
	IModel model;
	IController controller;

	
	public BoardSquareButton(int x, int y, int width, int height, IModel model,IController controller, Color color,
			int borderWidth, int playerBoard, Color borderCol )
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
		this.playerBoard = playerBoard;
	}

	public BoardSquareButton( int width, int height, Color color )
	{
		// Call the other constructor with some default values
		this(-1,-1,width, height,null,null, color, 0, 0, null);
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
				g.setColor(Color.black);
				g.drawOval(2, 2, 46, 46);
				g.setColor(Color.white);
				g.fillOval(2, 2, 46, 46);
			}
			else if (piece == 2) {
				g.setColor(Color.white);
				g.drawOval(2,2, 46, 46);
				g.setColor(Color.black);
				g.fillOval(2,2, 46, 46);
			}
		}
		
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		controller.squareSelected(playerBoard, x, y);
	}
	

}