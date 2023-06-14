#pragma once
#include "FSM/State.h"

class Witch;
struct Telegram;

// ---------------------------------------------------------------------------------------------
class BrewPotions : public State<Witch>
{
private:
	BrewPotions() {}

	//copy BrewPotions  and assignment should be private
	BrewPotions(const BrewPotions&);
	BrewPotions& operator=(const BrewPotions&);

public:
	static BrewPotions* Instance();

	virtual void Enter(Witch* witch);
	virtual void Execute(Witch* witch);
	virtual void Exit(Witch* witch);
	virtual bool OnMessage(Witch* witch, const Telegram& msg);
};

// ---------------------------------------------------------------------------------------------
class ServeCustomers : public State<Witch>
{
private:
	ServeCustomers() {}

	//copy BrewPotions  and assignment should be private
	ServeCustomers(const ServeCustomers&);
	ServeCustomers& operator=(const ServeCustomers&);

public:
	static ServeCustomers* Instance();

	virtual void Enter(Witch* witch);
	virtual void Execute(Witch* witch);
	virtual void Exit(Witch* witch);
	virtual bool OnMessage(Witch* witch, const Telegram& msg);
};