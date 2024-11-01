#pragma once

#include <vector>
#include <cmath>
#include "numericArrays.h"
#include <raylib.h>

class Shape : public NumericArrays<2>
{
protected:
public:
    static Shape Rectangle(Vec2 corner1, Vec2 corner2)
    {
        return Shape({corner1,
                      {corner2[0], corner1[1]},
                      corner2,
                      {corner1[0], corner2[1]}});
    }

    Shape(std::vector<Vec2> elements) : NumericArrays<2>(elements) {}

    void subdivideUntil(int targetelements)
    {
        int partitions = ceil(targetelements / _elements.size());
        subdivide(partitions);
    }

    void draw(int thickness, bool markelements = false)
    {
        for (int i = 0; i < _elements.size(); i++)
        {
            DrawLineEx(
                {.x = static_cast<float>(_elements[i][0]),
                 .y = static_cast<float>(_elements[i][1])},
                {.x = static_cast<float>(_elements[(i + 1) % _elements.size()][0]),
                 .y = static_cast<float>(_elements[(i + 1) % _elements.size()][1])},
                thickness,
                BLACK);
            if (markelements)
            {
                DrawCircle(_elements[i][0], _elements[i][1], 2, BLACK);
            }
        }
    }
};