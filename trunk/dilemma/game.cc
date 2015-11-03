#include <cstddef>
#include <exception>
#include <string>

#include "enum.h"
#include "factory.h"
#include "game.h"
#include "matrix.h"
#include "strategy.h"

using std::string;
using std::vector;

void erase_digits(string & name)
{
	size_t found = name.find_last_of("_");
	if(found!=string::npos)
	{
		name.erase(name.begin() + found, name.end());
	}
}

Game::Game(string n1, string n2, string n3, const vector<vector <int> > & rules) : scores(n1, n2, n3), rules_(rules)
{
	if(!rules_.size())
	{
		rules_.resize(3);
		for(auto & v : rules_)
		{
			v.resize(8);
		}
		rules_[0][0] = 4;
		rules_[0][1] = 2;
		rules_[0][2] = 2;
		rules_[0][3] = 5;
		rules_[0][4] = 0;
		rules_[0][5] = 3;
		rules_[0][6] = 3;
		rules_[0][7] = 1;

		rules_[1][0] = 4;
		rules_[1][1] = 2;
		rules_[1][2] = 5;
		rules_[1][3] = 2;
		rules_[1][4] = 3;
		rules_[1][5] = 0;
		rules_[1][6] = 3;
		rules_[1][7] = 1;

		rules_[2][0] = 4;
		rules_[2][1] = 5;
		rules_[2][2] = 2;
		rules_[2][3] = 2;
		rules_[2][4] = 3;
		rules_[2][5] = 3;	
		rules_[2][6] = 0;
		rules_[2][7] = 1;
	}

	erase_digits(n1);
	erase_digits(n2);
	erase_digits(n3);

	prisoner1 = std::unique_ptr<Strategy>(Factory<string, Strategy>::instance()->create(n1));
	prisoner2 = std::unique_ptr<Strategy>(Factory<string, Strategy>::instance()->create(n2));
	prisoner3 = std::unique_ptr<Strategy>(Factory<string, Strategy>::instance()->create(n3));
}

void Game::tick()
{
	vector<choice> choices(3);
	choices[0] = prisoner1->decide();
	choices[1] = prisoner2->decide();
	choices[2] = prisoner3->decide();

	prisoner1->enemy_choices(choices[1], choices[2]);
	prisoner2->enemy_choices(choices[0], choices[2]);
	prisoner3->enemy_choices(choices[0], choices[1]);

	if(choices[0] == choice::RemainSilent &&  choices[1] == choice::RemainSilent &&  choices[2] == choice::RemainSilent)
	{
		scores.add_scores(rules_[0][0], rules_[1][0], rules_[2][0]);
	}
	else if(choices[0] == choice::RemainSilent &&  choices[1] == choice::RemainSilent &&  choices[2] == choice::Betray)
	{
		scores.add_scores(rules_[0][1], rules_[1][1], rules_[2][1]);
	}
	else if(choices[0] == choice::RemainSilent &&  choices[1] == choice::Betray &&  choices[2] == choice::RemainSilent)
	{
		scores.add_scores(rules_[0][2], rules_[1][2], rules_[2][2]);
	}
	else if(choices[0] == choice::Betray &&  choices[1] == choice::RemainSilent &&  choices[2] == choice::RemainSilent)
	{
		scores.add_scores(rules_[0][3], rules_[1][3], rules_[2][3]);
	}
	else if(choices[0] == choice::RemainSilent &&  choices[1] == choice::Betray &&  choices[2] == choice::Betray)
	{
		scores.add_scores(rules_[0][4], rules_[1][4], rules_[2][4]);
	}
	else if(choices[0] == choice::Betray &&  choices[1] == choice::RemainSilent &&  choices[2] == choice::Betray)
	{
		scores.add_scores(rules_[0][5], rules_[1][5], rules_[2][5]);
	}
	else if(choices[0] == choice::Betray &&  choices[1] == choice::Betray &&  choices[2] == choice::RemainSilent)
	{
		scores.add_scores(rules_[0][6], rules_[1][6], rules_[2][6]);
	}
	else if(choices[0] == choice::Betray &&  choices[1] == choice::Betray &&  choices[2] == choice::Betray)
	{
		scores.add_scores(rules_[0][7], rules_[1][7], rules_[2][7]);
	}
}