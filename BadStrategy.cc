#include <string>
#include "strategy.h"
#include "factory.h"
#include "enum.h"
using namespace std;


class BadStrategy : public Strategy
{
public:
	BadStrategy(){}
	~BadStrategy(){}
	BadStrategy(const BadStrategy & other){}
	choice decide() const {return Betray;}
};

namespace
{
	bool b = Factory<string, Strategy>::instance()->doregister<BadStrategy>("BadStrategy");
}
