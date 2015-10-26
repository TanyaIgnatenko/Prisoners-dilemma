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
	void user_interface(vector<string> & name_of_strategy, Mode & mode, int & steps, matrix & scores);
	void print_results_of_tour(std::map<string, int> & sum_of_scores) const;
private:
	static bool compare(const pair<string, int> & a, const pair<string, int> & b);
};
#endif
