//Sharfaraz Salek
//CS-380
//Implementation of Breadth First Search and Depth First Search
//C++11

#include <iostream>
#include <string>
#include "SearchAlgorithms.cpp"
using namespace std;

int main(int argc, char * argv[])
{
	string searchtype;

	if (argc > 2)
	{
		//Initialize Game
		Bricks Game1;
		Game1.LoadGame(argv[1]);
		
		//Execute Game depending on chose search
		searchtype = argv[2];
		if (searchtype == "dfs")
		{
			DFS(Game1);	
		}
		else if (searchtype == "bfs")
		{
			BFS(Game1);
		}
		else
		{
			cout << "Please select bfs or dfs as searchtype" << endl;
		}
		
	}
	else
	{
		cout << "Please select a level and a searchtype" << endl;
	}
	
	return 0;
}