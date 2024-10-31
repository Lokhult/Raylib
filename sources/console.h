#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <functional>
#include <regex>
#include <raylib.h>

const float margin = 5;
const float padding = 5;
const float fontSize = 16;
const Color consoleBackground{255, 255, 255, 150};
const int borderWidth = 2;

class ConsoleCommand
{
    typedef std::function<std::string(std::string)> callbackType;

private:
    callbackType _callback;
    std::string _format;

public:
    ConsoleCommand(std::string format, callbackType callback) : _callback(callback), _format(format) {}
    std::string operator()(std::string args)
    {
        // Check if args fit command
        std::regex rx(_format);
        if (std::regex_search(args, rx))
        {
            return _callback(args);
        }
        return "";
    }
};

class Console
{
private:
    Rectangle _bounds{
        .x = margin,
        .y = margin,
        .width = static_cast<float>(GetScreenWidth()) - 2 * margin,
        .height = fontSize + 2 * padding};
    std::string _content;
    std::string _output;
    std::vector<ConsoleCommand> _commands;
    bool _focused = false;

public:
    void addCommand(ConsoleCommand command)
    {
        _commands.push_back(command);
    }

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

    void submit()
    {
        bool foundCommand = false;
        for (auto command : _commands)
        {
            auto result = command(_content);
            if (result != "")
            {
                _output += result + '\n';
                foundCommand = true;
                break;
            }
        }
        
        if (!foundCommand)
        {
            _output += "No command was found\n";
        }
        _content = "";
    }
};
