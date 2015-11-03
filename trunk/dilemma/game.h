#ifndef GAME_H
#define GAME_H

#include <string>

#include "matrix.h"
#include "strategy.h"

using std::string;
using std::vector;

class Game
{
public:
	Game(string n1, string n2, string n3, const vector<vector<int>> & rules);
	~Game() { clean_up();}

	Game(const Game & other) = delete;
	Game & operator = (const Game & other) = delete;

	void tick();
	void print_move_scores() const {scores.print_move_scores();}
	void print_game_scores() const {scores.print_game_scores();}
	void clean_up() {delete prisoner1; delete prisoner2; delete prisoner3;}
	int get_game_scores(int prisoner_number) const {return scores.get_game_scores(prisoner_number);}

private:
	Strategy *prisoner1 = nullptr;
	Strategy *prisoner2 = nullptr;
	Strategy *prisoner3 = nullptr;
	struct matrix scores;
	vector<vector <int> > rules_;
};
#endif