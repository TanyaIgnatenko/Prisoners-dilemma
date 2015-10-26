#include <cstring>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

#include "user.h"
#include "factory.h"
#include "matrix.h"
#include "enum.h"

using namespace for_matrix;

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
		std::vector<string> name_of_strategy;

		
		for(auto it = args.begin(); ( it != args.end() && it->find(std::string("--")) == string::npos); ++it)
		{
			if(true == Factory<string, Strategy>::instance()->is_registered(*it))
			{
				name_of_strategy.push_back(*it);
			}
			else
			{
				std::cerr << "Wrong input. Please write correct names of strategies.\n";
				return 1;
			}
		}

		if( 3 > name_of_strategy.size())
		{
			cerr << "Wrong input. Please write correct count of strategies\n";
			return 1;
		}
		
		Mode mode;

		int idx = name_of_strategy.size();
		if(idx < args.size() && args[idx].find("--mode") !=  string::npos)
		{
			if(args[idx] == "--mode=detailed")
			{
				mode = Detailed;
			}
			else if(args[idx] == "--mode=fast")
			{
				mode = Fast;
			}
			else if(args[idx] == "--mode=tournament")
			{
				mode = Tournament;
			}	
			else
			{
				std::cerr << "Wrong input. Please write correct name of mode or don't do it.\n";
				return 1;	
			}
			++idx;
		}
		else if(3 < name_of_strategy.size())
		{
			mode = Tournament; //by default if count of strategies is more than 3
		}
		else
		{
			mode = Detailed; //by default if count of strategies equals 3
		}

		int steps;
		try
		{
			if(idx < args.size() && args[idx].find("--steps=") !=  string::npos)
			{
				if(mode == Detailed)
				{
					cerr << "Wrong input. Detailed mode doesn't need arg of steps.\n";
					return 1;
				}
				args[idx].erase (0,8);
				steps = std::stoi(args[idx]);
				if( 0 > steps)
				{
					cerr << "Wrong input. Count of steps must be a positive natural number.\n";
					return 1;
				}

				++idx;
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
		if(idx < args.size() && args[idx].find("--matrix=") !=  string::npos)
		{
			if(mode == Tournament)
			{
				std::cerr << "Wrong input. Tournament doesn't need arg of file of matrix.\n";
				return 1;
			}

			args[idx].erase (0,9);
			file_of_matrix.open("in");
			if(!file_of_matrix)
			{
				std::cerr << "Can't open file of matrix.\n";
				return 1;
			}
			scores = extract_matrix(file_of_matrix);
			idx++;
		}

		if(idx < argc)
		{
			std::cerr << "Wrong input. You had wrote unneccessary args.\n";
		}

		user info;

		info.user_interface(name_of_strategy, mode, steps, scores);

		return 0;
	}
}
