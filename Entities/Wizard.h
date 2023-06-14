#ifndef WIZARD_H
#define WIZARD_H

#include <string>

#include "FSM/State.h"
#include "FSM/BaseGameEntity.h"
#include "FSM/Locations.h"
#include "WizardStates.h"
#include "Misc/ConsoleUtils.h"
#include "FSM/StateMachine.h"
#include "Misc/Utils.h"

#define TIREDNESS_THRESHOLD   10
#define THIRST_LEVEL           3
#define STUDY_HOURS            5
#define BROOMSTICK_CONFIDENCE  3
#define SPELLS_CONFIDENCE      3

class Wizard : public BaseGameEntity
{
private:
    //an instance of the state machine class
    StateMachine<Wizard>* m_pStateMachine;

    location_type m_Location;

    int _fatigue;
    int _thirst;
    int _spellsConfidence;
    int _broomstickConfidence;
    int _studyHours;

public:
    Wizard(int id) :BaseGameEntity(id),
        m_Location(BEDROOM), //starting state
        _fatigue(0),
        _thirst(THIRST_LEVEL),
        _spellsConfidence(0),
        _broomstickConfidence(0),
        _studyHours(0)
        {
            m_pStateMachine = new StateMachine<Wizard>(this);
            m_pStateMachine->SetCurrentState(SleepTillRested::Instance());
        }

    ~Wizard() { delete m_pStateMachine; }

    void Update() {
        SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        m_pStateMachine->Update();
    }

    virtual bool HandleMessage(const Telegram& msg) { return m_pStateMachine->HandleMessage(msg); }

    void Sleep() {
        _fatigue = 0;
        _thirst = THIRST_LEVEL;
        _spellsConfidence = 0;
        _broomstickConfidence = 0;
        _studyHours = 0;
    }

    void ResetStats() {
        _spellsConfidence = 0;
        _broomstickConfidence = 0;
        _studyHours = 0;
        _thirst = THIRST_LEVEL;
    }

    // GETTERS
    StateMachine<Wizard>* GetFSM()const { return m_pStateMachine; }
    location_type Location()const { return m_Location; }

    const inline int GetFatigue()               { return _fatigue; }
    const inline int GetThirst()                { return _thirst; }
    const inline int GetSpellConfidence()       { return _spellsConfidence; }
    const inline int GeteBroomstickConfidence() { return _broomstickConfidence; }
    const inline int GetStudyHours()            { return _studyHours; }

    // SETTERS
    void ChangeLocation(const location_type loc) { m_Location = loc; }

    // fatigue
    bool IsTired()      { return _fatigue >= TIREDNESS_THRESHOLD; }
    void DecreaseFatigue() { _fatigue -= 1; }
    void IncreaseFatigue() { _fatigue += 1; }
    
    // thirst
    bool IsntThirsty() { return _thirst <= 0; }
    void SetThirst(int n) { _thirst = n; }
    void DecreaseThirst() { _thirst -= 1; }

    // spell confidence
    bool IsSpellsConfident()       { return _spellsConfidence >= SPELLS_CONFIDENCE; }
    void IncreaseSpellConfidence() { _spellsConfidence++; }
    void SetSpellConfidence(int n) { _spellsConfidence = n; }
    
    // broomstick confidence
    bool IsBroomstickConfident()        { return _broomstickConfidence >= BROOMSTICK_CONFIDENCE; }
    void IncreaseBroomstickConfidence() { _broomstickConfidence++; }
    void SetBroomstickConfidence(int n) { _broomstickConfidence = n; }

    // study hours
    bool HasStudiedEnough() { return _studyHours >= STUDY_HOURS; }
    void IncreaseTimeStudied() { _studyHours++; }
    void SetTimeStudied(int n) { _studyHours = n; }
};

#endif
