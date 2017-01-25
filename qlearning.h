#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <algorithm>
#include "class_tictactoe.h"

using namespace std;

//extern map<string, double> Q;
//extern multimap  <string, double> Q;
//extern typedef std::vector< std::vector<double> > Qmatrix;

typedef map<int, double> action_value;
typedef map<string, action_value> table_states;
extern table_states Q;
extern tictactoe Tictactoe; 

class QLearning{
public:
	
	string start_state = "123456789";
	int max_games;
	int games;
	float learning_rate;
	float discount;
	string current_state;
	string next_state;
	string state_key;	
	string next_key;
	int player;
	int action;
	int opponent;
	double reward;
	float epsilon;

	string make_key(string, int); //state player
	void add_key(string key);
	int choose_action(string, float);//state
	string execute(string, int);//state, action
	void reinforcement(string); //Rewards and penalties
	void updateQ(string, int, string);
	int opponent_player();
	void switch_player();
	bool checkintable(string);

private:
	double lowestQ(string);
	double highestQ(string);
	vector<int> allowedactions(string);
};

string QLearning::make_key(string state, int player)
{	
	string key;

	if (player == 1)
		key = state + "X";
		//key = state + "_" + boost::lexical_cast<std::string>(player);//if player is a string
	else
		key = state + "O";
	
	//cout<<"Current_statekey: "<<key<<endl;
	return key;
}

void QLearning::add_key(string key)
{
   Q.insert (make_pair(key, action_value())); //Initialize States,actions
	//cout<<"Add key"<<endl;	
	vector<int> myactions  = allowedactions(key);

	vector<int>::iterator it;
	for (it=myactions.begin(); it<myactions.end(); it++)
	{ 	
		Q[key].insert (make_pair(*it, 1)); //Initialize each Action (= i) with +1
	}
}

int QLearning::choose_action(string state_key, float epsilon)
{
	float p;	
	int a;
	vector<int> myactions = allowedactions(state_key);
	int size = myactions.size();
	int array[size];
	double Qmax;
	int iter=0;
	int i; 

	map<string, action_value>::iterator it_out; //pointer for the outermost
	map<int, double>::iterator it_in; //innermost map
	
	//cout<<"Available actions: ";
	vector<int>::iterator it;
	for (it=myactions.begin(); it<myactions.end(); it++)
	{
		array[iter] = *it;
		//cout <<' '<< array[iter];
		iter++;
	}
	//cout<<endl;

	p = (rand() % 10000) / 10000.0;
	//cout<<"Random number: "<<p<<endl;
	if (p <= epsilon) //Explore
	{
		i = rand() % size;
		//cout<<i<<endl;
		a = array[i];
		
	}
	else //Choose policy
	{
		Qmax = highestQ(state_key);
		//cout<<Qmax<<endl;
		for(it_out = Q.begin(); it_out !=Q.end(); it_out++)
			if((*it_out).first == state_key)
				for(it_in=(*it_out).second.begin(); it_in !=(*it_out).second.end(); it_in++)
					if((*it_in).second == Qmax)
						a = (*it_in).first;
	}
	//cout<<"Chosen action: "<<a<<endl;
	return a;
}

string QLearning::execute(string current_state, int action)
{
	string next_state;
	char mark=(this->player == 1) ? 'X' : 'O';
	bool ret = Tictactoe.mark_square(action, action, Tictactoe.square[action], mark);
	if (ret)
		current_state.at(action-1) = mark;
	next_state = current_state;
	//cout<<"Execute."<<endl;
	return next_state;
}

void QLearning::reinforcement(string next_state)
{
	if(Tictactoe.checkwin(next_state))
		if(this->player == 1)
			this->reward = 10;
		else
			this->reward = 10;
	else
		this->reward = 0;
}

void QLearning::updateQ(string state_key, int action, string next_key)
{
	double expected;
	double change;	
	if (Tictactoe.checkwin(next_key.substr(0,8)))
	{
		expected = this->reward;
		cout<<this->reward<<endl;
	}	
	else
		if (this->player == 1)
			expected =  this->reward + this->discount*highestQ(next_key);
		else
			expected =  this->reward + this->discount*highestQ(next_key);
	change = this->learning_rate*(expected - Q[state_key][action]);
	Q[state_key][action] += change;
	cout<<"Q["<<state_key<<"]["<<action<<"]"<<Q[state_key][action]<<endl;
}

