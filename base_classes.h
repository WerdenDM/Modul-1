#pragma once
#include <list>
#include <iostream>
class Base;

using list_iterator = std::list<Base*>::iterator;
extern int S;
class Base
{
protected:
	static int N;
	int id;
	static std::list<Base*> instances;
	list_iterator current_instance_position;

	virtual void updateCount() = 0
	{
		N++;
	}

	list_iterator register_this()
	{
		instances.push_back(this);
		return std::prev(std::end(instances));
	}

	void unregister_this()
	{
		instances.erase(current_instance_position);
	}
public:
	Base()
	{
		id = getCount();
		updateCount();
		current_instance_position = register_this();
	}

	virtual int getCount() const = 0 { return N; }
	
	virtual int getId() const { return id; }

	virtual int get_new_value(int current_value) const = 0
	{
		return 2 * current_value - N + 25;
	}

	virtual const std::list<Base*>& get_register_classes() const
	{
		return instances;
	}


	virtual ~Base()
	{ 
		unregister_this();
		std::cout << "Base class dectructed" << std::endl;
	}
};

class Alpha : public Base
{
private:
	static int N_alpha;
protected:
	virtual void updateCount() override
	{
		++N_alpha;
	}
public:
	Alpha() :Base() 
	{
		id = getCount();
		updateCount();
	}

	virtual int getCount() const override
	{
		return N_alpha;
	}


	virtual int get_new_value(int current_value) const override
	{
		return current_value - N;
	}

	virtual ~Alpha() override
	{
		S = get_new_value(S);
		std::cout << "Alpha class dectructed" << std::endl;
	}
};

class Beta : public Base
{
private:
	static int N_beta;
protected:
	virtual void updateCount() override
	{
		++N_beta;
	}
public:
	Beta() :Base() 
	{ 
		id = getCount();
		updateCount();
	}
	virtual int getCount() const override
	{
		return N_beta;
	}
	
	virtual int get_new_value(int current_value) const override
	{
		return current_value + N + 25;
	}

	virtual ~Beta() override
	{
		S = get_new_value(S);
		std::cout << "Beta class dectructed" << std::endl;
	}
};

class Gamma : public Base
{
private:
	static int N_gamma;
protected:
	virtual void updateCount() override
	{
		++N_gamma;
	}
public:
	Gamma() :Base() 
	{ 
		id = getCount();
		updateCount(); 
	}
	virtual int getCount() const override
	{
		return N_gamma;
	}
	virtual int get_new_value(int current_value) const override
	{
		return current_value + 3*N;
	}

	virtual ~Gamma() override
	{
		S = get_new_value(S);
		std::cout << "Gamma class dectructed" << std::endl;
	}
};

int predictSValue(const std::list<Base*>& base_classes, int start_value);