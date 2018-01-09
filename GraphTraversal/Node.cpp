//Sharfaraz Salek
//CS-380
//Node Class Implementation
//C++11

#include "Sliding-Brick-Game.cpp"
using namespace std;

//Data Structure to help with Graph Traversal
class Node{

public:
	Node(); //Default Constructor
	Node(const Node &p1); //Copy constructor
	Node(Node *p, int s, block m); //Alternate Constructor
	

	//Inspectors
	int getState(); 
	block getMove();
	Node* getParent();

private:
	Node *parent;
	int state;
	block move;
};


//Node Implementation
//Default Constructor
Node::Node()
{
	parent = NULL;
	state = 0;
	move.i = 0;
	move.m = 'c';
}

//Alternate Constructor
Node::Node(Node *p, int s, block m)
{
	parent = p;
	state = s;
	move = m;
}

//Copy Constructor
Node::Node(const Node &p1)
{
	parent = new Node;
	*parent = *p1.parent;
	state = p1.state;
	move = p1.move;
}

//Returns index for state in state vector
int Node::getState()
{
	return state;
}

//move that led to stored state
block Node::getMove()
{
	return move;
}

//Returns parent node
Node* Node::getParent()
{
	return parent;
}