#pragma once

#include <string>
#include <vector>
#include <regex>
#include <functional>
#include <sstream>

const std::string regexInt = R"(^[0-9]?$)";
const std::string regexDouble = R"(^[0-9](\.[0-9]?)?$)";
const std::string regexString = R"(^.?$)";

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
        // Checks that args matches
        std::string arg;
        std::istringstream argStream(args);
        for (int i = 0; i < _format.size(); i++)
        {
            getline(argStream, arg, ' ');
            auto formatWord = _format[i];
            std::regex rx(formatWord);

            if (!std::regex_search(arg, rx))
            {
                return "";
            }

            if (i > 0)
                argList.push_back(arg);
        }

        return _callback(argList);
    }
};