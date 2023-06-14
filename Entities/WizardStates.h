#pragma once
#include "FSM/State.h"

class Wizard;
struct Telegram;

// ---------------------------------------------------------------------------------------------
class EnterLibraryAndStudy : public State<Wizard>
{
private:
	EnterLibraryAndStudy() {}

	//copy ctor and assignment should be private
	EnterLibraryAndStudy(const EnterLibraryAndStudy&);
	EnterLibraryAndStudy& operator=(const EnterLibraryAndStudy&);

public:
	static EnterLibraryAndStudy* Instance();

	virtual void Enter(Wizard* miner);
	virtual void Execute(Wizard* miner);
	virtual void Exit(Wizard* miner);
	virtual bool OnMessage(Wizard* miner, const Telegram& msg);
};

// ---------------------------------------------------------------------------------------------
class PracticeBroomstickFlying : public State<Wizard>
{
private:
	PracticeBroomstickFlying() {}

	//copy ctor and assignment should be private
	PracticeBroomstickFlying(const PracticeBroomstickFlying&);
	PracticeBroomstickFlying& operator=(const PracticeBroomstickFlying&);

public:
	static PracticeBroomstickFlying* Instance();

	virtual void Enter(Wizard* miner);
	virtual void Execute(Wizard* miner);
	virtual void Exit(Wizard* miner);
	virtual bool OnMessage(Wizard* miner, const Telegram& msg);
};

// ---------------------------------------------------------------------------------------------
class PracticeCastingSpells : public State<Wizard>
{
private:
	PracticeCastingSpells() {}

	//copy ctor and assignment should be private
	PracticeCastingSpells(const PracticeCastingSpells&);
	PracticeCastingSpells& operator=(const PracticeCastingSpells&);

public:
	static PracticeCastingSpells* Instance();

	virtual void Enter(Wizard* miner);
	virtual void Execute(Wizard* miner);
	virtual void Exit(Wizard* miner);
	virtual bool OnMessage(Wizard* miner, const Telegram& msg);
};

// ---------------------------------------------------------------------------------------------
class SleepTillRested : public State<Wizard>
{
private:
	SleepTillRested() {}

	//copy ctor and assignment should be private
	SleepTillRested(const SleepTillRested&);
	SleepTillRested& operator=(const SleepTillRested&);

public:
	static SleepTillRested* Instance();

	virtual void Enter(Wizard* miner);
	virtual void Execute(Wizard* miner);
	virtual void Exit(Wizard* miner);
	virtual bool OnMessage(Wizard* miner, const Telegram& msg);
};

// ---------------------------------------------------------------------------------------------
class DrinkMagicPotion : public State<Wizard>
{
private:
	DrinkMagicPotion() {}

	//copy ctor and assignment should be private
	DrinkMagicPotion(const DrinkMagicPotion&);
	DrinkMagicPotion& operator=(const DrinkMagicPotion&);

public:
	static DrinkMagicPotion* Instance();

	virtual void Enter(Wizard* miner);
	virtual void Execute(Wizard* miner);
	virtual void Exit(Wizard* miner);
	virtual bool OnMessage(Wizard* miner, const Telegram& msg);
};

// ---------------------------------------------------------------------------------------------
class GoToMageBattle : public State<Wizard>
{
private:
	GoToMageBattle() {}

	//copy ctor and assignment should be private
	GoToMageBattle(const GoToMageBattle&);
	GoToMageBattle& operator=(const GoToMageBattle&);

public:
	static GoToMageBattle* Instance();

	virtual void Enter(Wizard* miner);
	virtual void Execute(Wizard* miner);
	virtual void Exit(Wizard* miner);
	virtual bool OnMessage(Wizard* miner, const Telegram& msg);
};
