#pragma once

#include <vector>
#include "numericArray.h"
#include <raylib.h>

class RaylibShape
{
protected:
    std::vector<Vec2> _vertices;

public:
    static RaylibShape Rectangle(Vec2 corner1, Vec2 corner2)
    {
        return RaylibShape({corner1,
                            {corner2[0], corner1[1]},
                            corner2,
                            {corner1[0], corner2[1]}});
    }

    RaylibShape(std::vector<Vec2> vertices) : _vertices(vertices) {}

    void draw()
    {
        for (int i = 0; i < _vertices.size(); i++)
        {
            DrawLineEx(
                {.x = static_cast<float>(_vertices[i][0]),
                 .y = static_cast<float>(_vertices[i][1])},
                {.x = static_cast<float>(_vertices[(i + 1) % _vertices.size()][0]),
                 .y = static_cast<float>(_vertices[(i + 1) % _vertices.size()][1])},
                5,
                BLACK);
        }
    }
};