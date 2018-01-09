//Sharfaraz Salek
//CS-380
//Implementaion of A* Search Algorithm
//C++11

#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <cmath>
#include <list>
#include "Node.cpp"
using namespace std;

//Helper Functions 
//checks whether child is in closed list
bool inClosed(Bricks &Game, vector <Node*> closed,  Node* child)
{
	
	for (int j=0; j<closed.size(); j++)
	{
		if (Game.CompareStates(closed[j]->getState(), child->getState()))
		{
			return true;
		}
	}

	return false;
}

//Constructs path to goal state from initial state
void constructPath(Node *current)
{
	if (current->getParent() != NULL)
	{
		constructPath(current->getParent());
		cout << "(" << current->getMove().i << "," << current->getMove().m << ")" << endl;
	}

}

//Creates a vector contatining position for the masterbrick
pos masterInitial(Bricks &Game, int &g_x, int &g_y)
{
	vector < vector <int> > state = Game.ReturnState(0);
	vector <pos> master;
	int count = 0;

	//Record Position of Master Brick
	for (int i=0; i<state.size(); i++)
	{
		for (int j=0; j<state[i].size(); j++)
		{
			if (state[i][j] == 2)
			{
				master.push_back(pos());
				master[count].y = i;
				master[count].x = j;
				count++;
			}
		}
	}
	
	//Determine whether to get top left of Goal or bottom right
	vector <pos> goalPos = Game.GetGoal();
	if (goalPos[0].x == 0 or goalPos[0].y == 0)
	{
		g_x = goalPos[0].x;
		g_y = goalPos[0].y;
	}
	else
	{
		g_x = goalPos[goalPos.size()-1].x;
		g_y = goalPos[goalPos.size()-1].y;	
	}

	//Returns the top left position of the master brick if goal is on top or left
	//Return the bottom right position of the master brick if goal is on botton or right 
	if (g_x == 0 or g_y == 0)
	{
		pos topleft;
		topleft.x = master[0].x;
		topleft.y = master[0].y;
		return  topleft;
	}
	else
	{
		pos botright;
		botright.x = master[master.size()-1].x;
		botright.y = master[master.size()-1].y;
		return  botright;	
	}
}

//Heuristic Function: Manhattan Distance
void heuristic(int &g_x, int &g_y, Node* p)
{
	//Calculate heuristic from either top left or bottom right
	int m_x = p->getMPos().x;
	int m_y = p->getMPos().y;
	int heuristic;
	heuristic = abs(g_y - m_y) + abs(g_x - m_x); 
	p->setH(heuristic); //Distance from goal + distance from start
	p->setF(heuristic + p->getG());//F(n) = h(n) + g(n)
}

//Helper function to help calculate position of master brick after move has been applied
pos MPos(Node *N, block &AllChildren)
{
	char move = AllChildren.m;
	pos newPos;

	if (AllChildren.i == 2)
	{
		switch(move)
		{
			case 'u':	newPos.y = N->getMPos().y - 1; //Moves up one spot
						newPos.x = N->getMPos().x; //Same X Position
						return newPos;
			
			case 'd': 	newPos.y = N->getMPos().y + 1; //Moves down one spot
						newPos.x = N->getMPos().x; //Same X Position
						return newPos;

			case 'l':	newPos.y = N->getMPos().y; //Same Y position
						newPos.x = N->getMPos().x - 1; //Move left one position
						return newPos;

			case 'r': 	newPos.y = N->getMPos().y; //Same Y position
						newPos.x = N->getMPos().x + 1; //Move right one position
						return newPos;

			default:	cout << "Error in MPos" << endl; //Error Handling
						return newPos; 	
		}
	}
	else
	{
		//If Masterbrick has not been moved
		newPos.y = N->getMPos().y; 
		newPos.x = N->getMPos().x; 
		return newPos;
	}
}

//Insertion sort for open list
void openInsert(list <Node*> &open, Node* child)
{
	bool inserted = false;

	if (open.empty())
	{
		open.push_back(new Node(child->getParent(), child->getState(), 
			child->getMove(), child->getG(), child->getH(), child->getF(), child->getMPos()));
		inserted = true;
	}
	else
	{
		//Iterates and finds correct position to enter into open list i.e. ascending in terms of F(n)
		for (list <Node*>::iterator it = open.begin(); it != open.end(); ++it)
		{
			if (child->getF() <= (*it)->getF())
			{
				open.insert(it, new Node(child->getParent(), child->getState(), 
					child->getMove(), child->getG(), child->getH(), child->getF(), child->getMPos()));
				inserted = true;
				break;
			}
		}

	}

	//When Node F(n) is greater than rest of list
	if(!inserted) 
	{
		open.push_back(new Node(child->getParent(), child->getState(), 
				child->getMove(), child->getG(), child->getH(), child->getF(), child->getMPos()));
	}
}

void Astar(Bricks &Game)
{

	//Normalizing and Recording Goal Coordinates
	int stateidx = 0;
	Game.Normalize(stateidx);
	Game.SetGoalPos();
	int g_x = 0;
	int g_y = 0;
	
	//Creating Initial Node
	list <Node*> open;
	open.push_back(new Node());
	open.front()->setMPos(masterInitial(Game, g_x, g_y));
	heuristic(g_x, g_y, open.front()); //calls heuristic on initial state

	//Loop through children till goal state is reached
	vector<Node*> closed;
	while (!open.empty())
	{
		Node* N = open.front(); //open is insertion sorted in ascending heuristic value
		open.pop_front();

		//If the given node is already in the closed node then the most optimal configuration from that Node alerady explored
		//This is because open list is sorted in ascending F(n). Optimizes and reduces number of nodes that need to be explored
		if(inClosed(Game, closed, N))
		{
			continue; //moves on to next element
		}
		Game.SetBoard(N->getState());

		//Checks to see if game is complete
		if(Game.Complete())
		{
			constructPath(N);
			return Game.PrintState(N->getState());	
		}

		//Add to closed list
		closed.push_back(N);

		//Add children to Open list when not in closed list
		Game.AllMoves(N->getState());
		vector<block> AllChildren = Game.ReturnAllMoves();
		for (int z = 0; z < AllChildren.size(); z++)
		{
			//Finds Child Nodes, intiializes, Normalizes and adds to open list if not duplicate state
			Game.applyMoveCloning(N->getState(), AllChildren[z].i, AllChildren[z].m); 
			stateidx++;
			Node child(N, stateidx, AllChildren[z], N->getG()+1, 0, 0, MPos(N, AllChildren[z])); //write function for MPos
			Game.Normalize(child.getState());
			heuristic(g_x, g_y, &child);
			
			//Adds child to open list only if not in closed
			if (!inClosed(Game, closed, &child))
			{
				openInsert(open, &child);
			}	

		}
	
	}

}