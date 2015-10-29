#include <string>

#include "enum.h"
#include "factory.h"
#include "strategy.h"

class BadStrategy : public Strategy
{
public:
	BadStrategy(){}
	~BadStrategy(){}
	BadStrategy(const BadStrategy & other ){}
	choice decide() const {return choice::Betray;}
};

namespace
{
	bool b = Factory<std::string, Strategy>::instance()->doregister<BadStrategy>("BadStrategy");
}
