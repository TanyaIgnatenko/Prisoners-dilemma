#ifndef GAME_H
#define GAME_H

#include <string>
#include "strategy.h"
#include "matrix.h"
using namespace std;


class Game
{
public:
	Game(string & n1, string & n2, string & n3);
	Game(const Game & other) : scores(other.scores), prisoner1(other.prisoner1), prisoner2(other.prisoner2), prisoner3(other.prisoner3){}
	~Game() { delete prisoner1; delete prisoner2; delete prisoner3;}
	void tick(int steps = 1);

	int get_game_scores(int number_of_prisoner) const {return scores.get_game_scores(number_of_prisoner);}
	void print_move_scores() const {scores.print_move_scores();}
	void print_game_scores() const {scores.print_game_scores();}

private:

	Strategy *prisoner1 = nullptr;
	Strategy *prisoner2 = nullptr;
	Strategy *prisoner3 = nullptr;
	struct matrix scores;
};
#endif