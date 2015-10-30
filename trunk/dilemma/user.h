#ifndef USER_H
#define USER_H

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "enum.h"
#include "matrix.h"

class user
{
public:
	Result command_line_parser(int argc, const char **argv);
	void user_interface(vector<std::string> & strategy_name, Mode mode, int steps, matrix & scores);
	void print_results_of_tour(std::map<std::string, int> & sum_of_scores) const;
private:
	static bool pair_second_compare(const std::pair<std::string, int> & a, const std::pair<std::string, int> & b);
};
#endif
