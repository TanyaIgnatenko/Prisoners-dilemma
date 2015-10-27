#include <string>

#include "strategy.h"
#include "factory.h"
#include "enum.h"

class TitForTatStrategy : public Strategy
{
public:
	TitForTatStrategy(){history = new History;}
	TitForTatStrategy(const TitForTatStrategy & other){}
	~TitForTatStrategy(){}

	void enemy_choices(choice a, choice b){ history->enemy_choices2.push_back(a); history->enemy_choices3.push_back(b);}
	choice decide() const;
};

choice TitForTatStrategy::decide() const
{
	int idx = history->enemy_choices2.size() - 1;
	if(idx < 0)
	{
		return choice::RemainSilent;
	}
	if(choice::Betray == history->enemy_choices2[idx] || choice::Betray == history->enemy_choices3[idx])
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
namespace
{
	bool b = Factory<std::string, Strategy>::instance()->doregister<TitForTatStrategy>("TitForTatStrategy");
}
