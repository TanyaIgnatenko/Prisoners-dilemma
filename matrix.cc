#include <string>
#include <vector>
#include <iostream>
#include "matrix.h"
using namespace std;
using namespace for_matrix;

inline matrix::matrix(string n1, string n2, string n3, std::vector<char> sc1, std::vector<char> sc2, std::vector<char> sc3)
: name_of_strategy1(n1), name_of_strategy2(n2), name_of_strategy3(n3), scores1(sc1), scores2(sc2), scores3(sc3), empty(0)
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
	cout << name_of_strategy1 << ": " << +scores1[move]<< endl;// unary + promotes to a type printable as a number, regardless of type
	cout << name_of_strategy2 << ": " << +scores2[move]<< endl;// unary + promotes to a type printable as a number, regardless of type
	cout << name_of_strategy3 << ": " << +scores3[move]<< endl;// unary + promotes to a type printable as a number, regardless of type
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
	cout << name_of_strategy1 << ": " << sum1 << endl;
	cout << name_of_strategy2 << ": " << sum2 << endl;
	cout << name_of_strategy3 << ": " << sum3 << endl;
	cout << "" << endl;
}

matrix matrix::operator=(const matrix & other)
{
	name_of_strategy1 = other.name_of_strategy1;
	name_of_strategy2 = other.name_of_strategy2;
	name_of_strategy3 = other.name_of_strategy3;
	scores1 = other.scores1;
	scores2 = other.scores2;
	scores3 = other.scores3;
	empty = other.empty;
	cout << "8" << endl;
}

matrix for_matrix::extract_matrix(ifstream & file)
{
	string name1;
	cout << "entrance!" << endl;
	file >> name1;
	cout << "1" << endl;
	std::vector<char> scores1;
	char c;
	file.get(c);
	cout << "2" << endl;
	while(c != '\n')// we skip spaces
	{
		file.get(c);
		scores1.push_back(c);
		file.get(c);
		cout << "3" << endl;
	}

	string name2;
	file >> name2;
	cout << "4" << endl;
	std::vector<char> scores2;
	file.get(c);
	cout << "5" << endl;
	while(c != '\n')// we skip spaces
	{
		file.get(c);
		scores2.push_back(c);
		file.get(c);
		cout << "6" << endl;
	}

	string name3;
	file >> name3;
	std::vector<char> scores3;
	file.get(c);
	while(c != '\n')// we skip spaces
	{
		file.get(c);
		scores3.push_back(c);
		file.get(c);
		cout << "7" << endl;
	}

	matrix m1(name1, name2, name3, scores1, scores2, scores3);
	cout << "almost exit!" << endl;
		
	return m1;
}