#ifndef WIZARD_H
#define WIZARD_H

#include <raylib.h>
#include "hero.h"
#include "weapon.h"

typedef struct Wizard {
  Hero base;               //法師的基本資訊
}Wizard;

Wizard* WizardInit();

#endif
