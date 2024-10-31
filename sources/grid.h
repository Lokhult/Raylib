#pragma once

#include <array>
#include <ranges>
#include <algorithm>
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

        auto topLeft = GetScreenToWorld2D({0, 0}, cam.cam());
        auto topRight = GetScreenToWorld2D({static_cast<float>(GetScreenWidth()), 0}, cam.cam());
        auto bottomRight = GetScreenToWorld2D({static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())}, cam.cam());
        auto bottomLeft = GetScreenToWorld2D({0, static_cast<float>(GetScreenHeight())}, cam.cam());
        std::array<float, 4> xCoords{topLeft.x, topRight.x, bottomRight.x, bottomLeft.x};
        std::array<float, 4> yCoords{topLeft.y, topRight.y, bottomRight.y, bottomLeft.y};
        std::ranges::sort(xCoords);
        std::ranges::sort(yCoords);
        Vector2 minCoords{xCoords[0], yCoords[0]};
        Vector2 maxCoords{xCoords[3], yCoords[3]};

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