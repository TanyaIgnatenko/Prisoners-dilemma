#ifndef RANDOMSTRATEGY_H
#define RANDOMSTRATEGY_H
#include <string>
#include <stdlib.h>
#include <time.h>  

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
	choice decide() const {srand (time(NULL)); int x = rand() % 2; return x ? Betray : RemainSilent;}

	class Creator : public Strategy::Creator
	{
	public:
		Strategy * operator()() const
		{
			return new RandomStrategy;
		}
	};
};

namespace
{
	bool b3 = Factory<string, Strategy, Strategy::Creator>::instance()->doregister("RandomStrategy", new RandomStrategy::Creator);
}
#endif