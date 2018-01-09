package cs380.othello;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.util.List;

/**
 *
 * @author Sharfaraz
 */

public class ss3783mcstPlayer extends OthelloPlayer {
    int iterations;

   	public ss3783mcstPlayer(int i) {
   		iterations = i;
   	} 

   	public OthelloMove MCST(OthelloState state, int iterations) {
   		ss3783Node root = new ss3783Node(state);
   		for (int i=0; i<iterations; i++) {
   			ss3783Node node = root.treePolicy();
   			if (node != null) {
   				int nodeScore = node.defaultPolicy();
   				node.backup(nodeScore);
   			}

   		}
      return root.bestChild().returnMove();
   	}
    
    public OthelloMove getMove(OthelloState state) {
    	OthelloMove move = MCST(state, iterations);
    	return move;

    }
    
}