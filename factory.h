#ifndef FACTORY_H
#define FACTORY_H

#include <map>
#include <sstream>

#include "strategy.h"

template <class Base>
class AbstractCreator
{
public:
	virtual Base * operator()() const = 0;
};

template <class C, class Base>
class Creator final: public AbstractCreator <Base>
{
public:
	Base * operator()() const override { return new C(); }
};

template <class ID, class PRODUCT>
class IgnoreErrorPolicy;

template <class ID, class PRODUCT>
class ThrowExceptionErrorPolicy;

template <class Base, class ID, class PRODUCT, template <class, class> class ErrorPolicy = IgnoreErrorPolicy>
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
			creators_[id] = new Creator<C, Base>();
		}
		else
		{
			error_handler.on_duplicate_registered(id);
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
			error_handler.on_remove_failed(id);
		}
	}

private:
	Factory(){}
	~Factory(){}
	ErrorPolicy<ID, PRODUCT> error_handler;
	std::map<ID, AbstractCreator<Base>*> creators_;
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
	std::string generate_message(const char * msg, const ID & id) const
	{
		std::stringstream strm;
		strm << msg << ", requested type id : " << id;
		return strm.str();
	}

	PRODUCT * on_create_failed(const ID & id) const
	{
		throw FactoryException(generate_message("Factory - can't create object (not registered)", id));
	}

	void on_remove_failed(const ID & id)
	{
		throw FactoryException(generate_message("Factory - can't remove class (not registered)", id));
	}

	void on_duplicate_registered(const ID & id)
	{
		throw FactoryException(generate_message("Factory - class already registered", id));
	}
};

#endif
