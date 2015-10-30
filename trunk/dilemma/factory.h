#ifndef FACTORY_H
#define FACTORY_H

#include <map>
#include <sstream>

#include "strategy.h"

template <class Base>
class abstractCreator
{
public:
	virtual Base * operator()() const = 0;
};

template <class C, class Base>
class Creator final: public abstractCreator <Base>
{
public:
	Base * operator()() const override { return new C(); }
};

template <class ID, class PRODUCT>
class FactoryIgnoreErrorPolicy;

template <class ID, class PRODUCT>
class FactoryThrowExceptionErrorPolicy;

template <class Base, class ID, class PRODUCT, template <class, class> class FactoryErrorPolicy = FactoryIgnoreErrorPolicy>
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
		return error_handler.onCreateFailed(id);
	}	
	
	template <class C>
	bool doregister(const ID & id)
	{
		auto it = creators_.find(id);
		if (creators_.end() == it)
		{
			creators_[id] = new Creator<C, Base>();
		}
		else
		{
			error_handler.onDuplicateRegistered(id);
		}
		return true;
	}

	bool is_registered(const ID & id)
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
			error_handler.onRemoveFailed(id);
		}
	}

private:
	Factory(){}
	~Factory(){}
	FactoryErrorPolicy<ID, PRODUCT> error_handler;
	std::map<ID, abstractCreator<Base>*> creators_;
};

class FactoryException : public std::exception
{
public:

	FactoryException(const std::string & msg) throw() : _msg(msg) {}
	virtual ~FactoryException() throw() {}
	
	virtual const char * what() const throw(){ return _msg.c_str();}
	
private:

	std::string	_msg;
};

template <class ID, class PRODUCT>
class FactoryIgnoreErrorPolicy
{
public:
	PRODUCT * onCreateFailed(const ID & id) const{ return nullptr;}
	void onDuplicateRegistered(const ID & id){}
	void onRemoveFailed(const ID & id){}
};

template <class ID, class PRODUCT>
class FactoryThrowExceptionErrorPolicy
{
public:
	std::string generateMessage(const char * msg, const ID & id) const
	{
		std::stringstream strm;
		strm << msg << ", requested type id : " << id;
		return strm.str();
	}

	PRODUCT * onCreateFailed(const ID & id) const
	{
		throw FactoryException(generateMessage("Factory - can't create object (not registered)", id));
	}

	void onRemoveFailed(const ID & id)
	{
		throw FactoryException(generateMessage("Factory - can't remove class (not registered)", id));
	}

	void onDuplicateRegistered(const ID & id)
	{
		throw FactoryException(generateMessage("Factory - class already registered", id));
	}
};

#endif
