#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#include "enum.h"
#include "factory.h"
#include "strategy.h"
#include "user.h"

class TitForTatForgiveStrategy final: public Strategy
{
public:
	TitForTatForgiveStrategy();
	~TitForTatForgiveStrategy() override {delete history;}

	TitForTatForgiveStrategy(const TitForTatForgiveStrategy & other) = delete;
	TitForTatForgiveStrategy & operator=(const TitForTatForgiveStrategy & other) = delete;

	choice decide() override;
	void enemy_choices(choice a, choice b){ history->enemy_choices2.push_back(a); history->enemy_choices3.push_back(b);}

private:
	int forgive_step = 5;

};

choice TitForTatForgiveStrategy::decide()
{
	int idx = history->enemy_choices2.size();
	if(idx == 0)
	{
		return choice::RemainSilent;
	}
	if((idx + 1) % forgive_step == 0)
	{
		return choice::RemainSilent;
	}
	if(choice::Betray == history->enemy_choices2[idx-1] || choice::Betray == history->enemy_choices3[idx-1])
	{
		history->my_choices.push_back(choice::Betray);
		return choice::Betray;
	}
	else
	{
		history->my_choices.push_back(choice::RemainSilent);
		return choice::RemainSilent;
	}
}

TitForTatForgiveStrategy::TitForTatForgiveStrategy()
{
	string strategy_dir = User::instance()->get_config_dir();
	history = new History;
	std::string step;
	ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	if(!strategy_dir.length())
	{
		std::cerr << "Wrong input. You forgot to write a dirname of configs for TitForTatForgiveStrategy.\n";
		forgive_step = 5; //by default
	}
	else
	{
		string command = "test -e " + strategy_dir + "/" + "TitForTatForgiveStrategy.txt";
		if(system(command.c_str()))
		{
			std::cerr << "Wrong input. Can't find a file of config for TitForTatForgiveStrategy.\n";
		}
		else
		{
			try
			{
				command.clear();
				command = "cd " + strategy_dir;
				system(command.c_str());
				file.open("TitForTatForgiveStrategy.txt");

				file >> step;
				forgive_step = std::stoi(step);
				if( 0 >= forgive_step)
				{
					std::cerr << "Wrong input in a config file for TitForTatForgiveStrategy, that's why we have to use a default forgive_step.\n";
					forgive_step = 5;
				}

			}
			catch(std::invalid_argument)
			{
				std::cerr << "Wrong input in a config file for TitForTatForgiveStrategy, that's why we have to use a default forgive_step.\n";
				forgive_step = 5;
			}
			catch(std::ios_base::failure)
			{
				std::cerr << "Error in file of config for TitForTatForgiveStrategy.\n";
				forgive_step = 5;
			}
		}
	}
}

namespace
{
	bool b = Factory<std::string, Strategy>::instance()->doregister<TitForTatForgiveStrategy>("TitForTatForgiveStrategy");
}
