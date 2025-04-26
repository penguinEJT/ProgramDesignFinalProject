#include "raylib.h"
#include <math.h>

#define MAX_PASSIVES 3

const char *passives[MAX_PASSIVES] = {
    "Regeneration",
    "Max HP +20",
    "Attack Speed +10%"
};

int main(void)
{
    // CHANGED: Reduced window size for a smaller interface
    const int screenWidth = 600;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Passive Skill Selection");

    // 定義顏色
    Color backgroundColor = DARKPURPLE;    // 背景：深紫色
    Color buttonColor = (Color){0, 139, 139, 255}; // 按鈕：深青色
    Color buttonHoverColor = (Color){0, 255, 255, 255}; // 被觸碰的按鈕：亮青色
    Color titleColorBase = GOLD;           // 標題基礎顏色：金色

    Rectangle buttons[MAX_PASSIVES];
    int buttonWidth = 300;
    int buttonHeight = 60;
    // CHANGED: Increased spacing from 10 to 30 for more separation between options
    int spacing = 30;
    int startY = (screenHeight - (buttonHeight * MAX_PASSIVES + spacing * (MAX_PASSIVES - 1))) / 2;

    for (int i = 0; i < MAX_PASSIVES; i++)
    {
        buttons[i] = (Rectangle){
            (screenWidth - buttonWidth) / 2,
            startY + i * (buttonHeight + spacing),
            buttonWidth,
            buttonHeight
        };
    }

    SetTargetFPS(60);

    // CHANGED: Replaced exitWindow with selectedPassive to track selection and return index
    int selectedPassive = -1;

    float time = 0.0f; // Moved time declaration outside loop for clarity

    while (selectedPassive == -1 && !WindowShouldClose())
    {
        // 更新
        time += GetFrameTime();
        Vector2 mousePoint = GetMousePosition();

        BeginDrawing();
        ClearBackground(backgroundColor);

        // 繪製標題「Passive Upgrade」並添加脈動效果
        const char *titleText = "Passive Upgrade";
        int titleWidth = MeasureText(titleText, 30);
        // CHANGED: Fixed alpha calculation to oscillate between 0.5 and 1.0
        float alpha = 0.75f + 0.25f * sinf(time * 2.0f * PI); // 透明度在0.5到1.0之間變化
        Color titleColor = (Color){titleColorBase.r, titleColorBase.g, titleColorBase.b, (unsigned char)(alpha * 255)};
        DrawText(titleText, screenWidth / 2 - titleWidth / 2, 50, 30, titleColor);

        for (int i = 0; i < MAX_PASSIVES; i++)
        {
            Color btnColor = buttonColor;
            if (CheckCollisionPointRec(mousePoint, buttons[i]))
            {
                btnColor = buttonHoverColor;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    // CHANGED: Set selectedPassive to the index of the chosen passive
                    selectedPassive = i;
                    TraceLog(LOG_INFO, "Selected Passive: %s", passives[i]);
                }
            }

            DrawRectangleRec(buttons[i], btnColor);
            int textWidth = MeasureText(passives[i], 20);
            DrawText(passives[i],
                     buttons[i].x + (buttonWidth - textWidth) / 2,
                     buttons[i].y + (buttonHeight - 20) / 2,
                     20,
                     RAYWHITE); // 使用白色文字以提高對比
        }

        EndDrawing();
    }

    CloseWindow();

    // CHANGED: Return the index of the selected passive (-1 if none selected)
    return selectedPassive;
}