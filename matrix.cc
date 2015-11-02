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

void matrix::extract_matrix(std::ifstream & file)
{
	try
	{
		file >> strategy_name1;
		char score;
		file.get(score);
		int count = 0;

		while(score != '\n')// we skip spaces
		{
			file.get(score);
			scores1.push_back(atoi(&score));
			file.get(score);
			++count;
		}

		file >> strategy_name2;
		file.ignore();
		for (int i = 0; i < count; ++i) // we skip spaces
		{
			file.get(score);
			scores2.push_back(atoi(&score));
			file.ignore();
		}


		file >> strategy_name3;
		file.ignore();
		for (int i = 0; i < count; ++i) // we skip spaces
		{
			file.get(score);
			scores3.push_back(atoi(&score));
			file.ignore();
		}
		empty = 0;
	}
	catch(std::invalid_argument)
	{
		this->clear_up();
		std::cerr << "Invalid arguments in a matrix file!" << std::endl;
	}
}

void matrix::dump_matrix() const
{
	ofstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		file.open("matrix.txt");

		file << strategy_name1;
		for (char val: scores1)
		{
			file << " " << +val;
		}
		file << "\n";

		file << strategy_name2;
		for (auto val: scores2)
		{
			file << " " << +val;
		}
		file << "\n";

		file << strategy_name3;
		for (auto val: scores3)
		{
			file << " " << +val;
		}
	}
	catch(std::ios_base::failure)
	{
		std::cerr << "Can't dump matrix!" << std::endl;
	}	
}
