#include "raylib.h"
#include <stdio.h>
#include <math.h>

#define BUTTON_WIDTH 250
#define BUTTON_HEIGHT 60
#define BUTTON_PADDING 30

// 武器名稱和描述
const char *weaponNames[] = {
    "Fireball", "LaserGun", "Katana", "ShockStaff", "Whip", "Barrier"
};

const char *weaponDescriptions[] = {
    "Fireball rotates around the player, attacking enemies.",
    "LaserGun fires a laser beam to attack enemies in front.",
    "Katana slashes enemies, cutting them down.",
    "ShockStaff emits a shockwave around the player, knocking enemies back.",
    "Whip swings horizontally to attack enemies.",
    "Barrier creates a field that attacks enemies inside it."
};

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    // 定義介面的顏色
    Color backgroundColor = BLACK;
    Color buttonNormalColor = MAROON;
    Color buttonHoveredColor = RED;
    Color buttonBorderColor = RED;
    Color buttonTextColor = WHITE;
    Color descriptionTextColor = YELLOW;

    int num_rows = 3;
    int total_height = num_rows * BUTTON_HEIGHT + (num_rows - 1) * BUTTON_PADDING;
    int starting_y = (screenHeight - total_height) / 2;

    InitWindow(screenWidth, screenHeight, "Weapon Selection");
    SetTargetFPS(60);

    int hoveredButton = -1;
    int selectedWeapon = -1;
    float time = 0.0f;

    while (!WindowShouldClose() && selectedWeapon == -1) {
        time += GetFrameTime();
        Vector2 mousePoint = GetMousePosition();
        hoveredButton = -1;

        for (int i = 0; i < 6; i++) {
            int row = i % num_rows;
            int col = i / num_rows;
            float x = (col == 0) ? 50 : (screenWidth - 50 - BUTTON_WIDTH);
            float y = starting_y + row * (BUTTON_HEIGHT + BUTTON_PADDING);
            Rectangle buttonRect = {x, y, BUTTON_WIDTH, BUTTON_HEIGHT};

            if (CheckCollisionPointRec(mousePoint, buttonRect)) {
                hoveredButton = i;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    selectedWeapon = i;
                    printf("Selected weapon: %s\n", weaponNames[i]);
                }
            }
        }


        BeginDrawing();
        ClearBackground(backgroundColor);

        //劃出標題
        const char *titleText = "Choose Your Favorite Weapon";
        int titleWidth = MeasureText(titleText, 30);
        float alpha = 0.5f + 0.5f * sinf(time * 2.0f * PI); // Alpha oscillates between 0.5 and 1.0
        Color titleColor = (Color){descriptionTextColor.r, descriptionTextColor.g, descriptionTextColor.b, (unsigned char)(alpha * 255)};
        DrawText(titleText, screenWidth/2 - titleWidth/2, 50, 30, titleColor);

        for (int i = 0; i < 6; i++) {
            int row = i % num_rows;
            int col = i / num_rows;
            float x = (col == 0) ? 50 : (screenWidth - 50 - BUTTON_WIDTH);
            float y = starting_y + row * (BUTTON_HEIGHT + BUTTON_PADDING);
            Rectangle buttonRect = {x, y, BUTTON_WIDTH, BUTTON_HEIGHT};

            if (i == hoveredButton) {
                DrawRectangleRec(buttonRect, buttonHoveredColor);
            } else {
                DrawRectangleRec(buttonRect, buttonNormalColor);
            }
            DrawRectangleLinesEx(buttonRect, 2, buttonBorderColor);

            //武器名稱
            int textWidth = MeasureText(weaponNames[i], 20);
            DrawText(weaponNames[i], buttonRect.x + buttonRect.width/2 - textWidth/2, buttonRect.y + 15, 20, buttonTextColor);
        }

        // 怕有人不選
        if (hoveredButton != -1) {
            int descWidth = MeasureText(weaponDescriptions[hoveredButton], 20);
            DrawText(weaponDescriptions[hoveredButton], screenWidth/2 - descWidth/2, 500, 20, descriptionTextColor);
        }

        EndDrawing();
    }

    CloseWindow();
    return selectedWeapon;
}
