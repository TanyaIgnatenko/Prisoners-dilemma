#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "matrix.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

matrix::matrix(string & n1, string & n2, string & n3, vector<char> & sc1, vector<char>  & sc2, vector<char> & sc3)
: strategy_name1(n1), strategy_name2(n2), strategy_name3(n3), scores1(sc1), scores2(sc2), scores3(sc3), empty(0)
{}

void matrix::add_scores(char sc1, char sc2, char sc3)
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
	int move = scores1.size() - 1;
	cout << strategy_name1 << ": " << +scores1[move]<< endl;// unary + promotes to a type printable as a number, regardless of type
	cout << strategy_name2 << ": " << +scores2[move]<< endl;// unary + promotes to a type printable as a number, regardless of type
	cout << strategy_name3 << ": " << +scores3[move]<< endl;// unary + promotes to a type printable as a number, regardless of type
	cout << "" << endl;
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
	cout << strategy_name1 << ": " << sum1 << endl;
	cout << strategy_name2 << ": " << sum2 << endl;
	cout << strategy_name3 << ": " << sum3 << '\n' << endl;
}

matrix & matrix::operator=(const matrix & other)
{
	strategy_name1 = other.strategy_name1;
	strategy_name2 = other.strategy_name2;
	strategy_name3 = other.strategy_name3;
	scores1 = other.scores1;
	scores2 = other.scores2;
	scores3 = other.scores3;
	empty = other.empty;
}

void matrix::extract_matrix(std::ifstream & file)
{
	string name1;
	file >> name1;
	vector<char> scores1;
	char c;
	file.get(c);
	while(c != '\n')// we skip spaces
	{
		file.get(c);
		scores1.push_back(c);
		file.get(c);
	}

	string name2;
	file >> name2;
	vector<char> scores2;
	file.get(c);
	while(c != '\n')// we skip spaces
	{
		file.get(c);
		scores2.push_back(c);
		file.get(c);
	}

	string name3;
	file >> name3;
	vector<char> scores3;
	file.get(c);
	while(c != '\n')// we skip spaces
	{
		file.get(c);
		scores3.push_back(c);
		file.get(c);
	}

	matrix m1(name1, name2, name3, scores1, scores2, scores3);

	*this = m1;
}