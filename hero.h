#ifndef HERO_H
#define HERO_H

#include <raylib.h>
#include "weapon.h"
#include "collisionbox.h"

typedef struct Hero{
  char name[51];                   //英雄名稱

  Vector2 position;                //英雄位置
  Vector2 direction;               //英雄目前的朝向
  Texture2D texture;               //英雄的貼圖
  CollisionBox box;                //碰撞箱，用於執行碰撞檢測

  Weapon* weapons[6];              //英雄目前持有的武器
  unsigned int weaponCount;        //英雄目前的武器數量，上限為6

  double speed;                    //英雄的移動速度
  double hp;                       //英雄的血量
  double attackPower;              //角色攻擊力
  double pickupRadius;             //英雄的拾取半徑

  void (*move)(Hero* self, KeyboardKey key);   //角色移動
  void (*update)(Hero* self, float deltaTime); //角色狀態更新
  void (*destroy)(Hero* self);                 //角色銷毀函數,將角色從記憶體中刪除
}Hero;

Hero* HeroInit(Vector2 position, Vector2 direction, Texture2D texture, double attackPower, double speed, double hp, double pickupRange);   //角色初始化函數

void heroMove(Hero* self, KeyboardKey);    //依照輸入決定角色移動

#endif
