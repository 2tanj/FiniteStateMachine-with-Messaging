#include "Entities/WitchStates.h"
#include "FSM/State.h"
#include "Entities/Witch.h"
#include "FSM/Locations.h"
#include "Messaging/MessageDispatcher.h"
#include "Misc/CrudeTimer.h"
#include "FSM/EntityNames.h"
#include "Messaging/MessageTypes.h"
#include "Misc/utils.h"

#include <iostream>

// ----------------------------------BREW_POTIONS
BrewPotions* BrewPotions::Instance()
{
    static BrewPotions instance;
    return &instance;
}
void BrewPotions::Enter(Witch* w)
{
    if (w->Location() != WITCHES_CAULDRON)
    {
        std::cout << "\n" << GetNameOfEntity(w->ID()) << ": " << "Im starting with potion brewing.";

        w->ChangeLocation(WITCHES_CAULDRON);
    }
}
void BrewPotions::Execute(Witch* w)
{
    w->BrewPotion();

    std::cout << "\n" << GetNameOfEntity(w->ID()) << ": " << "Im brewing potions. Potion count: " << w->GetPotionCount();
}
void BrewPotions::Exit(Witch* w)
{
    std::cout << "\n" << GetNameOfEntity(w->ID()) << ": "
        << "Im stopping with potion brewing.\n";
}
bool BrewPotions::OnMessage(Witch* w, const Telegram& msg) {
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg) {
    case msg_WizardArrived:
        std::cout << "\nMessage handled by " << GetNameOfEntity(w->ID())
            << " at time: " << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

        std::cout << "\n" << GetNameOfEntity(w->ID())
                  << ": Coming right up to serve you!";

        w->GetFSM()->ChangeState(ServeCustomers::Instance());
        return true;
    }

    return false;
}

// ----------------------------------SERVE_CUSTOMERS
ServeCustomers* ServeCustomers::Instance()
{
    static ServeCustomers instance;
    return &instance;
}
void ServeCustomers::Enter(Witch* w)
{
    if (w->Location() != WITCHES_CAULDRON)
    {
        std::cout << "\n" << GetNameOfEntity(w->ID()) << ": " << "Im serving customers.";

        w->ChangeLocation(WITCHES_CAULDRON);
    }
}
void ServeCustomers::Execute(Witch* w)
{
    // dialogue changes according to potion inventory
    std::string dialogue  = w->ServePotion() ? "Enjoy your potion!" : "Sorry, we're all out.";

    std::cout << "\n" << GetNameOfEntity(w->ID()) << ": " << dialogue;
}
void ServeCustomers::Exit(Witch* w)
{
    std::cout << "\n" << GetNameOfEntity(w->ID()) << ": "
        << "Im no longer serving customers.\n";
}
bool ServeCustomers::OnMessage(Witch* w, const Telegram& msg) {
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg) {
    case msg_WizardLeft:
        std::cout << "\nMessage handled by " << GetNameOfEntity(w->ID())
            << " at time: " << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

        std::cout << "\n" << GetNameOfEntity(w->ID())
            << ": Thank you for coming, see you next time!";

        w->GetFSM()->ChangeState(BrewPotions::Instance());
        return true;
    }
    return false;
}