#ifndef COLLISIONBOX_H
#define COLLISIONBOX_H

#include <raylib.h>
#include <stdbool.h>

typedef struct CollisionBox{
  Rectangle rec;             //紀錄碰撞箱的長寬與位置
  float rotationAngle;       //紀錄長方形的旋轉角度
}CollisionBox;

CollisionBox* CollisionBoxInit(Rectangle rec, float rotationAngle);       //初始化碰撞箱
bool CheckCollsionBoxes(CollisionBox box1,CollisionBox box2);             //碰撞箱之間執行碰撞檢測
void CollsionBoxRotation(CollisionBox* box, Vector2 vector);               //將碰撞箱的角度調整至與向量vector的方向一致

#endif
