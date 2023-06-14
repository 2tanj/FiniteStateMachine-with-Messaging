#include "Entities/WizardStates.h"
#include "FSM/State.h"
#include "Entities/Wizard.h"
#include "FSM/Locations.h"
#include "FSM/EntityNames.h"
#include "Messaging/MessageTypes.h"
#include "Messaging/MessageDispatcher.h"
#include "Misc/utils.h"

#include <iostream>

// ----------------------------------ENTER_LIBRARY_AND_STUDY
EnterLibraryAndStudy* EnterLibraryAndStudy::Instance()
{
	static EnterLibraryAndStudy instance;
	return &instance;
}
void EnterLibraryAndStudy::Enter(Wizard* w)
{
    if (w->Location() != LIBRARY)
    {
        std::cout << "\n" << GetNameOfEntity(w->ID()) << ": " << "Going to the library.";

        w->ChangeLocation(LIBRARY);
    }
}
void EnterLibraryAndStudy::Execute(Wizard* w)
{
    w->IncreaseTimeStudied();
    w->IncreaseFatigue();

    std::cout << "\n" << GetNameOfEntity(w->ID()) << ": " << "Im studying.";

    if (w->HasStudiedEnough())
        w->GetFSM()->ChangeState(PracticeCastingSpells::Instance());

    else if (w->IsTired())
        w->GetFSM()->ChangeState(SleepTillRested::Instance());
}
void EnterLibraryAndStudy::Exit(Wizard* w)
{
    std::cout << "\n" << GetNameOfEntity(w->ID()) << ": "
        << "Im leaving the library.\n";
}
bool EnterLibraryAndStudy::OnMessage(Wizard* w, const Telegram& msg) {
    return false;
}

// ----------------------------------PRACTICE_BROOMSTICK_FLYING
PracticeBroomstickFlying* PracticeBroomstickFlying::Instance()
{
    static PracticeBroomstickFlying instance;
    return &instance;
}
void PracticeBroomstickFlying::Enter(Wizard* w)
{
    if (w->Location() != QUIDDITCH_PITCH)
    {
        std::cout << "\n" << GetNameOfEntity(w->ID()) << ": " << "Going to the quiddich pitch.";

        w->ChangeLocation(QUIDDITCH_PITCH);
    }
}
void PracticeBroomstickFlying::Execute(Wizard* w)
{
    w->IncreaseBroomstickConfidence();
    w->IncreaseFatigue();

    std::cout << "\n" << GetNameOfEntity(w->ID()) << ": " << "Im practicing broomstick flying.";

    if (w->IsBroomstickConfident())
        w->GetFSM()->ChangeState(GoToMageBattle::Instance());
}
void PracticeBroomstickFlying::Exit(Wizard* w)
{
    std::cout << "\n" << GetNameOfEntity(w->ID()) << ": "
        << "Im leaving the quiddich pitch.\n";
}
bool PracticeBroomstickFlying::OnMessage(Wizard* w, const Telegram& msg) {
    return false;
}

// ----------------------------------PRACTICE_CASTING_SPELLS
PracticeCastingSpells* PracticeCastingSpells::Instance()
{
    static PracticeCastingSpells instance;
    return &instance;
}
void PracticeCastingSpells::Enter(Wizard* w)
{
    if (w->Location() != PRACTICE_RANGE)
    {
        std::cout << "\n" << GetNameOfEntity(w->ID()) << ": " << "Going to the practice range.";

        w->ChangeLocation(PRACTICE_RANGE);
    }
}
void PracticeCastingSpells::Execute(Wizard* w)
{
    w->IncreaseSpellConfidence();
    w->IncreaseFatigue();

    std::cout << "\n" << GetNameOfEntity(w->ID()) << ": " << "Im practicing casting spells.";

    if (w->IsSpellsConfident())
        w->GetFSM()->ChangeState(GoToMageBattle::Instance());
    else if (w->IsTired())
        w->GetFSM()->ChangeState(SleepTillRested::Instance());
}
void PracticeCastingSpells::Exit(Wizard* w)
{
    std::cout << "\n" << GetNameOfEntity(w->ID()) << ": "
        << "Im leaving the practice range.\n";
}
bool PracticeCastingSpells::OnMessage(Wizard* w, const Telegram& msg) {
    return false;
}

