#ifndef FACTORY_H
#define FACTORY_H
#include <map>
#include "strategy.h"

template <class ID, class PRODUCT, class CREATOR>
class Factory
{
public:
	PRODUCT * create(const ID & id)
	{
		auto creator = creators_.find(id);
		if(creators_.end() != creator)
		{
			return (creator->second)->operator()();
		}
		return nullptr;
	}	

	bool doregister(const ID & id, CREATOR * cr)
	{
		creators_[id] = cr;
		return true;
	}

	static Factory * instance()
	{
		static Factory f;
		return &f;
	}

private:
	Factory(){}
	~Factory(){}
	std::map<ID, CREATOR*> creators_;
};

#endif
