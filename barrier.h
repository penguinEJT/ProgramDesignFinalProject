#ifndef BARRIER_H
#define BARRIER_H

#include <raylib.h>
#include "weapon.h"

/*--------------------------------------
結界會依據角色位置持續生成一個半徑為radius的圓，在圓內的敵人會持續受到傷害。
radius會依據attackRange而改變。
--------------------------------------*/

typedef struct Barrier{
  Weapon base;             //結界的基本資訊
  double radius;           //結界的攻擊半徑
}Barrier;

void BarrierAttack(Weapon* self);                        //結界的攻擊函數
void BarrierUpdate(Weapon* self, float deltaTime);       //結界的狀態更新函數
void BarrierDestroy(Weapon* slef);                       //結界的銷毀函數
#endif
