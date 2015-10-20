#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <map>
#include "enum.h"


using namespace std;


class user
{
public:
	void user_interface(vector<string> & name_of_strategy, int count_of_strategies, Mode & mode, int & steps);
	void print_results_of_tour(std::map<string, int> & sum_of_scores, std::vector<string> & name_of_strategy, int & count_of_strategies) const;
	// int get_scores(const std::map<const string, int> * scores, name_of_strategy[i]) const;
	// void print_results(const std::map<const string, int> * scores)const ;
};
#endif
