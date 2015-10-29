#include <string>

#include "enum.h"
#include "factory.h"
#include "strategy.h"

class KindStrategy : public Strategy::Strategy
{
public:
	KindStrategy(){}
	~KindStrategy(){}
	KindStrategy(const KindStrategy & other){}
	choice decide() const {return choice::RemainSilent;}
};

namespace
{
	bool b = Factory<std::string, Strategy>::instance()->doregister<KindStrategy>("KindStrategy");
}