double QLearning::lowestQ(string state_key)
{
	double min;
	vector <int> myactions = allowedactions(state_key);
	int size = myactions.size();
	double array[size];
	map<string, action_value>::iterator it_out; //pointer for the outermost
	map<int, double>::iterator it_in; //innermost map
	
	int iter=0;
	cout<<"Qvalues for "<< state_key<<' '; 
	for(it_out = Q.begin(); it_out !=Q.end(); it_out++)
		if((*it_out).first == state_key)
			for(it_in=(*it_out).second.begin(); it_in !=(*it_out).second.end(); it_in++)
			{
				array[iter] = (*it_in).second;
				cout<<array[iter]<<" ";
				iter++;
			}
			cout<<endl;

	min = array[0] ;
	for ( unsigned int i=1;  i < sizeof(array)/sizeof(array[0]);  ++i )
   	if ( array[i] < min )
      	min = array[i];
	return min;
}

double QLearning::highestQ(string key)
{
	double max;
	vector <int> myactions = allowedactions(key);
	int size = myactions.size();
	double array[size];

	map<string, action_value>::iterator it_out; //pointer for the outermost
	map<int, double>::iterator it_in; //innermost map
	
	int iter=0;
	cout<<"Qvalues for "<< state_key<<' ';
	for(it_out = Q.begin(); it_out !=Q.end(); it_out++)
		if((*it_out).first == state_key)
			for(it_in=(*it_out).second.begin(); it_in !=(*it_out).second.end(); it_in++)
			{
				array[iter] = (*it_in).second;
				cout<<array[iter]<<" ";	
				iter++;
			}
	cout<<endl;
			
	max = array[0] ;
	for ( unsigned int i=1;  i < sizeof(array)/sizeof(array[0]);  ++i )
   	if ( array[i] > max )
      	max = array[i];
	return max;
}

int QLearning::opponent_player()
{
	if (this->player == 1)
		this->opponent = 2;
	else
		this->opponent = 1;
	//cout<<"Opponent: "<<this->opponent<<endl;
	return this->opponent;
}

void QLearning::switch_player()
{
	if (this->player == 1)
		this->player = 2;
	else
		this->player = 1;
	//cout<<"SwitchedPlayer: "<<this->player<<endl;
}


bool QLearning::checkintable(string state_key)
{
	map<string, action_value>::iterator it_out;
	
	for(it_out = Q.begin(); it_out !=Q.end(); it_out++)
		if((*it_out).first == state_key)
		{
			//cout<<"New key in table."<<endl;			
			return false;
		}
	//cout<<"New key not in table."<<endl;	
	return true;
}

vector<int> QLearning::allowedactions(string state_key)
{	
	vector<int> myvector;
	for(unsigned int k=0; k<state_key.length(); k++)
		if(state_key.at(k) != 'X' && state_key.at(k) != 'O')
			myvector.push_back (state_key.at(k)-48);
	//cout<<"Yep."<<endl;
	return myvector;
}

/*int* QLearning::allowedactions(string state_key)
{	
	//Return an array	
	int max = 1;           // no longer const
	int* a = new int[max];  // allocated on heap
	int n = 0;

	for(unsigned int k=0; k<state_key.length(); k++)
		if(state_key.at(k) != 'X' && state_key.at(k) != '0')
		{
			a[n] = state_key.at(k);   		
			n++;
    		if (n >= max)o
			{
        		max = max + 1;            // double the previous size
        		int* temp = new int[max]; // create new bigger array.
        		for (int i=0; i<n; i++) 
				{
            	temp[i] = a[i];       // copy values to new array.
      		}
				delete [] a;              // free old array memory.
      		a = temp;                 // now a points to new array.
			}
		}

	for (int i=0;i<n;i++)
		a[i] = a[i]-48;
}*/
/*
int QLearning::choose_action(string state_key, float epsilon)
{
	float p;	
	int a;
	vector<int> myactions = allowedactions(state_key);
	int size = myactions.size();
	int array[size];
	double Qmax;
	int iter=0;
	int i; 

	map<string, action_value>::iterator it_out; //pointer for the outermost
	map<int, double>::iterator it_in; //innermost map
	
	//cout<<"Available actions: ";
	vector<int>::iterator it;
	for (it=myactions.begin(); it<myactions.end(); it++)
	{
		array[iter] = *it;
		//cout <<' '<< array[iter];
		iter++;
	}
	//cout<<endl;

	p = (rand() % 10000) / 10000.0;
	//cout<<"Random number: "<<p<<endl;
	if (p <= epsilon) //Explore
	{
		i = rand() % size;
		//cout<<i<<endl;
		a = array[i];
		
	}
	else //Choose policy
	{
		Qmax = highestQ(state_key);
		//cout<<Qmax<<endl;
		for(it_out = Q.begin(); it_out !=Q.end(); it_out++)
			if((*it_out).first == state_key)
				for(it_in=(*it_out).second.begin(); it_in !=(*it_out).second.end(); it_in++)
					if((*it_in).second == Qmax)
						a = (*it_in).first;
	}
	//cout<<"Chosen action: "<<a<<endl;
	return a;
}*/
