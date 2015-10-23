#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <map>
#include "enum.h"
#include "matrix.h"

using namespace std;
using namespace for_matrix;

class user
{
public:
	void user_interface(vector<string> & name_of_strategy, int count_of_strategies, Mode & mode, int & steps, matrix & scores);
	void print_results_of_tour(std::map<string, int> & sum_of_scores, std::vector<string> & name_of_strategy, int & count_of_strategies) const;
};
#endif
