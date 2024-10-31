#include <vector>

#include "raylib.h"
#include "numericArray.h"
#include "transition.h"
#include "RLCamera.h"

using namespace std;

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "Window title"

Color numeric_array_to_color(Rgba &array)
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

Vec2 denormalized_coords(Vec2 coords)
{
    return Vec2{coords[0] * SCREEN_WIDTH, coords[1] * SCREEN_HEIGHT};
}

void drawGrid(float spacing, int extension)
{
    float cutoff = 10e6;
    for (int i = 0; i <= extension; i++)
    {
        DrawLineV({-cutoff, i * spacing}, {cutoff, i * spacing}, BLACK);
        DrawLineV({-cutoff, -i * spacing}, {cutoff, -i * spacing}, BLACK);
        DrawLineV({i * spacing, -cutoff}, {i * spacing, cutoff}, BLACK);
        DrawLineV({-i * spacing, -cutoff}, {-i * spacing, cutoff}, BLACK);
    }
    DrawCircle(0, 0, 5, BLACK);
}

int main(void)
{
    RLCamera camera{SCREEN_WIDTH, SCREEN_HEIGHT};
    Rgba color{150, 150, 255, 2500};
    Rgba color1{150, 150, 255, 2500};
    Rgba color2{255, 150, 150, 2500};
    vector<Vec2> positions{
        Vec2{0.0, 0.0},
        Vec2{SCREEN_WIDTH, SCREEN_HEIGHT},
    };
    vector<Rgba> colors{
        Rgba{150, 150, 255, 2500},
        Rgba{255, 150, 150, 2500}};

    Transition<2> transition_pos{2, positions, {Interpolations::linear, Interpolations::linear}, Overflows::repeat};
    Transition<4> transition_colors{3, colors, Interpolations::ease_in_ease_out, Overflows::repeat};
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    // Texture2D texture = LoadTexture(ASSETS_PATH"test.png"); // Check README.md for how this works

    while (!WindowShouldClose())
    {
        BeginDrawing();
        camera.begin();
        camera.update(GetFrameTime());
        auto delta = GetTime() / 10;
        auto x = color1 * (1 - delta);
        auto y = color2 * delta;
        ClearBackground(numeric_array_to_color(color1));
        auto pos = transition_pos.update(GetFrameTime());
        auto color = transition_colors.update(GetFrameTime());
        // ClearBackground(RAYWHITE);
        drawGrid(50, 10);
        DrawCircle(pos[0], pos[1], 50, numeric_array_to_color(color));

        // DrawCircle(50, 150, 50, BLACK);
        // DrawCircle(150, 150, 50, BLACK);
        // const int texture_x = SCREEN_WIDTH / 2 - texture.width / 2;
        // const int texture_y = SCREEN_HEIGHT / 2 - texture.height / 2;
        // DrawTexture(texture, texture_x, texture_y, WHITE);

        // string str = to_string(pos[0]) + ", " + to_string(pos[1]);
        // string str = to_string(pos_t.t()) + ", " + to_string(pos_t.interpolated_t());
        // const char *text = str.c_str();
        // const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 20, 1);
        // DrawText(text, SCREEN_WIDTH / 2 - text_size.x / 2, 150, 20, BLACK);
        camera.end();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
