#include <vector>

#include "raylib.h"
#include "numericArray.h"
#include "transition.h"
#include "RLCamera.h"
#include "grid.h"

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

int main(void)
{
    RLCamera camera{SCREEN_WIDTH, SCREEN_HEIGHT};
    Grid grid;

    Vec2 pos;
    Rgba color;

    Transition<2> transition_pos{pos, 2, {
                                             Vec2{0.0, 0.0},
                                             Vec2{SCREEN_WIDTH, SCREEN_HEIGHT},
                                         },
                                 {Interpolations::linear, Interpolations::linear},
                                 Overflows::repeat};
    Transition<4> transition_colors{color, 4, {Rgba{150, 150, 255, 2500}, Rgba{255, 150, 150, 2500}}, Interpolations::ease_in_ease_out, Overflows::repeat};
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    // Texture2D texture = LoadTexture(ASSETS_PATH"test.png"); // Check README.md for how this works

    while (!WindowShouldClose())
    {
        BeginDrawing();
        camera.begin();
        camera.update(GetFrameTime());
        ClearBackground(BLUE);
        transition_pos.update(GetFrameTime());
        transition_colors.update(GetFrameTime());
        grid.draw(camera);
        DrawCircle(pos[0], pos[1], 50, numeric_array_to_color(color));

        camera.end();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
