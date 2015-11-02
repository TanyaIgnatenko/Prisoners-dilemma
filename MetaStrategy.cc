#include <cstddef>
#include <string>

#include "enum.h"
#include "factory.h"
#include "strategy.h"

class MetaStrategy final: public Strategy
{
public:
	MetaStrategy()
	{	try
		{
			strategy1 = Factory<std::string, Strategy>::instance()->create("RandomStrategy");
			strategy2 = Factory<std::string, Strategy>::instance()->create("BadStrategy");
		}
		catch(...)
		{
			clean_up();
			throw;
		}
	}
	~MetaStrategy() override {clean_up();}

	MetaStrategy(const MetaStrategy & other) = delete;
	MetaStrategy & operator=(const MetaStrategy & other) = delete;

	choice decide() override;
	void clean_up() {delete strategy1; delete strategy2;}
private:
	size_t move = 0;
	Strategy *strategy1 = nullptr;
	Strategy *strategy2 = nullptr;
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

