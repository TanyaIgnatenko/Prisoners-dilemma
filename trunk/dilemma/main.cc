#include <cstring>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "user.h"
#include "matrix.h"
#include "enum.h"
using namespace std;
using namespace for_matrix;

int main(int argc, char **argv)
{ 	
	if(4 > argc)
	{
		cerr << "Bad input. Please enter 4 arguments or more.\n";
		return 1;
	}
	else
	{
		std::vector<string> args;
		for (int i = 1; i < argc; ++i)
		{
			args.push_back(string(argv[i]));
		}
		std::vector<string> name_of_strategy;

		for(auto it = args.begin(); ( it != args.end() && it->find(string("--")) == string::npos); ++it)
		{
			name_of_strategy.push_back(*it);
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
				mode = Detailed; //by default
			}
			++idx;
		}
		else
		{
			mode = Detailed; //by default
		}

		if( 3 > name_of_strategy.size() || (Tournament != mode && 3 > name_of_strategy.size()))
		{
			cerr << "Bad input. For more information try \"help\".\n";
			return 1;
		}

		int steps;
		if(idx < args.size() && args[idx].find("--steps=") !=  string::npos)
		{
			if(mode == Detailed)
			{
				cerr << "Bad input. For more information try \"help\".\n";
				return 1;
			}
			args[idx].erase (0,8);
			steps = stoi(args[idx]);
			++idx;
		}
		else
		{
			steps = 1; //by default
		}
		
		matrix scores; 
		ifstream file_of_matrix;
		if(idx < args.size() && args[idx].find("--matrix=") !=  string::npos)
		{
			if(mode == Tournament)
			{
				cerr << "Bad input. For more information try \"help\".\n";
				return 1;
			}

			args[idx].erase (0,9);
			file_of_matrix.open(argv[idx]);

			if(!file_of_matrix)
			{
				cout << "Can't open file of matrix.\n";
				return 1;
			}
			scores = extract_matrix(file_of_matrix);
		}

		user info;

		info.user_interface(name_of_strategy, name_of_strategy.size(), mode, steps, scores);

		return 0;
	}
}
