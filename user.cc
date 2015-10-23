#include <algorithm>
#include <iostream>
#include <string>
#include <map>

#include "user.h"
#include "matrix.h"
using namespace std;
using namespace for_matrix;


bool compare(const pair<string, int> & a, const pair<string, int> & b)
{
	return a.second < b.second; 
}

void user::print_results_of_tour(std::map<string, int> & sum_of_scores, std::vector<string> & name_of_strategy, int & count_of_strategies) const
{
	cout << "Scores of tour:" << endl;
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

	int idx = scores.size() - 1;
	cout <<"\n" << "The Winer/s: " << endl;
	cout << scores[idx].first << " " << scores[idx].second << "\n"; 
	for (int i = scores.size() - 2; scores[i].second == scores[i+1].second; --i) //when some strategies has equal amount of scores
	{
		 cout << scores[i].first << " " << scores[i].second << "\n"; 
	}
	cout << "" << endl;
}