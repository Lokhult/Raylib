#pragma once

#include <string>
#include <vector>
#include <regex>
#include <functional>
#include <sstream>
#include <iostream>

namespace Types
{
    const std::string Int = R"(^-?\d+$)";
    const std::string Double = R"(-?\d*(\.\d*)?$)";
    const std::string String = R"(^.*$)";
}

class ConsoleCommand
{
    typedef std::function<std::string(std::vector<std::string>)> callbackType;

private:
    callbackType _callback;
    std::vector<std::string> _format;

public:
    ConsoleCommand(std::vector<std::string> format, callbackType callback) : _callback(callback), _format(format) {}
    std::string operator()(std::string args)
    {
        std::vector<std::string> argList;
        std::string arg;
        std::istringstream argStream(args);
        while (getline(argStream, arg, ' '))
        {
            argList.push_back(arg);
        }

        // Checks that args matches
        if (argList.size() != _format.size())
            return "";

        for (int i = 0; i < _format.size(); i++)
        {
            std::regex rx(_format[i]);

            std::cout << "(format: " << _format[i] << ", arg: " << argList[i] << ") ";

            if (!std::regex_search(argList[i], rx))
            {
                return "";
            }

            if (i > 0)
                argList.push_back(arg);
        }

        return _callback(std::vector<std::string>(argList.begin() + 1, argList.end()));
    }
};