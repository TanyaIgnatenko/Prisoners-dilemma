#ifndef RANDOMSTRATEGY_H
#define RANDOMSTRATEGY_H
#include <string>
#include <random>  

#include "strategy.h"
#include "factory.h"
#include "enum.h"
using namespace std;


class RandomStrategy : public Strategy
{
public:
	RandomStrategy(){}
	~RandomStrategy(){}
	RandomStrategy(const RandomStrategy & other){}
	choice decide() const {random_device rand; int x = rand() % 2; return x ? Betray : RemainSilent;}
};

namespace
{
	bool b = Factory<string, Strategy>::instance()->doregister<RandomStrategy>("RandomStrategy");
}
#endif