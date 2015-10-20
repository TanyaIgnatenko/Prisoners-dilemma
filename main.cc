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
		std::vector<string> name_of_strategy(argc + 1);
		int count_of_strategies = 0;
		for(int i = 0; !strstr(argv[i+1], "mode") ; ++i)
		{
			name_of_strategy[i] = string(argv[i]);
			count_of_strategies++;
		}

		Mode mode;
		if(argv[4])
		{
			if(!strcmp(argv[4], "mode=detailed"))
			{
				mode = Detailed;
			}
			if(!strcmp(argv[4], "mode=fast"))
			{
				mode = Fast;
			}
			if(!strcmp(argv[4], "mode=tournament"))
			{
				mode = Tournament;
			}
			else
			{
				cerr << "Bad input. For more information try \"help\".\n";
				return 1;
			}

		}
		else
		{
			mode = Detailed;
		}

		if( 3 < count_of_strategies || (mode != Tournament && 3 > count_of_strategies))
		{
			cerr << "Bad input. For more information try \"help\".\n";
			return 1;
		}

		int steps;
		if(argv[5])
		{
			steps = *argv[5];
		}
		else
		{
			steps = 1;
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

		info.user_interface(name_of_strategy, count_of_strategies, mode, steps);

		return 0;
	}
}
