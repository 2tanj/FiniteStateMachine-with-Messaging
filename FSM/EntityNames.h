#ifndef NAMES_H
#define NAMES_H

#include <string>

enum
{
  ent_Wizard,
  ent_Witch
};

inline std::string GetNameOfEntity(int n)
{
  switch(n)
  {
  case ent_Wizard:
      return "Wizard";
  case ent_Witch:
      return "Witch";

  default:
    return "UNKNOWN!";
  }
}

#endif