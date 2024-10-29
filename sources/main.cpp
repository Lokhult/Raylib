#include "raylib.h"
#include "hsla/numeric_array.h"

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "Window title"

int main(void)
{
    numeric_array color1{150, 150, 255, 2500};
    numeric_array color2{255, 150, 150, 2500};
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    // Texture2D texture = LoadTexture(ASSETS_PATH"test.png"); // Check README.md for how this works

    while (!WindowShouldClose())
    {
        BeginDrawing();
        auto x = color1 * 0.5;
        auto y = color2 * 0.5;
        auto z = color1 + color2;
        Color d = {x[0], x[1], x[2], x[3]};
        ClearBackground(d);

        // const int texture_x = SCREEN_WIDTH / 2 - texture.width / 2;
        // const int texture_y = SCREEN_HEIGHT / 2 - texture.height / 2;
        // DrawTexture(texture, texture_x, texture_y, WHITE);

        const char *text = "OMG! IT WORKS!";
        const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 20, 1);
        // DrawText(text, SCREEN_WIDTH / 2 - text_size.x / 2, texture_y + texture.height + text_size.y + 10, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
