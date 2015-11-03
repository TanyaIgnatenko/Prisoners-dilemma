#include <cstddef>
#include <memory>
#include <string>

#include "enum.h"
#include "factory.h"
#include "strategy.h"

class MetaStrategy final: public Strategy
{
public:
	MetaStrategy()
	{	
		strategy1 = std::unique_ptr<Strategy>(Factory<std::string, Strategy>::instance()->create("RandomStrategy"));
		strategy2 = std::unique_ptr<Strategy>(Factory<std::string, Strategy>::instance()->create("BadStrategy"));
	}
	~MetaStrategy() override {}

	MetaStrategy(const MetaStrategy & other) = delete;
	MetaStrategy & operator=(const MetaStrategy & other) = delete;

	choice decide() override;
private:
	size_t move = 0;
	std::unique_ptr<Strategy> strategy1;
	std::unique_ptr<Strategy> strategy2;
};

choice MetaStrategy::decide()
{
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

namespace
{
	bool b = Factory<std::string, Strategy>::instance()->doregister<MetaStrategy>("MetaStrategy");
}

