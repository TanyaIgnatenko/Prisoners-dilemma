#ifndef BADSTRATEGY_H
#define BADSTRATEGY_H
#include <string>

#include "strategy.h"
#include "factory.h"
#include "enum.h"
using namespace std;


class BadStrategy : public Strategy
{
public:
	BadStrategy(): name(string("BadStrategy")){}
	~BadStrategy(){}
	BadStrategy(const BadStrategy & other){}
	choice decide() const {return RemainSilent;}
	const string & get_name() const {return name;}

	class Creator : public Strategy::Creator
	{
	public:
		Strategy * operator()() 
		{
			return new BadStrategy;
		}
	};

private:
	const string name;
};

namespace
{
	bool b2 = Factory<string, Strategy, Strategy::Creator>::instance()->doregister("BadStrategy", BadStrategy::Creator());
}
#endif