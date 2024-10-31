#pragma once

#include <string>
#include <raylib.h>

const float margin = 5;
const float padding = 5;
const float fontSize = 16;
const Color consoleBackground{255, 255, 255, 150};
const int borderWidth = 2;

class Console
{
private:
    Rectangle _bounds{
        .x = margin,
        .y = margin,
        .width = static_cast<float>(GetScreenWidth()) - 2 * margin,
        .height = fontSize + 2 * padding};
    std::string _content = "Console Line";
    bool _focused = false;

public:
    void draw()
    {
        update();
        DrawRectangleRec(_bounds, consoleBackground);
        if (_focused)
        {
            DrawRectangleLinesEx(_bounds, borderWidth, Color{255, 255, 255, 255});
        }
        DrawText(_content.c_str(), _bounds.x + padding, _bounds.y + padding, fontSize, BLACK);
    }

    void update()
    {
        if (IsMouseButtonPressed(0) && CheckCollisionPointRec(GetMousePosition(), _bounds))
        {
            _focused = true;
        }
        if (IsMouseButtonReleased(0) && !CheckCollisionPointRec(GetMousePosition(), _bounds))
        {
            _focused = false;
        }
    }
};
