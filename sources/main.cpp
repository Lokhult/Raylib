#include "raylib.h"
#include "numeric_array/numeric_array.h"
#include <iostream>
// #include <algorithm>

using namespace std;

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "Window title"

Color numeric_array_to_color(numeric_array &array)
{
    return Color{static_cast<unsigned char>(array[0]), static_cast<unsigned char>(array[1]), static_cast<unsigned char>(array[2]), static_cast<unsigned char>(array[3])};
}

int main(void)
{
    numeric_array color1{150, 150, 255, 2500};
    numeric_array color2{255, 150, 150, 2500};
    auto pos = numeric_array::linear_range(0, 250, 5);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    // Texture2D texture = LoadTexture(ASSETS_PATH"test.png"); // Check README.md for how this works

    while (!WindowShouldClose())
    {
        BeginDrawing();
        auto delta = GetTime() / 10;
        auto x = color1 * (1 - delta);
        auto y = color2 * delta;
        ClearBackground(numeric_array_to_color(color1));

        for (auto p: pos)
            DrawCircle(p, p, 50, BLACK);

        // DrawCircle(50, 150, 50, BLACK);
        // DrawCircle(150, 150, 50, BLACK);
        // const int texture_x = SCREEN_WIDTH / 2 - texture.width / 2;
        // const int texture_y = SCREEN_HEIGHT / 2 - texture.height / 2;
        // DrawTexture(texture, texture_x, texture_y, WHITE);
        string str = to_string(pos[0]) + to_string(pos[1]) + to_string(pos[2]) + to_string(pos[3]);
        const char *text = str.c_str();
        const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 20, 1);
        DrawText(text, SCREEN_WIDTH / 2 - text_size.x / 2, 150, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
