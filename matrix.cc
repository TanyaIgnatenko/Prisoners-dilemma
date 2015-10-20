#include <string>
#include <vector>
#include <iostream>
#include "matrix.h"
using namespace std;

void matrix::add_scores(char sc1, char sc2, char sc3)
{
	scores1.push_back(sc1);
	scores2.push_back(sc2);
	scores2.push_back(sc3);
}

int matrix::get_game_scores(int number_of_prisoner) const
{
	int sum = 0;
	switch(number_of_prisoner)
	{
		case 1:
		{
			for(int i = 0; i < scores1.size(); ++i)
			{
				sum += scores1[i];
			}
			break;	
		}

		case 2:
		{
			for(int i = 0; i < scores2.size(); ++i)
			{
				sum += scores2[i];
			}
			break;	
		}

		case 3:
		{
			for(int i = 0; i < scores3.size(); ++i)
			{
				sum += scores3[i];
			}
			break;	
		}
	}
	return sum;
}

void matrix::print_move_scores() const
{
	cout << "Scores of move:" << endl;
	cout << name_of_strategy1 << ": " << *scores1.end()<< endl;
	cout << name_of_strategy2 << ": " << *scores2.end()<< endl;
	cout << name_of_strategy3 << ": " << *scores3.end()<< endl;
}

void matrix::print_game_scores() const
{
	int sum1 = 0 , sum2 = 0, sum3 = 0;
	for(int i = 0; i < scores1.size(); ++i)
	{
		sum1 += scores1[i];
	}
	for(int i = 0; i < scores2.size(); ++i)
	{
		sum2 += scores2[i];
	}
	for(int i = 0; i < scores3.size(); ++i)
	{
		sum3 += scores3[i];
	}
	cout << "Scores of game:" << endl;
	cout << name_of_strategy1 << ": " << sum1 << endl;
	cout << name_of_strategy2 << ": " << sum2 << endl;
	cout << name_of_strategy3 << ": " << sum3 << endl;
}
