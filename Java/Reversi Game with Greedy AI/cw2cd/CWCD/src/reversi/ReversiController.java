package reversi;

public class ReversiController implements IController {

	IModel model;
	IView view;

	@Override
	public void initialise(IModel model, IView view)
	{
		this.model = model;
		this.view = view;
	}
	
	public void startup() {
		for (int y=0;y<8;y++) {
		     for (int x = 0; x < 8; x++) {
		    	model.setBoardContents(x, y, 0);   	     	 
		     }
		}
		
		model.setBoardContents(3, 3, 1);
		model.setBoardContents(4, 4, 1);
		model.setBoardContents(3, 4, 2);
		model.setBoardContents(4, 3, 2);
		
		view.feedbackToUser(1, "White player – choose where to put your piece");
		view.feedbackToUser(2, "Black player – not your turn");
		
		model.setPlayer(1);
		model.setFinished(false);
		view.refreshView();
	}
	
	public void update() {
		boolean whiteplay = canPlay(1);
		boolean blackplay = canPlay(2);
		
		if (!whiteplay && !blackplay) {
			model.setFinished(true);
			int white = 0;//how many pieces
			int black = 0;
			
			for (int y=0;y<8;y++) {
				for (int x=0;x<8;x++) {
					if (model.getBoardContents(x, y)==1) {
						white++;
					}
					else if (model.getBoardContents(x, y)==2) {
						black++;
					}
				}
			}
			
			if (white>black) {
				view.feedbackToUser(1, "White won. White " + white + " to Black " + black + ". Reset game to replay.");
				view.feedbackToUser(2, "White won. White " + white + " to Black " + black + ". Reset game to replay.");	
			}
			else if (black>white) {
				view.feedbackToUser(1, "Black won. Black " + black + " to White " + white + ". Reset game to replay.");
				view.feedbackToUser(2, "Black won. Black " + black + " to White " + white + ". Reset game to replay.");
			}
			else {
				view.feedbackToUser(1, "Draw. Both players ended with " + black + " pieces. Reset game to replay.");
				view.feedbackToUser(2, "Draw. Both players ended with " + black + " pieces. Reset game to replay.");
			}
			view.refreshView();//refresh the board now with the updates
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
			view.feedbackToUser(1, "White player – choose where to put your piece");
			view.feedbackToUser(2, "Black player – not your turn");
		}
		else {//BLACK P2
			view.feedbackToUser(2, "Black player – choose where to put your piece");
			view.feedbackToUser(1, "White player – not your turn");		
		}
		view.refreshView();//refresh the board now with the updates
		
	}
	
	@Override
	public void squareSelected( int player, int x, int y ) {		
		int other=otherPlayer(player);//gets other player
		
		if(model.hasFinished() == true) {
			return;
		}
		if ((model.getPlayer())!=player) {//IS NOT CORRECT PLAYER
			view.feedbackToUser(player, "It is not your turn!");
			return;
		}
		else if (canPlay(player) == false) {
			model.setPlayer(other);//switch player
			update();
			//return;
		}
		else {//IS CORRECT PLAYER

			//IS THE MOVE VALID?
			if (isMoveValid(x, y, player)>0) {//MOVE VALID
				
				model.setBoardContents(x, y, player);//update board
				setCaptured(x, y, player);
				model.setPlayer(other);//switch player
				update();
				//return;
			}
			
			else {//MOVE INVALID
				view.feedbackToUser(player, "Invalid location to play a piece.");
				view.refreshView();
			}
						
		}

	
	}
	
	public boolean canPlay(int player) {
		for (int y = 0;y< 8;y++) {
			for (int x = 0;x< 8;x++) {
				if ((model.getBoardContents(x, y)==0)&&(isMoveValid(x, y, player)>0)) {
					return true;
				}
			}
		}
		return false;
	}
	
	public int otherPlayer(int player) {
		int other = 0;//opposite player
		
		//setting other player based on who current player is
		if (player == 1) {
			other = 2;
		}
		else {
			other = 1;
		}
		return other;
	}
	
