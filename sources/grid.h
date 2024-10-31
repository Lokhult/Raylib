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
        int extension = 10;
        auto c = cam.cam();
        auto v = Vector2{0, 0};

        auto minCoords = GetScreenToWorld2D({0, 0}, cam.cam());
        auto maxCoords = GetScreenToWorld2D({static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())}, cam.cam());

        for (int i = 0; i <= extension; i++)
        {
            DrawLineV({minCoords.x + 5, static_cast<float>(i * _spacing)}, {maxCoords.x - 5, static_cast<float>(i * _spacing)}, BLACK);
            DrawLineV({minCoords.x + 5, static_cast<float>(-i * _spacing)}, {maxCoords.x - 5, static_cast<float>(-i * _spacing)}, BLACK);
            DrawLineV({static_cast<float>(i * _spacing), minCoords.y + 5}, {static_cast<float>(i * _spacing), maxCoords.y - 5}, BLACK);
            DrawLineV({static_cast<float>(-i * _spacing), minCoords.y + 5}, {static_cast<float>(-i * _spacing), maxCoords.y - 5}, BLACK);
        }

        DrawCircle(0, 0, 5, BLACK);
    }
};