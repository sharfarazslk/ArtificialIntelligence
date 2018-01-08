//Sharfaraz Salek
//CS-380
//Assignment - 1
//C++

#include "Sliding-Brick-Game.cpp"
#include <iostream>
using namespace std;


int main(int argc, char * argv[])
{
	bool solved;

	if (argc >2)
	{
		Bricks Game1;
		Game1.LoadGame(argv[1]);
		Game1.RandomWalk(0, atoi(argv[2]));
	}
	else
	{
		cout << "Please select a game file" << endl;
	}
	
	return 0;
}






