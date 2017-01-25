#include <iostream>
#include <stdlib.h>
#include <string>
#include "qlearning.h"
using namespace std;

table_states Q;
tictactoe Tictactoe;
QLearning QL;

int main()
{	
	QL.games = 0;
	QL.max_games = 10000;
	QL.current_state = QL.start_state;
	QL.discount = 0.7;
	QL.learning_rate=0.7;
	QL.epsilon = 1;
	int i;
	
	while(QL.games<QL.max_games)
	{
		
		if (QL.games == QL.max_games-1) //For the player
		{
			Tictactoe.board();
			QL.state_key = QL.make_key(QL.current_state,QL.player);
			if (QL.checkintable(QL.state_key))
				QL.add_key(QL.state_key);
			if (QL.player==2)
			{
				cout<<"Hello Human (player2), enter the number: ";
				cin>> QL.action;
			}
			else
				QL.action = QL.choose_action(QL.state_key, QL.epsilon);
		
			QL.next_state = QL.execute(QL.current_state, QL.action);
		
			QL.next_key = QL.make_key(QL.next_state, QL.opponent_player());
			if (QL.checkintable(QL.next_key))
				QL.add_key(QL.next_key);

			QL.reinforcement(QL.next_state);
			QL.updateQ(QL.state_key, QL.action, QL.next_key);
			i=Tictactoe.checkwin();
		}	
		else
		{
			QL.state_key = QL.make_key(QL.current_state,QL.player);
			if (QL.checkintable(QL.state_key))
				QL.add_key(QL.state_key);

			QL.action = QL.choose_action(QL.state_key, QL.epsilon);
		
			QL.next_state = QL.execute(QL.current_state, QL.action);
		
			QL.next_key = QL.make_key(QL.next_state, QL.opponent_player());
			if (QL.checkintable(QL.next_key))
				QL.add_key(QL.next_key);

			QL.reinforcement(QL.next_state);
			QL.updateQ(QL.state_key, QL.action, QL.next_key);
			i=Tictactoe.checkwin();
		}
		if (i!=-1) //win or draw
		{
			if (QL.games == QL.max_games -1)
				Tictactoe.board();
			QL.games += 1;
			if(i==1)
			{				
				cout<<"Player"<<QL.player<<" Wins!!"<<endl;
			}
			else
				cout<<"It's a Draw!!!"<<endl;
			cout<<"Game number: "<<	QL.games - 1 <<endl;
			Tictactoe.resetboard();
			QL.current_state = QL.start_state;	
			QL.player = 1;
			if (QL.epsilon > 0.05)  
 				QL.epsilon = QL.epsilon * 0.9999;
		}
		else
		{
			QL.current_state= QL.next_state;
			QL.switch_player();
			cout<<"******************************************"<<endl;
		}
	}
return 0;
}
