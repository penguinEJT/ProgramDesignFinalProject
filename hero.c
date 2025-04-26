#include <raylib.h>
#include <stdlib.h>
#include <string.h>
#include "hero.h"
#include "collisionbox.h"
#include "weapon.h"
#include "selectioninterface.h"


Hero* HeroInit(char name[51], Vector2 position, Texture2D texture, double attackPower, double speed, double hp, double pickupRadius) {
  Hero* hero = (Hero*)malloc(sizeof(Hero));

  strcpy(hero->name, name);

  hero->position = position;
  hero->direction = (Vector2){0,0};
  hero->texture = texture;

  hero->weaponCount = 0;
  hero->hpRecoveryRate = 0.0;
  hero->level = 1;
  hero->exp = 0;
  hero->nextLevelExp = 100;  // 需要100經驗值升級

  hero->attackPower = attackPower;
  hero->speed = speed;
  hero->hp = hp;
  hero->pickupRadius = pickupRadius; 

  hero->move = HeroMove;
  hero->draw = HeroDraw;
  hero->update = HeroUpdate;
  hero->destroy = HeroDestroy;

  return hero;
}  

void HeroMove(Hero* self) {
  Vector2 nextDirection = (Vector2){0, 0};

  if(IsKeyDown(KEY_UP)) {
    self->position.y -= self->speed;
    nextDirection.y = 1;
  }
  if(IsKeyDown(KEY_DOWN)) {
    self->position.y += self->speed;
    nextDirection.y = -1;
  }
  if(IsKeyDown(KEY_RIGHT)) {
    self->position.x += self->speed;
    nextDirection.x = 1;
  }
  if(IsKeyDown(KEY_LEFT)) {
    self->position.x -= self->speed;
    nextDirection.x = -1;
  }

  if(nextDirection.x ==0 && nextDirection.y ==0) {
    return;
  }

  self->direction = nextDirection;
}   

void HeroDraw(Hero* self) {
  //角色面朝右方，正常繪製貼圖
  if(self->direction.x == 1) {
    DrawTexture(self->texture, self->position.x, self->position.y, WHITE);
  }
  //角色面朝左方，將貼圖左右反轉後再繪製
  else {
    Rectangle source = {0, 0, -self->texture.width, self->texture.height};
    DrawTextureRec(self->texture, source,self->position, WHITE);
  }
}

void HeroUpdate(Hero *self, double deltaTime) {
  //調整碰撞箱的大小和位置
  self->box.rec.width = self->texture.width;
  self->box.rec.height = self->texture.height;

  self->box.rec.x = self->position.x;
  self->box.rec.y = self->position.y;

  //更新各個武器的狀態
  for(int i=0; i<self->weaponCount; i++) {

    //調整武器位置
    self->weapons[i]->position.x = self->position.x;
    self->weapons[i]->position.y = self->position.y;
    //調整武器方向
    self->weapons[i]->direction = self->direction;

    //調整各個武器的狀態
    self->weapons[i]->update(self->weapons[i], deltaTime);     
  }
}

void HeroDestroy(Hero *self) {
  free(self);
}
