#include <cstring>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "user.h"
#include "enum.h"
using namespace std;

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
		// for(int i = 0; args[i].find("--") ==  string::npos && i < argc; ++i)
		// { 
		// 	name_of_strategy.push_back(args[i]);
		// }

		for(auto it = args.begin(); ( it != args.end() && it->find(string("--")) == string::npos); ++it)
		{
			name_of_strategy.push_back(*it);
		}

		
		Mode mode;
		int idx = name_of_strategy.size() + 1;
		if(idx < argc && args[idx].find("--mode") !=  string::npos)
		{
			if(argv[idx] == "mode=detailed")
			{
				mode = Detailed;
			}
			else if(argv[idx] == "mode=fast")
			{
				mode = Fast;
			}
			else if(argv[idx] == "mode=tournament")
			{
				mode = Tournament;
			}	
			else
			{
				mode = Detailed; //by default
			}
			idx++;
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
		if(idx < argc && args[idx].find("--steps") !=  string::npos)
		{
			args[idx].erase (0,9);
			args[idx].pop_back();
			steps = stoi(args[idx]);
		}
		else
		{
			steps = 1; //by default
		}
		
		/*ifstream file_of_matrix;
		if(argv[7])
		{
			file_of_matrix.open(argv[7]);
			if(!file_of_matrix)
			{
				cout « "Can't open file of matrix.\n"
				return 1;
			}
		}*/

			user info;

			info.user_interface(name_of_strategy, name_of_strategy.size(), mode, steps);

			return 0;
	}
}
