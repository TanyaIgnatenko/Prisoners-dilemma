#ifndef FACTORY_H
#define FACTORY_H

#include <exception>
#include <map>

#include "strategy.h"

template <class PRODUCT>
class AbstractCreator
{
public:
	virtual PRODUCT * operator()() const = 0;
	virtual ~AbstractCreator(){}
};

template <class C, class PRODUCT>
class Creator final: public AbstractCreator <PRODUCT>
{
public:
	PRODUCT * operator()() const override { return new C(); }
	virtual ~Creator(){}
};

template <class ID, class PRODUCT>
class IgnoreErrorPolicy;

template <class ID, class PRODUCT>
class ThrowExceptionErrorPolicy;

template <class ID, class PRODUCT, template <class, class> class ErrorPolicy = ThrowExceptionErrorPolicy>
class Factory
{
public:

	Factory(const Factory &) = delete;
	Factory & operator=(const Factory &) = delete;

	PRODUCT * create(const ID & id)
	{
		auto creator = creators_.find(id);
		if(creators_.end() != creator)
		{
			return (creator->second)->operator()();
		}
		return error_handler.on_create_failed(id);
	}	
	
	template <class C>
	bool doregister(const ID & id)
	{
		auto it = creators_.find(id);
		if (creators_.end() == it)
		{
			creators_[id] = new Creator<C, PRODUCT>();
		}
		else
		{
			error_handler.on_duplicate_registered(id);
		}
		return true;
	}

	bool is_registered(const ID & id) const
	{
		return creators_.find(id) != creators_.end();
	}

	static Factory * instance()
	{
		static Factory f;
		return &f;
	}

	void remove(const ID & id)
	{
		auto it = creators_.find(id);
		if (it != creators_.end())
		{
			delete it->second;
			creators_.erase(it);
		}
		else
		{
			error_handler.on_remove_failed(id);
		}
	}

private:
	Factory(){}
	~Factory()
	{
		for(auto val: creators_)
		{
			delete val.second;
		}
	}
	ErrorPolicy<ID, PRODUCT> error_handler;
	std::map<ID, AbstractCreator<PRODUCT>*> creators_;
};

template <class ID, class PRODUCT>
class IgnoreErrorPolicy
{
public:
	PRODUCT * on_create_failed(const ID & id) const{ return nullptr;}
	void on_duplicate_registered(const ID & id){}
	void on_remove_failed(const ID & id){}
};

template <class ID, class PRODUCT>
class ThrowExceptionErrorPolicy
{
public:

	PRODUCT * on_create_failed(const ID & id) const
	{
		throw std::runtime_error("Factory - can't create object (not registered)");
	}

	void on_remove_failed(const ID & id)
	{
		throw std::runtime_error("Factory - can't remove class (not registered)");
	}

	void on_duplicate_registered(const ID & id)
	{
		throw std::runtime_error("Factory - class already registered");
	}
};

#endif