// ----------------------------------GO_TO_MAGE_BATTLE
GoToMageBattle* GoToMageBattle::Instance()
{
    static GoToMageBattle instance;
    return &instance;
}
void GoToMageBattle::Enter(Wizard* w)
{
    if (w->Location() != BATTLEFIELD)
    {
        std::cout << "\n" << GetNameOfEntity(w->ID()) << ": " << "Going to the battlefield!";

        w->ChangeLocation(BATTLEFIELD);
    }
}
void GoToMageBattle::Execute(Wizard* w)
{
    w->ResetStats();
    std::cout << "\n" << GetNameOfEntity(w->ID()) << ": " << "Im having a mage battle.";

    // the result of the battle is random
    // our mage has a 60% chance to win
    float battleOutcome = RandFloat();
    std::cout << " - " << battleOutcome << std::endl;

    if (battleOutcome <= .60f) {
        std::cout << "\n" << GetNameOfEntity(w->ID()) << ": " << "I won the battle!";
        w->GetFSM()->ChangeState(DrinkMagicPotion::Instance());
    }
    else {
        std::cout << "\n" << GetNameOfEntity(w->ID()) << ": " << "I lost the battle!";
        w->GetFSM()->ChangeState(SleepTillRested::Instance());
    }
}
void GoToMageBattle::Exit(Wizard* w)
{
    std::cout << "\n" << GetNameOfEntity(w->ID()) << ": "
        << "Im leaving the battlefield.\n";
}
bool GoToMageBattle::OnMessage(Wizard* w, const Telegram& msg) {
    return false;
}

// ----------------------------------SLEEP_TILL_RESTED
SleepTillRested* SleepTillRested::Instance()
{
	static SleepTillRested instance;
	return &instance;
}
void SleepTillRested::Enter(Wizard* w)
{
    if (w->Location() != BEDROOM)
    {
        std::cout << "\n" << GetNameOfEntity(w->ID()) << ": " << "Im exhausted, heading to bed.";

        w->ChangeLocation(BEDROOM);
    }
}
void SleepTillRested::Execute(Wizard* w)
{
    w->Sleep();

    std::cout << "\n" << GetNameOfEntity(w->ID()) << ": " << "zzz";

    if (!w->IsTired())
    {
        w->GetFSM()->ChangeState(DrinkMagicPotion::Instance());
    }
}
void SleepTillRested::Exit(Wizard* w)
{
    std::cout << "\n" << GetNameOfEntity(w->ID()) << ": "
        << "I have slept, i'm now leaving the bedroom.\n";
}
bool SleepTillRested::OnMessage(Wizard* w, const Telegram& msg) {
    return false;
}

// ----------------------------------DRINK_MAGIC_POTION
DrinkMagicPotion* DrinkMagicPotion::Instance()
{
    static DrinkMagicPotion instance;
    return &instance;
}
void DrinkMagicPotion::Enter(Wizard* w)
{
    if (w->Location() != WITCHES_CAULDRON)
    {
        std::cout << "\n" << GetNameOfEntity(w->ID()) << ": " << "Going for a drink.";

        w->ChangeLocation(WITCHES_CAULDRON);

        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
                                  w->ID(),
                                  ent_Witch,
                                  msg_WizardArrived,
                                  NO_ADDITIONAL_INFO);
    }
}
void DrinkMagicPotion::Execute(Wizard* w)
{
    w->DecreaseThirst();

    std::cout << "\n" << GetNameOfEntity(w->ID()) << ": " << "Having a drink!";

    if (w->IsntThirsty())
    {
        if (RandBool())
            w->GetFSM()->ChangeState(EnterLibraryAndStudy::Instance());
        else
            w->GetFSM()->ChangeState(PracticeBroomstickFlying::Instance());

    }
}
void DrinkMagicPotion::Exit(Wizard* w)
{
    std::cout << "\n" << GetNameOfEntity(w->ID()) << ": "
        << "I had a drink, now im leaving.\n";

    Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
                              w->ID(),
                              ent_Witch,
                              msg_WizardLeft,
                              NO_ADDITIONAL_INFO);
}
bool DrinkMagicPotion::OnMessage(Wizard* w, const Telegram& msg) {


    return false;
}