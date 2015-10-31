#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "enum.h"
#include "game.h"
#include "matrix.h"
#include "user.h"

using std::map;
using std::pair;
using std::string;
using std::vector;

void User::user_interface(vector<string> & strategy_name, Mode mode, int steps, matrix & scores) const
{
	if(Mode::Detailed == mode)
	{
		Game game(strategy_name[0], strategy_name[1], strategy_name[2], scores);
		string command;

		std::cout << "==================================Game Starts!==================================" << std::endl;

		for(;;)
		{
			std::cout << "Please write a command:" << std::endl;
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

			else if(command == "dump")
			{
				game.dump_matrix();
			}

			else if(command == "quit")
			{
				std::cout << "==================================Game Over!====================================" << std::endl;
				return;
			}

			command.erase();
		}
	}
	else if(Mode::Fast == mode)
	{
		Game game(strategy_name[0], strategy_name[1], strategy_name[2], scores);
		std::cout << "==================================Game Starts!==================================" << std::endl;
		for (int i = 0; i < steps; ++i)
		{
			game.tick();
		}
		game.print_game_scores();
		std::cout << "==================================Game Over!====================================" << std::endl;
	}
	else if(Mode::Tournament == mode)
	{
		std::cout << "==============================Tournament Starts!================================" << std::endl;
		int k = 1;
		map<string, int> sum_of_scores;
		vector<string> idx_names;
		std::sort(strategy_name.begin(), strategy_name.end());

		for (size_t i = 0; i < strategy_name.size(); ++i) 
		{
			if(i != 0 && strategy_name[i] == strategy_name[i-1])
			{
				idx_names.push_back(strategy_name[i]+"_"+to_string(k));
				++k;
			}
			else
			{
				k = 1;
				idx_names.push_back(strategy_name[i]+"_0");
			}
			pair<const string, int> prisoner(idx_names.back(), 0);
			sum_of_scores.insert(prisoner).second;
		}
		for (size_t i = 0; i <  strategy_name.size(); ++i)
		{
			for (size_t j = i + 1; j < strategy_name.size(); ++j)
			{
				for (size_t k = j + 1; k < strategy_name.size(); ++k)
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
		std::cout << "==============================Tournament Over!=================================" << std::endl;
	}
}



