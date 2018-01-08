//Sharfaraz Salek
//HW1
//Needed for HW2

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <queue>
using namespace std;

//Header File
struct pos
{
	int x; //x coordinate of brick
	int y; //y coordinate of brick

};

struct block
{
	int i; //Block Number
	char m; //Direction to be moved Inputs: 'u', 'd', 'l', 'r'
};


class Bricks{

public:
	//Constructor
	Bricks();

	//Inspectors
	void PrintState(int n);
	bool Complete();
	bool CompareStates(int a, int b); //Compares two states
	void CheckPiece(int a, int p); //takes piece number and state
	void AllMoves(int p); //Returns all moves available given a state
	vector < vector <int> > ReturnState(int n); //Returns a game state stored
	vector <block> ReturnAllMoves(); //Returns a list of all available moves
	vector <pos> GetGoal(); //Returns position of Goal Position

	//Mutators
	void LoadGame(string filename);
	void Clone(int a); //Requires a State to be cloned
	void applyMove(int p, int q, char r); //Given state, piece and move 
	void applyMoveCloning(int p, int q, char r); //Given state, piece and move 
	void RecordMove(int a, char s);
	void Normalize(int a); //Enter a state to normalize
	void swapIdx(int idx1, int idx2); //Normlization Helper function
	void RandomWalk(int a, int n); //Given State and maximum turns
	void SetBoard(int n); //Sets board to a given state
	void SetGoalPos(); //Sets X, Y position of the top left corner of the goal


private:
	vector< vector <int> > board;
	vector< vector < vector <int> > > states;
	vector <block> move;	
	int w_board;
	int h_board;
	vector <pos> goal;
};


// --------- Implementation -----------


//Helper Functions
void RecordMove(int &movenum, int a, char s);
//Implementing Bricks Class

//Constructor with empty board
Bricks::Bricks()
{

}

//Inspectors
void Bricks::PrintState(int n)
{
	//Print First Line
	cout << w_board << "," << h_board << "," << endl;

	//Printing rest
	for (int i =0; i < h_board; i++)
  	{
  		for (int j=0; j < w_board; j++)
  		{
  			cout << states[n][i][j] << ",";
  		}
  		
  		cout << endl;
  	}

}

bool Bricks::Complete()
{
	for (int i=0; i<h_board; i++)
	{
		for(int j=0; j<w_board; j++)
		{
			if(board[i][j] == -1)
			{
				return false;
			}
		}
	}

	return true;
}

bool Bricks::CompareStates(int a, int b)
{

	for (int i=0; i<h_board; ++i)
	{
		for (int j=0; j<w_board; ++j)
		{
			if (states[a][i][j] != states[b][i][j])
			{
				return false;
			}
		}
		
	}

	return true;
}

