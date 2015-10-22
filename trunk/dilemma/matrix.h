#ifndef MATRIX_H
#define MATRIX_H
#include <string>
#include <vector>
using namespace std;

struct matrix
{
public:
	matrix(string & n1, string & n2, string & n3) : name_of_strategy1(n1), name_of_strategy2(n2), name_of_strategy3(n3){}
	matrix(const matrix & other) : name_of_strategy1(other.name_of_strategy1), name_of_strategy2(other.name_of_strategy2)\
	, name_of_strategy3(other.name_of_strategy3), scores1(other.scores1), scores2(other.scores2), scores3(other.scores3){}
	void add_scores(int sc1, int sc2, int sc3);
	int get_game_scores(int number_of_prisoner) const;
	void print_move_scores() const;
	void print_game_scores() const;
	~matrix(){}
private:
	string name_of_strategy1;
	string name_of_strategy2;
	string name_of_strategy3;

	std::vector<int> scores1;
	std::vector<int> scores2;
	std::vector<int> scores3;
};
#endif
