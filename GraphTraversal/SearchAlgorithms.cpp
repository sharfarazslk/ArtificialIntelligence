//Sharfaraz Salek
//CS-380
//Implementation of Breadth First Search and Depth First Search
//C++11

#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <stack>
#include <ctime>
#include "Node.cpp"
using namespace std;

//Helper functions
//Checks whether state exists in closed list
bool inClosed(Bricks &Game, vector <Node*> closed,  Node& child)
{
	
	for (int j=0; j<closed.size(); j++)
	{
		if (Game.CompareStates(closed[j]->getState(), child.getState()))
		{
			return true;
		}
	}

	return false;
}

//constructs the path needed to get goal state
void constructpath(Node *current)
{
	if (current->getParent() != NULL)
	{
		constructpath(current->getParent());
		cout << "(" << current->getMove().i << "," << current->getMove().m << ")" << endl;
	}

}

//Breadth First Search with a closed list
void BFS(Bricks &Game)
{
	queue <Node*> open; //Open list
	vector <Node*> closed; //Closed list
	int stateidx = 0; //Keeps track of game state
	Game.Normalize(stateidx); //Normalizes game state
	open.push(new Node());
	
	//Searches for a solution till open list is empty
	while(open.size()>0)
	{
		//Remove node from open list
		Node *current = open.front();
		open.pop();

		//Check if goal state
		Game.SetBoard(current->getState()); 
		if(Game.Complete())
		{
			//Push node into closed list
			closed.push_back(current);
			constructpath(current);
			return Game.PrintState(current->getState());
		}

		//Add all children to open list
		Game.AllMoves(current->getState());
		vector<block> AllChildren = Game.ReturnAllMoves();
		for (int z = 0; z < AllChildren.size(); ++z)
		{
			Game.applyMoveCloning(current->getState(), AllChildren[z].i, AllChildren[z].m);
			stateidx++;
			Node child(current, stateidx, AllChildren[z]);
			Game.Normalize(child.getState());
			
			//Adds child to open list if not in closed
			if (!inClosed(Game, closed, child))
			{
				open.push(new Node(current, stateidx, AllChildren[z]));
			}

		}
		//Push node into closed list
		closed.push_back(current);
	}
}

//Depth First Search with closed list
void DFS (Bricks &Game)
{
	stack <Node*> open; //Open list 
	vector <Node*> closed; //Closed list
	int stateidx = 0; //Keeps track of game state
	Game.Normalize(stateidx); //Normalizes game state
	open.push(new Node());

	//Searches for a solution till open stack is empty
	while(open.size()>0)
	{
		//Remove node from open list
		Node *current = open.top();
		open.pop();

		//Check if  goal state
		Game.SetBoard(current->getState()); 
		if(Game.Complete())
		{
			//Push node into closed list and build path back to parent
			closed.push_back(current);
			constructpath(current);
			return Game.PrintState(current->getState());
		}

		//Add all children to open list
		Game.AllMoves(current->getState());
		vector<block> AllChildren = Game.ReturnAllMoves();
		for (int z = 0; z < AllChildren.size(); ++z)
		{
			Game.applyMoveCloning(current->getState(), AllChildren[z].i, AllChildren[z].m);
			stateidx++;
			Node child(current, stateidx, AllChildren[z]);
			Game.Normalize(child.getState());
			
			//Adds child to open list if not in closed
			if (!inClosed(Game, closed, child))
			{
				open.push(new Node(current, stateidx, AllChildren[z]));
			}

		}
		//Push node into closed list
		closed.push_back(current);

	}	
}
