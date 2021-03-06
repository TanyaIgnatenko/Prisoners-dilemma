#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "matrix.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

void matrix::add_scores(int sc1, int sc2, int sc3)
{
	scores1.push_back(sc1);
	scores2.push_back(sc2);
	scores3.push_back(sc3);
}

int matrix::get_game_scores(int number_of_prisoner) const
{
	int sum = 0;
	switch(number_of_prisoner)
	{
		case 1:
		{
			for (auto val: scores1)
			{
				sum+= val;
			}
			break;	
		}

		case 2:
		{
			for (auto val: scores2)
			{
				sum+= val;
			}
			break;	
		}

		case 3:
		{
			for (auto val: scores3)
			{
				sum+= val;
			}
			break;	
		}
	}
	return sum;
}

void matrix::print_move_scores() const
{
	cout << "Scores of move:" << endl;
	int move = scores1.size() - 1;
	cout << strategy_name1 << ": " << +scores1[move]<< endl;// unary + promotes to a type printable as a number, regardless of type
	cout << strategy_name2 << ": " << +scores2[move]<< endl;// unary + promotes to a type printable as a number, regardless of type
	cout << strategy_name3 << ": " << +scores3[move]<< endl;// unary + promotes to a type printable as a number, regardless of type
	cout << "" << endl;
}

void matrix::print_game_scores() const
{
	int sum1 = 0 , sum2 = 0, sum3 = 0;
	sum1 = get_game_scores(1);
	sum2 = get_game_scores(2);
	sum3 = get_game_scores(3);

	cout << "Scores of game:" << endl;
	cout << strategy_name1 << ": " << sum1 << endl;
	cout << strategy_name2 << ": " << sum2 << endl;
	cout << strategy_name3 << ": " << sum3 << '\n' << endl;
}

matrix & matrix::operator=(const matrix & other)
{
	if(this != &other)
	{
		strategy_name1 = other.strategy_name1;
		strategy_name2 = other.strategy_name2;
		strategy_name3 = other.strategy_name3;
		scores1 = other.scores1;
		scores2 = other.scores2;
		scores3 = other.scores3;
		empty = other.empty;
	}
	return *this;
}