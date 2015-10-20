#include "game.h"
#include "matrix.h"
#include "factory.h"
#include "strategy.h"
#include "enum.h"
using namespace std;

Game::Game(string & n1, string & n2, string & n3) : scores(n1, n2, n3)
{
	prisoner1 = Factory<string, Strategy, Strategy::Creator>::instance()->create(n1);
	prisoner2 = Factory<string, Strategy, Strategy::Creator>::instance()->create(n2);
	prisoner3 = Factory<string, Strategy, Strategy::Creator>::instance()->create(n3);
}

void Game::tick(int steps)
{
	choice x1 = prisoner1->decide();
	choice x2 = prisoner2->decide();
	choice x3 = prisoner3->decide();

	if(Betray == x1 && Betray == x2 && Betray == x3)
	{
		scores.add_scores(1, 1, 1);
	}
	else if(Betray == x1 && Betray == x2 && RemainSilent == x3)
	{
		scores.add_scores(3, 3, 0);
	}
	else if(Betray  == x1 && Betray == x3 && RemainSilent == x2)
	{
		scores.add_scores(3, 0, 3);
	}
	else if(Betray  == x2 && Betray == x3 && RemainSilent == x1)
	{
		scores.add_scores(0, 3, 3);
	}
	else if(Betray  == x1 && RemainSilent == x2 && RemainSilent == x3)
	{
		scores.add_scores(5, 2, 2);
	}
	else if(Betray  == x2 && RemainSilent == x1 && RemainSilent == x3)
	{
		scores.add_scores(2, 5, 2);
	}
	else if(Betray  == x3 && RemainSilent == x1 && RemainSilent == x2)
	{
		scores.add_scores(2, 2, 5);
	}
	else if(RemainSilent == x1 && RemainSilent == x2 && RemainSilent == x3)
	{
		scores.add_scores(4, 4, 4);
	}
}