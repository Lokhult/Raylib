#pragma once

#include <raylib.h>
#include "RLCamera.h"

class Grid
{
private:
    double _spacing = 10;

public:
    void draw(RLCamera cam)
    {
        float cutoff = 10e6;
        int extension = 10;
        auto c = cam.cam();
        auto v = Vector2{0, 0};

        auto p = GetScreenToWorld2D(v, c);

        for (int i = 0; i <= extension; i++)
        {
            // horizontals
            DrawLineV({-cutoff, static_cast<float>(i * _spacing)}, {cutoff, static_cast<float>(i * _spacing)}, BLACK);
            DrawLineV({-cutoff, static_cast<float>(-i * _spacing)}, {cutoff, static_cast<float>(-i * _spacing)}, BLACK);
            DrawLineV({i * static_cast<float>(_spacing, -cutoff)}, {static_cast<float>(i * _spacing), cutoff}, BLACK);
            DrawLineV({static_cast<float>(-i * _spacing), -cutoff}, {static_cast<float>(-i * _spacing), cutoff}, BLACK);
        }

        DrawCircle(0, 0, 5, BLACK);
    }
};