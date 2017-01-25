#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class tictactoe
{
	public:	
	char square[10] = {'o','1','2','3','4','5','6','7','8','9'};
	char next_square[10];
	int checkwin();
	void board();
	bool mark_square(int, int, char &, char);
	void resetboard();
	int checkwin(string);
};

bool tictactoe::mark_square(int num, int choice, char & a, char mark)
{
	if (choice == num && ((int)a-48) == num)
	{
		a = mark;
		return true;
	}	
	else
	{
		cout<<"Invalid move ";
		cin.ignore();
		cin.get();
		return false;
	}	
} 

int tictactoe::checkwin()
{
	if (this->square[1] == this->square[2] && this->square[2] == this->square[3])
		return 1;

	else if (this->square[4] == this->square[5] && this->square[5] == this->square[6])
		return 1;

	else if (this->square[7] == this->square[8] && this->square[8] == this->square[9])
		return 1;

	else if (this->square[1] == this->square[4] && this->square[4] == this->square[7])
		return 1;

	else if (this->square[2] == this->square[5] && this->square[5] == this->square[8])
		return 1;

	else if (this->square[3] == this->square[6] && this->square[6] == this->square[9])
		return 1;

	else if (this->square[1] == this->square[5] && this->square[5] == this->square[9])
		return 1;
	
	else if (this->square[3] == this->square[5] && this->square[5] == this->square[7])
		return 1;

	else if (this->square[1] != '1' && this->square[2] != '2' && this->square[3] != '3' 
                    && this->square[4] != '4' && this->square[5] != '5' && this->square[6] != '6' 
                  && this->square[7] != '7' && this->square[8] != '8' && this->square[9] != '9')
		return 0;

	else
		return -1;
}

void tictactoe::board()
{
	system("clear");
	cout << "\n\n\tTic Tac Toe\n\n";

	cout << "Player 1 (X)  -  Player 2 (O)" << endl << endl;
	cout << endl;

	cout << "     |     |     " << endl;
	cout << "  " << this->square[1] << "  |  " << this->square[2] << "  |  " << this->square[3] << endl;

	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;

	cout << "  " << this->square[4] << "  |  " << this->square[5] << "  |  " << this->square[6] << endl;

	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;

	cout << "  " << this->square[7] << "  |  " << this->square[8] << "  |  " << this->square[9] << endl;

	cout << "     |     |     " << endl << endl;
}


void tictactoe::resetboard()
{
	this->square[0] ='o';
	this->square[1] ='1';
	this->square[2] ='2';
	this->square[3] ='3';
	this->square[4] ='4';
	this->square[5] ='5';
	this->square[6] ='6';
	this->square[7] ='7';
	this->square[8] ='8';
	this->square[9] ='9';
}


int tictactoe::checkwin(string next_state)
{
	
	for(unsigned int i=1;i<next_state.length();i++)
	{	
		next_square[i] = next_state[i]; 
	}
	
	if (this->next_square[1] == this->next_square[2] && this->next_square[2] == this->next_square[3])
		return 1;

	else if (this->next_square[4] == this->next_square[5] && this->next_square[5] == this->next_square[6])
		return 1;

	else if (this->next_square[7] == this->next_square[8] && this->next_square[8] == this->next_square[9])
		return 1;

	else if (this->next_square[1] == this->next_square[4] && this->next_square[4] == this->next_square[7])
		return 1;

	else if (this->next_square[2] == this->next_square[5] && this->next_square[5] == this->next_square[8])
		return 1;

	else if (this->next_square[3] == this->next_square[6] && this->next_square[6] == this->next_square[9])
		return 1;

	else if (this->next_square[1] == this->next_square[5] && this->next_square[5] == this->next_square[9])
		return 1;
	
	else if (this->next_square[3] == this->next_square[5] && this->next_square[5] == this->next_square[7])
		return 1;

	else if (this->next_square[1] != '1' && this->next_square[2] != '2' && this->next_square[3] != '3' 
                    && this->next_square[4] != '4' && this->next_square[5] != '5' && this->next_square[6] != '6' 
                  && this->next_square[7] != '7' && this->next_square[8] != '8' && this->next_square[9] != '9')
		return 0;

	else
		return -1;
}
