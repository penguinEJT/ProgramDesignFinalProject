#ifndef ARCHER_H
#define ARCHER_H

#include <raylib.h>
#include "hero.h"
#include "weapon.h"

typedef struct Archer {
  Hero base;               //法師的基本資訊
}Archer;

Archer* ArcherInit();

#endif
