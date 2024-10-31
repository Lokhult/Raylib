#include <string>
#include <vector>

#include "raylib.h"
#include "numericArray.h"
#include "transition.h"
#include "RLCamera.h"
#include "grid.h"
#include "transitionEngine.h"
#include "raylibConsole.h"
#include "consoleCommand.h"
#include "raylibShape.h"

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

    vector<NumericArray<3>> circles;

    RLCamera camera{SCREEN_WIDTH, SCREEN_HEIGHT};
    Grid grid;
    RaylibConsole console{SCREEN_WIDTH, SCREEN_HEIGHT};

    console.addCommand({{"circle", Types::Double, Types::Double, Types::Double},
                        [&circles](vector<string> args)
                        {
                            circles.push_back({stod(args[0]), stod(args[1]), stod(args[2])});
                            return "Circle created";
                        }});

    auto rect = RaylibShape::Rectangle({25, 25}, {75, 75});
    rect.subdivide(2);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        BeginDrawing();
        {
            camera.begin();
            {
                camera.update(GetFrameTime());
                ClearBackground(BLUE);
                rect.draw();
                grid.draw(camera);
                for (auto circle : circles)
                {
                    DrawCircle(circle[0], circle[1], circle[2], GREEN);
                }
            }
            camera.end();

            console.draw();
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
