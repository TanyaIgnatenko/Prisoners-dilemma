#ifndef KINDSTRATEGY_H
#define KINDSTRATEGY_H
#include <string>

#include "strategy.h"
#include "factory.h"
#include "enum.h"
using namespace std;

class KindStrategy : public Strategy::Strategy
{
public:
	KindStrategy(): name(string("KindStrategy")){}
	~KindStrategy(){}
	KindStrategy(const KindStrategy & other){}
	choice decide() const {return RemainSilent;}
	const string & get_name() const {return name;}

	class Creator : public Strategy::Creator
	{
	public:
		Strategy * operator()() 
		{
			return new KindStrategy;
		}
	};

private:
	const string name;
};

namespace
{
	bool b1 = Factory<string, Strategy, Strategy::Creator>::instance()->doregister("KindStrategy", KindStrategy::Creator());
}

#endif

