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

	matrix(const matrix & other) : strategy_name1(other.strategy_name1), strategy_name2(other.strategy_name2)\
	, strategy_name3(other.strategy_name3), scores1(other.scores1), scores2(other.scores2), scores3(other.scores3), empty(other.empty){}
	void add_scores(char sc1, char sc2, char sc3);
	int get_game_scores(int number_of_prisoner) const;
	void extract_matrix(std::ifstream & file);
	void dump_matrix() const;
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

	vector<char> scores1;
	vector<char> scores2;
	vector<char> scores3;

	bool empty = true;
};

#endif
