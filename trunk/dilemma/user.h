#ifndef USER_H
#define USER_H

#include <utility>
#include <string>
#include <vector>
#include <map>

#include "matrix.h"
#include "enum.h"

class user
{
public:
	void user_interface(vector<std::string> & strategy_name, Mode mode, int steps, matrix & scores);
	void print_results_of_tour(std::map<std::string, int> & sum_of_scores) const;
private:
	static bool pair_second_compare(const std::pair<std::string, int> & a, const std::pair<std::string, int> & b);
};
#endif
