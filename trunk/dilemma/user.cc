#include <algorithm>
#include <iostream>
#include <string>
#include <map>

#include "user.h"
using namespace std;


bool compare(const pair<string, int> & a, const pair<string, int> & b)
{
	return a.second < b.second; 
}

void user::print_results_of_tour(std::map<string, int> & sum_of_scores, std::vector<string> & name_of_strategy, int & count_of_strategies) const
{
	std::vector<std::pair<string, int> > scores(count_of_strategies);
	std::map<string, int>::iterator ptr = sum_of_scores.begin();
	for (int i = 0; i < count_of_strategies; ++i, ++ptr)
	{
		scores[i] = *ptr;
	}

	std::sort(scores.begin(), scores.end(), compare);
	for (int i = 0; i < count_of_strategies; ++i)
	{
		cout << scores[i].first << " " << scores[i].second << "\n";
	}

	cout << "The Winer: " <<  scores[count_of_strategies - 1].first << " " << scores[count_of_strategies - 1].second << "\n";

}



/*void user::print_results(const std::map<const string, int> * scores) const
{
	for (int i = 0, iterator ptr = scores->begin; i < 3; ++i, ++ptr)
	{
		cout << ptr->first << " " << ptr->second << "\n";
	}
}

int user::get_scores(const std::map<const string, int> * scores, name_of_strategy[i]) const
{
	iterator ptr = map->find(name_of_strategy);
	return ptr->second;
}*/
