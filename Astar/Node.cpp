//Sharfaraz Salek
//CS-380
//Node Class Implementation
//C++11

#include "Sliding-Brick-Game.cpp"
using namespace std;

class Node{

private:
	Node *parent; //Parent node
	int state; //Index of current state in state vector
	block move; //Move to get to current state
	int g; //Distance from Initial State
	int h; //Heuristic
	int f; //Function = H + G
	pos master; //Position of MasterBrick

public:
	Node(); //Default Constructor
	Node(const Node &p1); //Copy constructor
	Node(Node *p, int s, block m, int a, int b, int c, pos d); //Alternate Constructor

	//Inspectors
	int getState(); 
	block getMove();
	Node* getParent();
	int getH(); 
	int getG(); 
	int getF(); 
	pos getMPos(); 
	
	//Mutators
	void setH(int a); 
	void setG(int b);
	void setF(int c);
	void setMPos(pos a);
};


//Node Implementation
//Default Constructor
Node::Node()
{
	parent = NULL;
	state = 0;
	move.i = -2; //Dummy value for initial declaration
	move.m = 'n'; //Dummy value for initial declaration
	g = 0;
	h = 0;
	f = 0;
	master.x = 0;
	master.y = 0;
}

//Alternate Constructor
Node::Node(Node *p, int s, block m, int a, int b, int c, pos d)
{
	parent = p;
	state = s;
	move = m;
	g = a;
	h = b;
	f = c;
	master.x = d.x;
	master.y = d.y; 
}

//Copy Constructor
Node::Node(const Node &p1)
{
	parent = new Node;
	*parent = *p1.parent;
	state = p1.state;
	move = p1.move;
	g = p1.g;
	h = p1.h;
	master = p1.master;
}

//Returns state index
int Node::getState()
{
	return state;
}

//Returns Move
block Node::getMove()
{
	return move;
}

//Returns Parent Node
Node* Node::getParent()
{
	return parent;
}

//Returns Distance from Goal
int Node::getH()
{
	return h;
}

//Returns Distance From Intial State
int Node::getG()
{
	return g;
}

//Returns F = H + G
int Node::getF()
{
	return f;
}

//Returns Master Brick Position in State
pos Node::getMPos()
{
	return master;
}

//Mutators
void Node::setG(int a)
{
	g = a;
}

void Node::setH(int b)
{
	h = b;
}

void Node::setF(int c)
{
	f = c;
}

void Node::setMPos(pos a)
{
	master.x = a.x;
	master.y = a.y;
}