#ifndef STRATEGY_H
#define STRATEGY_H

#include <vector>

#include "enum.h"

struct History
{
	std::vector<choice> my_choices;
	std::vector<choice> enemy_choices2;
	std::vector<choice> enemy_choices3;
};

class Strategy
{
public:
	Strategy(){}
	virtual ~Strategy(){}

	Strategy(const Strategy & other) = delete;
	Strategy & operator=(const Strategy & other) = delete;
	
	virtual choice decide() = 0;
	virtual void enemy_choices(choice , choice){}
	
protected:
	History *history = nullptr;
};


#endif
