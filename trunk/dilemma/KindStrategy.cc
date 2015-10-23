#include <string>
#include "strategy.h"
#include "factory.h"
#include "enum.h"
using namespace std;

class KindStrategy : public Strategy::Strategy
{
public:
	KindStrategy(){}
	~KindStrategy(){}
	KindStrategy(const KindStrategy & other){}
	choice decide() const {return RemainSilent;}

	class Creator : public Strategy::Creator
	{
	public:
		Strategy * operator()() const
		{
			return new KindStrategy;
		}
	};
};

namespace
{
	bool b1 = Factory<string, Strategy, Strategy::Creator>::instance()->doregister("KindStrategy", new KindStrategy::Creator);
}
