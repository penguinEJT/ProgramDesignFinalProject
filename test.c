#include <stdio.h>
#include <raylib.h>
#include "warrior.h"
#include "lasergun.h"

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "test");

  Warrior* warrior = WarriorInit();
  LaserGun* laser = (LaserGun*)warrior->base.weapons[0];

  printf("%s\n", warrior->base.weapons[0]->name);

  double preTime = GetTime();
  double curTime = preTime;

  SetTargetFPS(60);

  while(!WindowShouldClose()){
    warrior->base.move(&warrior->base);
    printf("Laser gun cool time : %f\n", laser->base.curCooldownTime);

    printf("Laser gun position : (%f, %f)\n", laser->base.position.x, laser->base.position.y);

    printf("Hero position : (%f, %f)\n", warrior->base.position.x, warrior->base.position.y);
    printf("Laser gun rotation angle : %f\n", laser->box.rotationAngle);

    curTime = GetTime();
    double timeDiff = curTime - preTime;
    preTime = curTime;

    BeginDrawing();
    ClearBackground(WHITE);
    warrior->base.draw(&warrior->base);
    warrior->base.update(&warrior->base, timeDiff);

    EndDrawing();
  }
}
