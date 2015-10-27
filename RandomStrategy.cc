#include <string>
#include <random>  

#include "strategy.h"
#include "factory.h"
#include "enum.h"

class RandomStrategy : public Strategy
{
public:
	RandomStrategy(){}
	~RandomStrategy(){}
	RandomStrategy(const RandomStrategy & other){}
	choice decide() const {std::random_device rand; int x = rand() % 2; return x ? choice::Betray : choice::RemainSilent;}
};

namespace
{
	bool b = Factory<std::string, Strategy>::instance()->doregister<RandomStrategy>("RandomStrategy");
}