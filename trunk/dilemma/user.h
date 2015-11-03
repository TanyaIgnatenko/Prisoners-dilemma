#ifndef USER_H
#define USER_H

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "enum.h"
#include "matrix.h"

class User
{
public:
	User(const User & other) = delete;
	const User & operator=(const User & other)= delete;

	Result command_line_parser(int argc, const char **argv);
	Result user_interface(vector<std::string> & strategy_name, Mode mode, int steps, std::vector<std::vector <int> > & rules) const;
	void print_results_of_tour(std::map<std::string, int> & sum_of_scores) const;
	const string & get_config_dir() const {return strategy_dir;}
	std::vector<std::vector <int> > extract_rules(std::ifstream & file);

	static User * instance()
	{
		static User info;
		return &info; 
	}

private:
	User(){}
	~User(){}
	static bool pair_second_compare(const std::pair<std::string, int> & a, const std::pair<std::string, int> & b);
	string strategy_dir;
};
#endif
