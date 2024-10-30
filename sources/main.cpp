#include "raylib.h"
#include "numeric_array.h"
#include <iostream>

using namespace std;

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "Window title"

Color numeric_array_to_color(rgba &array)
{
    return Color{static_cast<unsigned char>(array[0]), static_cast<unsigned char>(array[1]), static_cast<unsigned char>(array[2]), static_cast<unsigned char>(array[3])};
}

int main(void)
{
    rgba color{150, 150, 255, 2500};
    rgba color1{150, 150, 255, 2500};
    rgba color2{255, 150, 150, 2500};
    vec2 pos1{0, 0};
    vec2 pos2{SCREEN_WIDTH, SCREEN_HEIGHT};
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    // Texture2D texture = LoadTexture(ASSETS_PATH"test.png"); // Check README.md for how this works

    while (!WindowShouldClose())
    {
        BeginDrawing();
        auto delta = GetTime() / 10;
        auto x = color1 * (1 - delta);
        auto y = color2 * delta;
        vec2 weights{delta, 1.0 - delta};
        auto pos = vec2::blend({pos1, pos2}, weights, vec2::blend_mode::linear);
        ClearBackground(numeric_array_to_color(color1));

        // ClearBackground(RAYWHITE);
        DrawCircle(pos[0], pos[1], 50, BLACK);

        // DrawCircle(50, 150, 50, BLACK);
        // DrawCircle(150, 150, 50, BLACK);
        // const int texture_x = SCREEN_WIDTH / 2 - texture.width / 2;
        // const int texture_y = SCREEN_HEIGHT / 2 - texture.height / 2;
        // DrawTexture(texture, texture_x, texture_y, WHITE);
        // string str = to_string(pos[0]) + to_string(pos[1]) + to_string(pos[2]) + to_string(pos[3]);
        // const char *text = str.c_str();
        // const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 20, 1);
        // DrawText(text, SCREEN_WIDTH / 2 - text_size.x / 2, 150, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
