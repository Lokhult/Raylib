#pragma once

#include <string>
#include <vector>

#include "consoleCommand.h"

class Console
{
protected:
    std::string _content;
    std::string _output;
    std::vector<ConsoleCommand> _commands;

public:
    void addCommand(ConsoleCommand command)
    {
        _commands.push_back(command);
    }

    std::string submitCommand(std::string args)
    {
        _content = args;
        return submit();
    }

    std::string submit()
    {
        std::string returnValue = "";
        for (auto command : _commands)
        {
            returnValue = command(_content);

            if (returnValue != "")
                break;
        }

        if (returnValue == "")
        {
            returnValue = "No command was found";
        }

        _output = returnValue + "\n" + _output;

        _content = "";

        return returnValue;
    }
};
