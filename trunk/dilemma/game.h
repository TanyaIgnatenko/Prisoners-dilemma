#ifndef GAME_H
#define GAME_H

#include <string>

#include "strategy.h"
#include "matrix.h"

class Game
{
public:
	Game(std::string n1, std::string n2, std::string n3, matrix & sc);
	~Game() { delete prisoner1; delete prisoner2; delete prisoner3;}
	void tick();

	int get_game_scores(int prisoner_number) const {return scores.get_game_scores(prisoner_number);}
	void print_move_scores() const {scores.print_move_scores();}
	void print_game_scores() const {scores.print_game_scores();}

private:
	Game(const Game & other){}
	Game & operator = (const Game & other){}
	Strategy *prisoner1 = nullptr;
	Strategy *prisoner2 = nullptr;
	Strategy *prisoner3 = nullptr;
	struct matrix scores;
};
#endif