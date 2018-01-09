package cs380.othello;

/*
* Implementation of minimax strategy to play Othello
* Meant to be played with Othello class provided for the exercise
*/

import java.util.*;

/**
*
* @author Sharfaraz
*/

public class ss3783MiniMax extends OthelloPlayer {
	int depth_limit;

	public ss3783MiniMax(int depth){
		//Sets depth limit for how deep to traverse
		depth_limit = depth;
	}

	OthelloMove endMove = new OthelloMove(0,0,0);
	public int minimax(OthelloState state, int depth)
	{
		int min, max;
		int index;
		List<OthelloMove> movesList = state.generateMoves();
		List <Integer> score = new LinkedList<Integer>();
		List<OthelloMove> moves = new LinkedList<OthelloMove>();
		OthelloState temp = new OthelloState(depth_limit);

		//Calculating Score
		//No more moves or depth specified reached
		if (movesList.size() == 0 || depth >= depth_limit)
		{
			return state.score();
		}

		depth++;
		
		for (int i=0; i< movesList.size(); i++)
		{
			temp = state.applyMoveCloning(movesList.get(i));
			score.add(minimax(temp, depth));
			moves.add(movesList.get(i));
		}

		//Use min or max based on player
		if (state.nextPlayerToMove == 0)
		{
			max = Collections.max(score);
			index = score.indexOf(max);
			endMove = moves.get(index);
			return score.get(index);
		}
		else if (state.nextPlayerToMove == 1)
		{
			min = Collections.min(score);
			index = score.indexOf(min);
			endMove = moves.get(index);
			return score.get(index);
		}

		return 0;

	}

	public OthelloMove getMove(OthelloState state){

			int result = minimax(state, 0);
			return endMove;

	}
}