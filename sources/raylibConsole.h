#pragma once

#include <raylib.h>
#include "console.h"

const float margin = 5;
const float padding = 5;
const float fontSize = 16;
const Color consoleBackground{255, 255, 255, 150};
const int borderWidth = 2;

class RaylibConsole : public Console
{
private:
    Rectangle _bounds;
    bool _focused = false;

public:
    RaylibConsole(int screenWidth, int screenHeight) : _bounds({.x = margin,
                                                                .y = margin,
                                                                .width = static_cast<float>(screenWidth) - 2 * margin,
                                                                .height = fontSize + 2 * padding}) {}
    void draw()
    {
        update();
        DrawRectangleRec(_bounds, consoleBackground);
        if (_focused)
        {
            DrawRectangleLinesEx(_bounds, borderWidth, Color{255, 255, 255, 255});
        }
        DrawText(_content.c_str(), _bounds.x + padding, _bounds.y + padding, fontSize, BLACK);
        DrawText(_output.c_str(), _bounds.x + padding, _bounds.y + _bounds.height + padding, fontSize, BLACK);
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

        if (_focused)
        {
            int charKey;
            while ((charKey = GetCharPressed()) != 0)
            {
                _content += static_cast<char>(charKey);
            }

            int key;
            while ((key = GetKeyPressed()) != 0)
            {
                switch (key)
                {
                case KEY_BACKSPACE:
                    _content = _content.substr(0, _content.size() - 1);
                    break;
                case KEY_ENTER:
                    submit();
                    break;
                }
            }
        }
    }
};