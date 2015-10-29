#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "user.h"
#include "factory.h"
#include "matrix.h"
#include "enum.h"

int main(int argc, char **argv)
{ 	
	if(4 > argc)
	{
		std::cerr << "Wrong input. Please enter 4 arguments or more.\n";
		return 1;
	}
	else
	{
		std::vector<string> args;
		for (int i = 1; i < argc; ++i)
		{
			args.push_back(std::string(argv[i]));
		}
		std::vector<string> strategy_name;

		
		for(auto it = args.begin(); ( it != args.end() && it->find(std::string("--")) == string::npos); ++it)
		{
			if(Factory<string, Strategy>::instance()->is_registered(*it))
			{
				strategy_name.push_back(*it);
			}
			else
			{
				std::cerr << "Wrong input. Please write correct names of strategies.\n";
				return 1;
			}
		}

		if( 3 > strategy_name.size())
		{
			cerr << "Wrong input. Please write correct count of strategies\n";
			return 1;
		}
		
		Mode mode;
		auto it = args.begin() + strategy_name.size();
		if(it != args.end() && it->find("--mode") != string::npos)
		{
			if(*it == "--mode=detailed")
			{
				mode = Mode::Detailed;
			}
			else if(*it == "--mode=fast")
			{
				mode = Mode::Fast;
			}
			else if(*it == "--mode=tournament")
			{
				mode = Mode::Tournament;
			}	
			else
			{
				std::cerr << "Wrong input. Please write correct name of mode or don't do it.\n";
				return 1;	
			}
			++it;
		}
		else if(3 < strategy_name.size())
		{
			mode = Mode::Tournament; //by default if count of strategies is more than 3
		}
		else
		{
			mode = Mode::Detailed; //by default if count of strategies equals 3
		}

		int steps;
		try
		{
			if(it != args.end() && it->find("--steps=") !=  string::npos)
			{
				if(mode == Mode::Detailed)
				{
					cerr << "Wrong input. Detailed mode doesn't need arg of steps.\n";
					return 1;
				}
				it->erase (0,8);
				steps = std::stoi(*it);
				if( 0 >= steps)
				{
					cerr << "Wrong input. Count of steps must be a positive natural number.\n";
					return 1;
				}

				++it;
			}
			else
			{
				steps = 1; //by default
			}
		}
		catch(std::invalid_argument)
		{
			cerr << "Wrong input. Count of steps must be a positive natural number.\n";
			return 1;
		}

		matrix scores; 
		std::ifstream file_of_matrix;
		if(it != args.end() && it->find("--matrix=") !=  string::npos)
		{
			if(mode == Mode::Tournament)
			{
				std::cerr << "Wrong input. Tournament doesn't need arg of file of matrix.\n";
				return 1;
			}

			it->erase(0,9);
			file_of_matrix.open("in");
			if(!file_of_matrix)
			{
				std::cerr << "Can't open file of matrix.\n";
				return 1;
			}
			scores.extract_matrix(file_of_matrix);
			++it;
		}

		if(it != args.end())
		{
			std::cerr << "Wrong input. You had wrote unneccessary args.\n";
			return 1;
		}

		user info;

		info.user_interface(strategy_name, mode, steps, scores);

		return 0;
	}
}
