#ifndef STRATEGY_H
#define STRATEGY_H

#include <string>
#include "enum.h"
using namespace std;


class Strategy
{
public:
	Strategy(){}
	virtual ~Strategy(){}
	virtual choice decide() const  = 0;

	class Creator
	{
	public:
		virtual Strategy * operator()() {return nullptr;};	
	};
};


#endif
