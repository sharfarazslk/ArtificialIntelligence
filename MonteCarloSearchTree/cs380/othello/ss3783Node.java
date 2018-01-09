package cs380.othello;

import java.util.*;

/**
* @author Sharfaraz
**/

public class ss3783Node {
	
	int timesVisited = 0;
	int averageScore = 0;
	OthelloState state = null;
	ss3783Node parent = null;
	OthelloMove currentMove = null;
	List<OthelloMove> movesList = null;
	List<ss3783Node> children = new LinkedList<ss3783Node>();

	public ss3783Node(OthelloState s) {
		state = s;
		movesList = state.generateMoves();
	}

	public void setParent(ss3783Node p) {
		parent = p;
	}

	public void setMove(OthelloMove m) {
		currentMove = m;
	}

	public ss3783Node getParent() {
		return parent;
	}

	public OthelloMove returnMove() {
		return currentMove;
	}

	public int getScore() {
		return averageScore;
	}

	//Determining Best Child to Explore
	public ss3783Node bestChild() {
		
		if (children.size() != 0) {
			int max = children.get(0).getScore();
			int min = children.get(0).getScore();
			int index = 0;

			if (state.nextPlayerToMove == 0) {
				
				for (int i=1; i<children.size(); i++){
					if (max < children.get(i).getScore()){
						max = children.get(i).getScore();
						index = i; 
					}
				}
				return children.get(index); 
			}
			else if (state.nextPlayerToMove == 1) {
				
				for (int i=1; i<children.size(); i++){
					if (min > children.get(i).getScore()){
						min = children.get(i).getScore();
						index = i; 
					}
				}
				return children.get(index);
			}

		} 
	
		return null;
	}

	//Policy to determine which tree to traverse
	public ss3783Node treePolicy() {
		if (movesList.size() == 0) { //Terminal with no children
			return this;
		}
		else if (movesList.size() != children.size()) { //When all children are not in tree
			//Create Child Node 
			children.add(new ss3783Node(state.applyMoveCloning(movesList.get(children.size()))));
			children.get(children.size()-1).setParent(this);
			children.get(children.size()-1).setMove(movesList.get(children.size()-1));
			return children.get(children.size()-1);
		}
		else if (movesList.size() == children.size()) { //Terminal and all children it tree
			Random rand = new Random();
			int greedy = rand.nextInt(10) + 1;
			int index = rand.nextInt(children.size());
			
			if (greedy <= 9) {
				return this.bestChild();
			}
			else if (greedy > 9) {
				return children.get(index);
			} 
		}

		return null;
	}

	public int defaultPolicy() {
		OthelloPlayer players[] = {new OthelloRandomPlayer(), new OthelloRandomPlayer()};
        OthelloState tmpState = state;
        do{
            // Get the move from the player:
            OthelloMove nextMove = players[state.nextPlayerToMove].getMove(tmpState);           
            tmpState = tmpState.applyMoveCloning(nextMove);            
        }while(!tmpState.gameOver());

        return tmpState.score();
	}

	public void backup(int newScore) {
		int tmpScore = averageScore*timesVisited;
		tmpScore = tmpScore + newScore;
		timesVisited += 1;
		averageScore = tmpScore/timesVisited;
		if (parent != null) {
			parent.backup(newScore);
		}

	}

}

