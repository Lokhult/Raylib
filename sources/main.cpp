#include <vector>

#include "raylib.h"
#include "numeric_array.h"
#include "transition.h"

using namespace std;

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "Window title"

Color numeric_array_to_color(rgba &array)
{
    return Color{static_cast<unsigned char>(array[0]), static_cast<unsigned char>(array[1]), static_cast<unsigned char>(array[2]), static_cast<unsigned char>(array[3])};
}

vector<double> linear_range(double start, double end, double count)
{
    std::vector<double> result;
    double range = end - start;
    double delta = range / (count - 1);

    for (double i = start; i < count; i++)
    {
        result.push_back(start + delta * i);
    }

    return result;
}

vec2 denormalized_coords(vec2 coords)
{
    return vec2{coords[0] * SCREEN_WIDTH, coords[1] * SCREEN_HEIGHT};
}

int main(void)
{
    rgba color{150, 150, 255, 2500};
    rgba color1{150, 150, 255, 2500};
    rgba color2{255, 150, 150, 2500};
    vector<vec2> positions{
        vec2{0.0, 0.0},
        vec2{SCREEN_WIDTH, 0.0},
    };
    vec2 p{0, 0};

    transition<2> pos_t{2, positions, interpolations::linear};

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
        auto pos = pos_t.update(GetFrameTime());
        // ClearBackground(RAYWHITE);
        DrawCircle(pos[0], pos[1], 50, BLACK);

        // DrawCircle(50, 150, 50, BLACK);
        // DrawCircle(150, 150, 50, BLACK);
        // const int texture_x = SCREEN_WIDTH / 2 - texture.width / 2;
        // const int texture_y = SCREEN_HEIGHT / 2 - texture.height / 2;
        // DrawTexture(texture, texture_x, texture_y, WHITE);
        string str = to_string(pos[0]) + ", " + to_string(pos[1]);
        // string str = to_string(pos_t.t()) + ", " + to_string(pos_t.interpolated_t());
        const char *text = str.c_str();
        const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 20, 1);
        DrawText(text, SCREEN_WIDTH / 2 - text_size.x / 2, 150, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
