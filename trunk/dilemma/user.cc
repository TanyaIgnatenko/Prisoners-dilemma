#include <algorithm>
#include <utility>
#include <iostream>
#include <string>
#include <map>

#include "user.h"
#include "matrix.h"

using std::string;
using std::map;

bool user::pair_second_compare(const pair<string, int> & a, const pair<string, int> & b)
{
	return a.second < b.second; 
}

void user::print_results_of_tour(map<string, int> & sum_of_scores) const
{
	cout << "Scores of tour:" << endl;
	std::vector<std::pair<string, int> > scores;
	for (auto ptr = sum_of_scores.begin(); ptr != sum_of_scores.end(); ptr++)
	{
		scores.push_back(*ptr);
	}
	std::sort(scores.begin(), scores.end(), pair_second_compare);
	for (int i = 0; i < scores.size(); ++i)
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
	cout << endl;
}