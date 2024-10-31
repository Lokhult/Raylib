#include <vector>

#include "raylib.h"
#include "numericArray.h"
#include "transition.h"
#include "RLCamera.h"
#include "grid.h"
#include "transitionEngine.h"
#include "console.h"

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
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    RLCamera camera{SCREEN_WIDTH, SCREEN_HEIGHT};
    Grid grid;
    Console console;
    TransitionEngine<2> transitionEngine2;
    TransitionEngine<4> transitionEngine4;

    Vec2 pos;
    Rgba color;

    Transition<2> transition_pos{pos, 2, {
                                             Vec2{0.0, 0.0},
                                             Vec2{SCREEN_WIDTH, SCREEN_HEIGHT},
                                         },
                                 {Interpolations::linear, Interpolations::linear},
                                 Overflows::repeat};
    Transition<4> transition_colors{color, 4, {Rgba{150, 150, 255, 2500}, Rgba{255, 150, 150, 2500}}, Interpolations::ease_in_ease_out, Overflows::repeat};
    transitionEngine2.addTransition(transition_pos);
    transitionEngine4.addTransition(transition_colors);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        transitionEngine2.update(GetFrameTime());
        transitionEngine4.update(GetFrameTime());

        BeginDrawing();
        {
            camera.begin();
            {
                camera.update(GetFrameTime());
                ClearBackground(BLUE);
                grid.draw(camera);
                DrawCircle(pos[0], pos[1], 50, numeric_array_to_color(color));
            }
            camera.end();

            console.draw();
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
