#include <string>

#include "enum.h"
#include "factory.h"
#include "strategy.h"

class MetaStrategy final: public Strategy
{
public:
	MetaStrategy()
	{	
		strategy1 = Factory<Strategy, std::string, Strategy>::instance()->create("RandomStrategy");
		strategy2 = Factory<Strategy, std::string, Strategy>::instance()->create("BadStrategy");
	}
	~MetaStrategy() override {}

	MetaStrategy(const MetaStrategy & other) = delete;
	MetaStrategy & operator=(const MetaStrategy & other) = delete;

	choice decide() const override;
private:
	Strategy *strategy1;
	Strategy *strategy2;
};

namespace
{
	bool b = Factory<Strategy, std::string, Strategy>::instance()->doregister<MetaStrategy>("MetaStrategy");
}

choice MetaStrategy::decide() const
 {
 	static size_t move = 0;
 	if(move % 2 == 0)
 	{
 		++move;
 		return strategy1->decide();
 	}
 	else
 	{
 		++move;
 		return strategy2->decide();
 	}
 }
