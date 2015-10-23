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

	class Creator : public Strategy::Creator
	{
	public:
		Strategy * operator()() const
		{
			return new BadStrategy;
		}
	};
};

namespace
{
	bool b2 = Factory<string, Strategy, Strategy::Creator>::instance()->doregister("BadStrategy", new BadStrategy::Creator);
}
