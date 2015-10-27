#include <string>

#include "strategy.h"
#include "factory.h"
#include "enum.h"

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
