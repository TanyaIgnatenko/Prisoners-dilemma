#include <string>

#include "enum.h"
#include "factory.h"
#include "strategy.h"

class KindStrategy final: public Strategy::Strategy
{
public:
	KindStrategy(){}
	~KindStrategy() override {} 

	KindStrategy(const KindStrategy & other) = delete;
	KindStrategy & operator=(const KindStrategy & other) = delete;
	
	choice decide() const override {return choice::RemainSilent;}
};

namespace
{
	bool b = Factory<Strategy, std::string, Strategy>::instance()->doregister<KindStrategy>("KindStrategy");
}
