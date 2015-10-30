#include <string>

#include "enum.h"
#include "factory.h"
#include "strategy.h"

class BadStrategy final: public Strategy
{
public:
	BadStrategy(){}
	~BadStrategy() override {}

	BadStrategy(const BadStrategy & other) = delete;
	BadStrategy & operator=(const BadStrategy & other) = delete;

	choice decide() const override {return choice::Betray;}
};

namespace
{
	bool b = Factory<Strategy, std::string, Strategy>::instance()->doregister<BadStrategy>("BadStrategy");
}
