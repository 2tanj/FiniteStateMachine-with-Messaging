#include <fstream>

#include "FSM/Locations.h"
#include "Entities/Wizard.h"
#include "Entities/Witch.h"
#include "Misc/ConsoleUtils.h"
#include "FSM/EntityNames.h"
#include "FSM/EntityManager.h"

#define UPDATE_REPETITIONS 30

int main()
{
    srand(time(NULL));

    Wizard Wizard(ent_Wizard);
    Witch Witch(ent_Witch);

    EntityMgr->RegisterEntity(&Wizard);
    EntityMgr->RegisterEntity(&Witch);

    for (int i=0; i < UPDATE_REPETITIONS; ++i) { 
        Wizard.Update();
        Witch.Update();

        Sleep(1000);
    }

    PressAnyKeyToContinue();

  return 0;
}