void Bricks::CheckPiece(int a, int p)
{
	
	//set current board to chosen state
	board = states[p];

	//Intialize position vector
	vector<pos> position;
	int idx = 0;

	//Find Position of Brick
	for(int i=0; i<h_board; ++i)
	{
		for(int j=0; j<w_board; ++j)
		{
			if (board[i][j] == a)
			{
				position.push_back(pos());
				position[idx].x = j;
				position[idx].y = i;
				idx++;
			}
		}
	}

	//Determine whether brick is horizontal/vertical/Square
	bool horz = true;
	bool vert = true;
	bool square = false;
	if (position.size()>1)
	{
		for(int i=0; i<position.size()-1; ++i)
		{
			if(position[i].x != position[i+1].x){vert=false;} //brick is horizontal
			if(position[i].y != position[i+1].y){horz=false;} //brick is vertical
		}

		if(position.size() == 4) {square = true;}	
	
	}
	
	//Find Spaces to move
	if(horz == true && vert == true && square == false) //Brick occupies one cell
	{
		if (a == 2)
		{
			//Empty cell or goal for master brick move up
			if (position[0].y>0 && (board[position[0].y-1][position[0].x] == 0 || 
				board[position[0].y-1][position[0].x] == -1 )) { RecordMove(a, 'u'); }

			//Empty cell or goal for master brick move down
			if (position[0].y<h_board-1 && (board[position[0].y+1][position[0].x] == 0 || 
				board[position[0].y+1][position[0].x] == -1 )) { RecordMove(a, 'd'); }

			//Empty cell or goal for master brick move left
			if (position[0].x>0 && (board[position[0].y][position[0].x-1] == 0 || 
				board[position[0].y][position[0].x-1] == -1 )) { RecordMove(a, 'l'); }

			//Empty cell or goal for master brick move right
			if (position[0].x<w_board-1 && (board[position[0].y][position[0].x+1] == 0 || 
				board[position[0].y][position[0].x+1] == -1 )) { RecordMove(a, 'r'); }

		}
		else
		{
			//Empty cell brick move up
			if (position[0].y>0 && board[position[0].y-1][position[0].x] == 0) 
				{ RecordMove(a, 'u'); }

			//Empty cell or goal for master brick move down
			if (position[0].y<h_board-1 && board[position[0].y+1][position[0].x] == 0) 
				{ RecordMove(a, 'd'); }

			//Empty cell move left
			if (position[0].x>0 && board[position[0].y][position[0].x-1] == 0) 
				{ RecordMove(a, 'l'); }

			//Empty cell move right
			if (position[0].x<w_board-1 && board[position[0].y][position[0].x+1] == 0) 
				{ RecordMove(a, 'r'); }
		}		

	}
	else if (horz == true && vert == false && square == false) //Horizontal Block
	{
		
		if (a == 2)
		{	
			//Cells up are empty/goal cells
			int legal = 1;
			for(int i=0; i<position.size(); ++i) 
			{
				if(position[i].y>0 && (board[position[i].y-1][position[i].x] == 0 || 
				board[position[i].y-1][position[i].x] == -1 ))
				{
					legal = legal*1;
				}
				else
				{
					legal = legal*0;
				}
			
			}
			if(legal == 1) { RecordMove(a, 'u'); }

			//Cells down are empty/goal cells
			legal = 1;
			for(int i=0; i<position.size(); ++i) 
			{
				if(position[i].y<h_board-1 && (board[position[i].y+1][position[i].x] == 0 || 
				board[position[i].y+1][position[i].x] == -1 ))
				{
					legal = legal*1;
				}
				else
				{
					legal = legal*0;
				}
			
			}
			if(legal == 1) { RecordMove(a, 'd'); }

			//Cell left are empty/goal cells
			if (position[0].x>0 && (board[position[0].y][position[0].x-1] == 0 || 
				board[position[0].y][position[0].x-1] == -1 )) 
			{ 
				
				RecordMove(a, 'l'); 
			}
			
			//Cell right are empty/goal cells
			int lastpos = position.size()-1;
			if (position[lastpos].x<w_board-1 && (board[position[lastpos].y][position[lastpos].x+1] == 0 || 
				board[position[lastpos].y][position[lastpos].x+1] == -1 )) { RecordMove(a, 'r'); }

		}	
		else
		{
			//Cells up are empty
			int legal = 1;
			for(int i=0; i<position.size(); ++i) 
			{
				if(position[i].y>0 && board[position[i].y-1][position[i].x] == 0)
				{
					legal = legal*1;
				}
				else
				{
					legal = legal*0;
				}
			
			}
			if(legal == 1) { RecordMove(a, 'u'); }

			//Cells down are empty/goal cells
			legal = 1;
			for(int i=0; i<position.size(); ++i) 
			{
				if(position[i].y<h_board-1 && board[position[i].y+1][position[i].x] == 0)
				{
					legal = legal*1;
				}
				else
				{
					legal = legal*0;
				}
			
			}
			if(legal == 1) { RecordMove(a, 'd'); }

			//Cell left are empty/goal cells
			if (position[0].x>0 && board[position[0].y][position[0].x-1] == 0) 
			{ 
				//cout << "HERE" << endl;
				RecordMove(a, 'l'); 
			}
			
			//Cell right are empty/goal cells
			int lastpos = position.size()-1;
			if (position[lastpos].x<w_board-1 && board[position[lastpos].y][position[lastpos].x+1] == 0) 
			{ 
				RecordMove(a, 'r'); 
			}
		}
	}
	else if (horz == false && vert == true && square == false) //verical Block
	{

		if (a == 2)
		{	
			//Cells up are empty/goal cells
			if (position[0].y>0 && (board[position[0].y-1][position[0].x] == 0 || 
				board[position[0].y-1][position[0].x] == -1 )) 
			{ 
				
				RecordMove(a, 'u'); 
			}

			
			//Cells down are empty/goal cells
			int lastpos = position.size()-1;
			if (position[lastpos].y<h_board-1 && (board[position[lastpos].y+1][position[lastpos].x] == 0 || 
				board[position[lastpos].y+1][position[lastpos].x] == -1 )) 
			{ 
				RecordMove(a, 'd'); 
			}

			//Cell left are empty/goal cells
			int legal = 1;
			for(int i=0; i<position.size(); ++i) 
			{
				if(position[i].x>0 && (board[position[i].y][position[i].x-1] == 0 || 
				board[position[i].y][position[i].x-1] == -1 ))
				{
					legal = legal*1;
				}
				else
				{
					legal = legal*0;
				}
			
			}
			if(legal == 1) { RecordMove(a, 'l'); }
			
			//Cell right are empty/goal cells
			legal = 1;
			for(int i=0; i<position.size(); ++i) 
			{
				if(position[i].x<w_board-1 && (board[position[i].y][position[i].x+1] == 0 || 
				board[position[i].y][position[i].x+1] == -1 ))
				{
					legal = legal*1;
				}
				else
				{
					legal = legal*0;
				}
			
			}
			if(legal == 1) { RecordMove(a, 'r'); }

		}
		else
		{
			//Cells up are empty/goal cells
			if (position[0].y>0 && board[position[0].y-1][position[0].x] == 0) 
			{ 
				RecordMove(a, 'u'); 
			}

			//Cells down are empty/goal cells
			int lastpos = position.size()-1;
			if (position[lastpos].y<w_board-1 && board[position[lastpos].y+1][position[lastpos].x] == 0) 
			{ 
				RecordMove(a, 'd'); 
			}

			//Cell left are empty/goal cells
			int legal = 1;
			for(int i=0; i<position.size(); ++i) 
			{
				if(position[i].x>0 && board[position[i].y][position[i].x-1] == 0)
				{
					legal = legal*1;
				}
				else
				{
					legal = legal*0;
				}
			
			}
			if(legal == 1) { RecordMove(a, 'l'); }
			
			//Cell right are empty/goal cells
			legal = 1;
			for(int i=0; i<position.size(); ++i) 
			{
				if(position[i].x<h_board-1 && board[position[i].y][position[i].x+1] == 0)
				{
					legal = legal*1;
				}
				else
				{
					legal = legal*0;
				}
			
			}
			if(legal == 1) { RecordMove(a, 'r'); }
		}	
	}

	else if (square == true) //Square Brick
	{
		if (a == 2)
		{
			
			if (position[0].y > 0 && ((board[position[0].y-1][position[0].x] == 0 && 
				board[position[1].y-1][position[1].x] == 0) || (board[position[0].y-1][position[0].x] == -1 
				&& board[position[1].y-1][position[1].x] == -1)))
				{
					RecordMove(a, 'u');
				}

			if (position[3].y < h_board-1 && ((board[position[2].y+1][position[2].x] == 0 && 
				board[position[3].y+1][position[3].x] == 0) || (board[position[2].y+1][position[2].x] == -1 
				&& board[position[3].y+1][position[3].x] == -1)))
				{
					RecordMove(a, 'd');
				}

			if (position[0].x > 0 && ((board[position[0].y][position[0].x-1] == 0 && 
				board[position[2].y][position[2].x-1] == 0) || (board[position[0].y][position[0].x-1] == -1 
				&& board[position[2].y][position[2].x-1] == -1)))
				{
					RecordMove(a, 'l');
				}

			if (position[3].x < w_board-1 && ((board[position[1].y][position[1].x+1] == 0 && 
				board[position[3].y][position[3].x+1] == 0) || (board[position[1].y][position[1].x+1] == -1 
				&& board[position[3].y][position[3].x+1] == -1)))
				{
					RecordMove(a, 'r');
				}
			
		}
		else
		{
			if (position[0].y > 0 && (board[position[0].y-1][position[0].x] == 0 && 
				board[position[1].y-1][position[1].x] == 0))
				{
					RecordMove(a, 'u');
				}

			if (position[3].y < h_board-1 && (board[position[2].y+1][position[2].x] == 0 && 
				board[position[3].y+1][position[3].x] == 0))
				{
					RecordMove(a, 'd');
				}

			if (position[0].x > 0 && (board[position[0].y][position[0].x-1] == 0 && 
				board[position[2].y][position[2].x-1] == 0))
				{
					RecordMove(a, 'l');
				}

			if (position[3].x < w_board-1 && (board[position[1].y][position[1].x+1] == 0 && 
				board[position[3].y][position[3].x+1] == 0))
				{
					RecordMove(a, 'r');
				}

		}
	}

}

