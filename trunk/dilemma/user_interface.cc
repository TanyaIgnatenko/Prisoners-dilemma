#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>

#include "user.h"
#include "enum.h"
#include "game.h"
#include "matrix.h"

using namespace std;
using namespace for_matrix;

void user::user_interface(vector<string> & name_of_strategy, int count_of_strategies, Mode & mode, int & steps, matrix & scores)
{
	if(Detailed == mode)
	{
		Game game(name_of_strategy[0], name_of_strategy[1], name_of_strategy[2], scores);
		string command;

		for(;;)
		{
			getline(cin, command);
			if(command == "tick")
			{
				game.tick();
				game.print_move_scores();
				game.print_game_scores();
			}

			else if(command.find("tick ") !=  string::npos)
			{
				command.erase (0,4);
				int n = stoi(command);
				for (int i = 0; i < n; ++i)
				{
					game.tick();
					game.print_move_scores();
					game.print_game_scores();
				}
			}

			else if(command == "quit")
			{
				exit(0);
			}

			command.erase();
		}
	}
	else if(Fast == mode)
	{
		cout << "Fast" <<endl;
		Game game(name_of_strategy[0], name_of_strategy[1], name_of_strategy[2], scores);
		for (int i = 0; i < steps; ++i)
		{
			game.tick();
		}
		game.print_game_scores();
	}
	else if(Tournament == mode)
	{
		std::map<string, int> sum_of_scores;
		for (int i = 0; i < count_of_strategies; ++i)
		{
			std::pair<const string, int> prisoner(name_of_strategy[i], 0);
			sum_of_scores.insert(prisoner);
		}
		for (int i = 0; i <  count_of_strategies; ++i)
		{
			for (int j = i + 1; j < count_of_strategies; ++j)
			{
				for (int k = j + 1; k < count_of_strategies; ++k)
				{

					Game game(name_of_strategy[i], name_of_strategy[j], name_of_strategy[k], scores);

					for (int i = 0; i < steps; ++i)
					{
						game.tick();
					}
					game.print_game_scores();

					sum_of_scores[name_of_strategy[i]] += game.get_game_scores(1);
					sum_of_scores[name_of_strategy[j]] += game.get_game_scores(2);
					sum_of_scores[name_of_strategy[k]] += game.get_game_scores(3);
					
					print_results_of_tour(sum_of_scores, name_of_strategy, count_of_strategies);
				}
			}
		}
	}
}


