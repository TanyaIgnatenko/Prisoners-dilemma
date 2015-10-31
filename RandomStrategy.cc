#include <random>  
#include <string>

#include "enum.h"
#include "factory.h"
#include "strategy.h"

class RandomStrategy final: public Strategy
{
public:
	RandomStrategy(){}
	~RandomStrategy() override {}

	RandomStrategy(const RandomStrategy & other) = delete;
	RandomStrategy & operator=(const RandomStrategy & other) = delete;
	
	choice decide() override {std::random_device rand; int x = rand() % 2; return x ? choice::Betray : choice::RemainSilent;}
};

namespace
{
	bool b = Factory<std::string, Strategy>::instance()->doregister<RandomStrategy>("RandomStrategy");
}