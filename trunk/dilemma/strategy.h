#ifndef STRATEGY_H
#define STRATEGY_H
#include <vector>
#include <string>
#include "enum.h"
using namespace std;

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
	virtual choice decide() const = 0;
	virtual void enemy_choices(choice , choice){}
	
protected:
	History *history = nullptr;
};


#endif
