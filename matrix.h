#ifndef MATRIX_H
#define MATRIX_H

#include <fstream>
#include <string>
#include <vector>

using namespace std;
using std::string;
using std::vector;

struct matrix
{
public:
	matrix(){}
	matrix(string & n1, string & n2, string & n3) : strategy_name1(n1), strategy_name2(n2), strategy_name3(n3), empty(0){}

	void add_scores(int sc1, int sc2, int sc3);
	int get_game_scores(int number_of_prisoner) const;
	void print_move_scores() const;
	void print_game_scores() const;
	bool is_empty() const { return empty;}

	void clear_up(){ empty = 1;}

	matrix & operator=(const matrix & other);
	~matrix(){}
private:
	string strategy_name1;
	string strategy_name2;
	string strategy_name3;

	vector<int> scores1;
	vector<int> scores2;
	vector<int> scores3;

	bool empty = true;
};

#endif