	public int isMoveValid(int x, int y, int player) {
		if (model.getBoardContents(x, y)!=0) {//if tile is already filled then not valid
			return 0;
		}
		int other = otherPlayer(player);
		int totalTiles = 0;//how many pieces captured

	    for (int x_offset = -1;x_offset <= 1;x_offset++) {//for every tile on right or left
	        for (int y_offset = -1;y_offset <= 1;y_offset++) {//for every tile above or below   	
	            if (x_offset == 0 && y_offset == 0) {//up by 0 and left/right by 0 is staying still so same tile
	            	continue; //skip current tile
	            }
	            
	            //getting tile coords for tile to check
	            int current_x_direction = x + x_offset;//add horizontal movement to tile
	            int current_y_direction = y + y_offset;//add vertical movement to tile
	            
	            boolean opponent = false;//boolean to register if we have encountered other player tile so can start counting
	            
	            int tiles= 0;//how many tiles moved in current direction
	            
	            while (current_x_direction >= 0 && current_x_direction < 8 && current_y_direction >= 0 && current_y_direction < 8) {//keep moving in this direction until end of board
	                int piece = model.getBoardContents(current_x_direction, current_y_direction);//current tile contents
	                
	                if (piece == other) {//detected opponent tile
	                    opponent = true;
	                    tiles++;
	                } 
	                
	                else if (piece == player) {//if tile is player's own
	                    
	                	if (opponent) {//if detected opponent tile before
	                    	totalTiles += tiles;//valid
	                    	break;
	                    }
	                    else {//if not detected opponent tile before
	                    	break; 
	                    }
	                } 
	                
	                else {//if empty square stop checking direction 
	                    break;
	                }
	                
	                //increment in next direction
	                current_x_direction += x_offset;
	                current_y_direction += y_offset;
	            }
	        }
	    }
	    return totalTiles;//returns most possible pieces that can be captured
	    //if return 0 then no valid possible directions
	}
	
	public void setCaptured(int x, int y, int player) {
		int other=otherPlayer(player);

	    for (int x_offset = -1;x_offset <= 1;x_offset++) {//for every tile on right or left
	        for (int y_offset = -1;y_offset <= 1;y_offset++) {//for every tile above or below   	
	            
	        	if (x_offset == 0 && y_offset == 0) {//skip current tile as up by 0 and left/right by 0 is staying still 
	            	continue;
	            }
	            
	            //getting tile coords for tile to check
	            int current_x_direction = x + x_offset;//add horizontal movement to tile
	            int current_y_direction = y + y_offset;//add vertical movement to tile
	            
	            boolean opponent = false;//boolean to register if we have encountered other player tile
	            
	            int tiles= 0;//how many tiles moved in current direction
	            
	            while (current_x_direction >= 0 && current_x_direction < 8 && current_y_direction >= 0 && current_y_direction < 8) {//keep moving in this direction until end of board
	                int piece = model.getBoardContents(current_x_direction, current_y_direction);//current tile contents
	                
	                if (piece == other) {//detected opponent tile
	                    opponent = true;
		                //increment
		                current_x_direction += x_offset;
		                current_y_direction += y_offset;
	                    tiles++;
	                } 
	                
	                else if (piece == player && opponent==true) {//valid move found
	                    
	                	for (int i = 1;i<= tiles;i++) {//set every piece in move to be player piece
	                		int new_x = x + x_offset*i;
	                		int new_y = y + y_offset*i;
	                		model.setBoardContents(new_x, new_y, player);
	                	}
	                	break;  
	                } 
	                
	                else {//if empty square encountered stop checking direction as end of move
	                    break;
	                }	         
	            }
	        }
	    }
	}
	

	public void doAutomatedMove( int player ) {//greedy ai
		int other=otherPlayer(player);//gets other player
		if(model.hasFinished() == true) {
			return;
		}
		if ((model.getPlayer()) != player) {//IS NOT CORRECT PLAYER
			view.feedbackToUser(player, "It is not your turn!");
			return;
		}
		else if (canPlay(player) == false) {
			model.setPlayer(other);//switch player
			update();
			return;
		}
		else {
			int bestcaptured = 0;//numb captured pieces
			int movex = 0;
			int movey = 0;
			

			if (model.hasFinished() == true) {
				return;//if game has finished make sure button doesnt work
			}
			else if (model.hasFinished() == false){
				for (int y = 0;y< 8;y++) {
					for (int x = 0;x< 8;x++) {								
						if (model.getBoardContents(x, y)==0) {//if empty tile 
							int captured = isMoveValid(x, y, player);					
							if (captured>bestcaptured) {//if move takes more than prev move stored
								bestcaptured = captured;
								movex = x;//store the coords
								movey = y;

							}						
						}
					}
				}
				
				if (bestcaptured>0) {//if a move was found
					model.setBoardContents(movex, movey, player);//update board
					setCaptured(movex, movey, player);
					model.setPlayer(other);//switch player
					update();
					//return;
				}
		}
		
		}		
	}



}

//comments
//System.out.print("Valid\n");
//System.out.print("Clicked tile\n");
//System.out.print("Clicked\n");
