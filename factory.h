#ifndef FACTORY_H
#define FACTORY_H
#include <map>
#include "strategy.h"

class abstractCreator
{
public:
	virtual Strategy * operator()() const = 0;
};

template <class C>
class Creator : public abstractCreator
{
public:
	Strategy * operator()() const { return new C(); }
};

template <class ID, class PRODUCT>
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
	
	template <class C>
	bool doregister(const ID & id)
	{
		auto it = creators_.find(id);
		if (creators_.end() == it)
		{
			creators_[id] = new Creator<C>();
		}
		return true;
	}

	bool is_registered(const ID & id)
	{
		return ((creators_.find(id) != creators_.end()) ? true : false);
	}

	static Factory * instance()// почему именно указатель отдаем, а не ссылку
	{
		static Factory f;
		return &f;
	}

private:
	Factory(){}
	~Factory(){}
	std::map<ID, abstractCreator*> creators_;
};

#endif