void Bricks::RecordMove(int a, char s)
{
	move.push_back(block());
	move[move.size()-1].i = a;
	move[move.size()-1].m = s;
}

void Bricks::AllMoves(int p)
{
	//Clean move vector
	if (move.size()>0)
	{
		while(!move.empty())
		{
			move.pop_back();
		}
	}

	vector<int> pieces; //Record all pieces
	board = states[p]; //set board to chosen state

	for (int i=0; i<board.size(); ++i)
	{
		for (int j=0; j<board[i].size(); ++j)
		{
			bool member = false;
			if (pieces.size()==0 && board[i][j]>=2)
			{
				pieces.push_back(board[i][j]);
				member = true;
			}
			else if (pieces.size()>0 && board[i][j]>=2)
			{
				for (int z=0; z<pieces.size(); ++z)
				{
					if(board[i][j] == pieces[z])
					{
						member = true;
					}
				}
			
				if(member == false)
				{
					pieces.push_back(board[i][j]);
				}
			}
		}
	}

	
	for (int i =0; i < pieces.size(); ++i)
	{
		CheckPiece(pieces[i], p);
	}

}

vector <pos> Bricks::GetGoal()
{
	return goal;
}



//Mutators
void Bricks::LoadGame(string filename)
{
	//Declaration
	queue <int> inputread;
	string temp;

	//Open File
	ifstream inputfile(filename.c_str());

	//Parse each line as string
	if (inputfile.is_open())
	{
		while (getline(inputfile, temp))
		{
			stringstream ss(temp);
			while(getline(ss, temp, ','))
			{
				inputread.push(atoi(temp.c_str()));
			}
		}
		
		inputfile.close();
	} 
	
	//Width of Game
	w_board = inputread.front();
	inputread.pop();

	//Height of Game
	h_board = inputread.front();
	inputread.pop();

	
	//Building Game board vector
	board.resize(h_board, vector<int>(w_board));
	int h = 0;
  	while (!inputread.empty())
  	{
  		//Populate each row
  		int w =0;
	    while (w < w_board)
	    {
	    	board[h][w] = inputread.front();
	    	inputread.pop();
	    	w++;
	    }
  		
  		h++;	
  	}
  	
  	//Saving state
  	states.push_back(board);
}

