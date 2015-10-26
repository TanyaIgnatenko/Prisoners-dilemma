#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>

#include "user.h"
#include "enum.h"
#include "game.h"
#include "matrix.h"

using namespace for_matrix;
using std::string;
using std::vector;
using std::pair;
using std::map;

void user::user_interface(vector<string> & name_of_strategy, Mode & mode, int & steps, matrix & scores)
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
		Game game(name_of_strategy[0], name_of_strategy[1], name_of_strategy[2], scores);
		for (int i = 0; i < steps; ++i)
		{
			game.tick();
		}
		game.print_game_scores();
	}
	else if(Tournament == mode)
	{
		int k = 1;
		map<string, int> sum_of_scores;
		vector<string> idx_names;
		std::sort(name_of_strategy.begin(), name_of_strategy.end());

		for (int i = 0; i < name_of_strategy.size(); ++i)
		{
			if(i != 0 && name_of_strategy[i] == name_of_strategy[i-1])
			{
				idx_names.push_back(name_of_strategy[i]+"_"+to_string(k));
				++k;
			}
			else
			{
				k = 1;
				idx_names.push_back(name_of_strategy[i]+"_0");
			}
			pair<const string, int> prisoner(idx_names.back(), 0);
			sum_of_scores.insert(prisoner).second;
		}
		for (int i = 0; i <  name_of_strategy.size(); ++i)
		{
			for (int j = i + 1; j < name_of_strategy.size(); ++j)
			{
				for (int k = j + 1; k < name_of_strategy.size(); ++k)
				{

					Game game(idx_names[i], idx_names[j], idx_names[k], scores);

					for (int i = 0; i < steps; ++i)
					{
						game.tick();
					}
					game.print_game_scores();

					sum_of_scores[idx_names[i]] += game.get_game_scores(1);
					sum_of_scores[idx_names[j]] += game.get_game_scores(2);
					sum_of_scores[idx_names[k]] += game.get_game_scores(3);
				}
			}
		}

		print_results_of_tour(sum_of_scores);
	}
}



