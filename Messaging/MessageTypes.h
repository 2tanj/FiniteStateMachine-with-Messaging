#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
    msg_WizardArrived,
    msg_WizardLeft
};


inline std::string MsgToStr(int msg)
{
    switch (msg)
    {
    case msg_WizardArrived:
        return "WizardArrived";

    case msg_WizardLeft:
        return "WizardLeft";

    default:
        return "Not recognized!";
    }
}

#endif