void Bricks::Clone(int a)
{
	//cloned vector declaration
	vector <vector<int> > temp (h_board, vector<int>(w_board));

	//Clone vector and save state
	temp = states[a];
	states.push_back(temp);

}

void Bricks::applyMove(int p, int q, char m)
{
	//Intialize move
	vector <pos> m0;

	//set board to appropriate state
	board = states[p];

	//Current X-Y position
	int idx = 0;
	for(int i=0; i<board.size(); ++i)
	{
		for (int j=0; j<board[i].size(); ++j)
		{
			if(board[i][j] == q)
			{
				m0.push_back(pos());
				m0[idx].x = j;
				m0[idx].y = i;
				idx++;
			}
		}
	}

	//Empty Brick's old position
	for(int i =0; i<m0.size(); ++i)
	{
		board[m0[i].y][m0[i].x] = 0; //Turn position to 0 
	}

	//Put Brick into desired position
	switch(m)
	{
		case 'u': for(int i =0; i<m0.size(); ++i)
					{
						board[m0[i].y-1][m0[i].x] = q; //move up one spot 
					}
					break;
		
		case 'd': for(int i =0; i<m0.size(); ++i)
					{
						board[m0[i].y+1][m0[i].x] = q; //move down one spot
					}
					break;

		case 'l': for(int i =0; i<m0.size(); ++i)
					{
						board[m0[i].y][m0[i].x-1] = q; //move left one spot
					}
					break;

		case 'r': for(int i =0; i<m0.size(); ++i)
					{
						board[m0[i].y][m0[i].x+1] = q; //move right one spot
					}
					break;
	}

	//Save back to state
	states[p] = board;

}

