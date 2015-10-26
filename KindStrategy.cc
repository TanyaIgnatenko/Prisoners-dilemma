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
};

namespace
{
	bool b = Factory<string, Strategy>::instance()->doregister<KindStrategy>("KindStrategy");
}
