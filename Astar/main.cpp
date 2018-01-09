//Sharfaraz Salek
//Implementaion of A* Search Algorithm
//C++11

#include <iostream>
#include "Astar.cpp"
using namespace std;

int main(int argc, char * argv[])
{
	string searchtype; 

	if (argc > 1)
	{
		//Initialize Game
		Bricks Game1;
		Game1.LoadGame(argv[1]);
		Astar(Game1);		
	
	}
	else
	{
		cout << "Please select a game to play" << endl;
	}
	
	return 0;
}