void Bricks::applyMoveCloning(int p, int q, char m)
{
	//Clone Given State
	Clone(p);

	//Call applyMove with cloned state
	applyMove(states.size()-1, q, m);
}

void Bricks::Normalize(int a)
{
	//set board to appropriate state
	board = states[a];

	//Normalization function given
	int nextIdx = 3;
	for(int i=0; i< h_board; ++i)
	{
		for (int j=0; j<w_board; ++j)
		{
			if (board[i][j] == nextIdx)
			{
				nextIdx++;
			}
			else if (board[i][j] > nextIdx)
			{
				swapIdx(nextIdx, board[i][j]);
				nextIdx++;
			}
		}

	}
	
	states[a] = board;

}

void Bricks::swapIdx(int idx1, int idx2)
{
	for (int i=0; i<h_board; ++i)
	{
		for (int j=0; j<w_board; ++j)
		{
			if (board[i][j] == idx1)
			{
				board[i][j] = idx2;
			}
			else if (board[i][j] == idx2)
			{
				board[i][j] = idx1;
			}
		}
	}
}

void Bricks::RandomWalk(int a, int n)
{
	board = states[a]; //Set initial board
	PrintState(a); // Prints result
	cout << endl;
	int c; //random choice that will be generated

	//Randomly chose moves
	for (int i=0; i < n; ++i)
	{
		
		AllMoves(a); //Generate moves
		
		//When moves are aviable
		if (move.size()<1)
		{
			break;
		}
		else
		{
			//Chosing a move
			if (move.size() == 1)
			{
				c = 0;
			}
			else
			{
				srand (time(NULL));
				c = rand() % (move.size()-1); //generate radom move
			}
			
			cout << "(" << move[c].i << "," << move[c].m << ")" << endl << endl;

			//Apply move
			applyMove(a, move[c].i, move[c].m);
			
			//Normalize and Print
			Normalize(a);
			board = states[a];
			PrintState(a);
			cout << endl;

			if (Complete()) 
			{
				break;
			}

		}

	}

}

vector < vector <int> > Bricks::ReturnState(int n)
{
	return states[n];
}

void Bricks::SetBoard(int n)
{
	board = states[n];
}

vector <block> Bricks::ReturnAllMoves()
{
	return move;
}

void Bricks::SetGoalPos()
{
	int count = 0;

	for (int i=0; i <h_board; i++)
	{
		for (int j=0; j<w_board; j++)
		{
			if(board[i][j] == -1)
			{	
				goal.push_back(pos());
				goal[count].x = j;
				goal[count].y = i;
				count++;
			}
		}
	}
}