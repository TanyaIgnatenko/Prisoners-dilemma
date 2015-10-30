#include <string>

#include "enum.h"
#include "factory.h"
#include "game.h"
#include "matrix.h"
#include "strategy.h"

void erase_digits(std::string & name)
{
	unsigned int found = name.find_last_of("_");
	if(found!=std::string::npos)
	{
		name.erase(name.begin() + found, name.end());
	}
}

Game::Game(std::string n1, std::string n2, std::string n3, matrix & sc) : scores(n1, n2, n3)
{
	if(!sc.is_empty())
	{
		scores = sc;
	}	
	erase_digits(n1);
	erase_digits(n2);
	erase_digits(n3);
	prisoner1 = Factory<Strategy, std::string, Strategy>::instance()->create(n1);
	prisoner2 = Factory<Strategy, std::string, Strategy>::instance()->create(n2);
	prisoner3 = Factory<Strategy, std::string, Strategy>::instance()->create(n3);
}

void Game::tick()
{
		choice choices[3];
		choices[0] = prisoner1->decide();
		choices[1] = prisoner2->decide();
		choices[2] = prisoner3->decide();

		prisoner1->enemy_choices(choices[1], choices[2]);
		prisoner2->enemy_choices(choices[0], choices[2]);
		prisoner3->enemy_choices(choices[0], choices[1]);

		if(choices[0] == choice::Betray &&  choices[1] == choice::Betray &&  choices[2] == choice::Betray)
		{
			scores.add_scores(1, 1, 1);
		}
		else if(choices[0] == choice::Betray &&  choices[1] == choice::Betray &&  choices[2] == choice::RemainSilent)
		{
			scores.add_scores(3, 3, 0);
		}
		else if(choices[0] == choice::Betray &&  choices[1] == choice::RemainSilent &&  choices[2] == choice::Betray)
		{
			scores.add_scores(3, 0, 3);
		}
		else if(choices[0] == choice::RemainSilent &&  choices[1] == choice::Betray &&  choices[2] == choice::Betray)
		{
			scores.add_scores(0, 3, 3);
		}
		else if(choices[0] == choice::Betray &&  choices[1] == choice::RemainSilent &&  choices[2] == choice::RemainSilent)
		{
			scores.add_scores(5, 2, 2);
		}
		else if(choices[0] == choice::RemainSilent &&  choices[1] == choice::Betray &&  choices[2] == choice::RemainSilent)
		{
			scores.add_scores(2, 5, 2);
		}
		else if(choices[0] == choice::RemainSilent &&  choices[1] == choice::RemainSilent &&  choices[2] == choice::Betray)
		{
			scores.add_scores(2, 2, 5);
		}
		else if(choices[0] == choice::RemainSilent &&  choices[1] == choice::RemainSilent &&  choices[2] == choice::RemainSilent)
		{
			scores.add_scores(4, 4, 4);
		}
}