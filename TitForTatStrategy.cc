#include <string>

#include "enum.h"
#include "factory.h"
#include "strategy.h"

class TitForTatStrategy final: public Strategy
{
public:
	TitForTatStrategy(){history = new History;}
	~TitForTatStrategy() override {delete history;}
	
	TitForTatStrategy(const TitForTatStrategy & other) = delete;
	TitForTatStrategy & operator=(const TitForTatStrategy & other) = delete;

	void enemy_choices(choice a, choice b){ history->enemy_choices2.push_back(a); history->enemy_choices3.push_back(b);}
	choice decide() override;
};

choice TitForTatStrategy::decide()
{
	int idx = history->enemy_choices2.size();
	if(idx == 0)
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
namespace
{
	bool b = Factory<std::string, Strategy>::instance()->doregister<TitForTatStrategy>("TitForTatStrategy");
}
