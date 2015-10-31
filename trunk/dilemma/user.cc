#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>

#include "user.h"

using std::string;
using std::map;

bool User::pair_second_compare(const pair<string, int> & a, const pair<string, int> & b)
{
	return a.second < b.second; 
}

void User::print_results_of_tour(map<string, int> & sum_of_scores) const
{
	cout << "Scores of tour:" << endl;
	std::vector<std::pair<string, int> > scores;
	for (auto val : sum_of_scores)
	{
		scores.push_back(val);
	}
	std::sort(scores.begin(), scores.end(), pair_second_compare);
	for (auto val : scores)
	{
		cout << val.first << " " << val.second << "\n";
	}

	int idx = scores.size() - 1;
	cout <<"\n" << "The Winer/s: " << endl;
	cout << scores[idx].first << " " << scores[idx].second << "\n"; 
	for (int i = scores.size() - 2; scores[i].second == scores[i+1].second; --i) //when some strategies has equal amount of scores
	{
		cout << scores[i].first << " " << scores[i].second << "\n"; 
	}
	cout << endl;
}
