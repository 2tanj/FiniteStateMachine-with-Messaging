#ifndef POTIONWITCH_H
#define POTIONWITCH_H

#include <string>

#include "FSM/State.h"
#include "FSM/BaseGameEntity.h"
#include "FSM/Locations.h"
#include "WitchStates.h" // witch states
#include "Misc/ConsoleUtils.h"
#include "FSM/StateMachine.h"
#include "Misc/Utils.h"

#define MAX_POTIONS         10
#define STARTING_POTIONS    3

class Witch : public BaseGameEntity
{
private:
    //an instance of the state machine class
    StateMachine<Witch>* m_pStateMachine;

    location_type m_Location;
    int _potionCount;

public:
    Witch(int id) :BaseGameEntity(id),
        m_Location(WITCHES_CAULDRON), //starting state
        _potionCount(STARTING_POTIONS)
    {
        m_pStateMachine = new StateMachine<Witch>(this);
        m_pStateMachine->SetCurrentState(BrewPotions::Instance());
    }

    ~Witch() { delete m_pStateMachine; }

    void Update() {
        SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        m_pStateMachine->Update();
    }

    virtual bool HandleMessage(const Telegram& msg) { return m_pStateMachine->HandleMessage(msg); }

    // GETTERS
    StateMachine<Witch>* GetFSM()const { return m_pStateMachine; }
    location_type Location()const { return m_Location; }

    const inline int GetPotionCount() { return _potionCount; }

    // SETTERS
    void ChangeLocation(const location_type loc) { m_Location = loc; }

    void BrewPotion() {
        if (_potionCount < MAX_POTIONS)
            _potionCount++;
    }

    bool ServePotion() { 
        if (_potionCount > 0) {
            _potionCount--;
            return true;
        }
        else
            return false;
    }
};

#endif
