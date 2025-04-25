#ifndef WARRIOR_H
#define WARRIOR_H

#include <raylib.h>
#include "hero.h"
#include "weapon.h"

typedef struct Warror {
  Hero base;               //戰士的基本資訊
}Warrior;

Warrior* WarriorInit();

#endif
