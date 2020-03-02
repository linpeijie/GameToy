/*
小镇上居民的名字
*/
#ifndef ENTITY_NAMES_H
#define ENTITY_NAMES_H

#include <string>

enum
{
  ent_Miner_Bob,

  ent_Elsa
};

inline std::string GetNameOfEntity(int n)
{
  switch(n)
  {
  case ent_Miner_Bob:

    return "Miner Bob";

  case ent_Elsa:

    return "Elsa";

  default:

    return "UNKNOWN!";
  }
}

#endif