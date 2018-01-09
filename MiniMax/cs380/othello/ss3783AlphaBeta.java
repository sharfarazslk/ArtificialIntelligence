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

public class ss3783AlphaBeta extends OthelloPlayer {
	int depth_limit;

	public ss3783AlphaBeta(int depth){
		//Sets depth limit for how deep to traverse
		depth_limit = depth;
	}

	OthelloMove endMove = new OthelloMove(0,0,0);
	public int alphaBeta(OthelloState state, int depth, int alpha, int beta)
	{
		int min, max;
		int index;
		List<OthelloMove> movesList = state.generateMoves();
		LinkedList <Integer> score = new LinkedList<Integer>();
		List<OthelloMove> moves = new LinkedList<OthelloMove>();
		OthelloState temp = new OthelloState(depth_limit);

		//Calculating Score
		//No more moves or depth specified reached
		if (movesList.size() == 0 || depth >= depth_limit)
		{
			return state.score();
		}

		depth++;
		
		for (int i=0; i < movesList.size(); i++)
		{
			temp = state.applyMoveCloning(movesList.get(i));
			score.add(alphaBeta(temp, depth, alpha, beta));
			moves.add(movesList.get(i));

			//Alpha Beta pruning
			if (score.size() > 0)
			{
				if (state.nextPlayerToMove == 0)
				{
					if (score.getLast() > alpha)
					{
						alpha = score.getLast();
					}
				}
				else if (state.nextPlayerToMove == 1)
				{
					if (score.getLast() < beta)
					{
						beta = score.getLast();
					}
				}
			}

			//Prune this tree
			if (alpha >= beta) break;
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

			int alpha = -1000; 
			int beta = 1000;
			int result = alphaBeta(state, 0, alpha, beta);
			return endMove;

		
	}
}