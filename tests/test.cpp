#include <iostream>
#include "../sources/console.h"

using namespace std;

int main()
{
    Console console;
    auto callback = [](vector<string> args)
    {
        int arg1 = stoi(args[0]);
        double arg2 = stod(args[1]);
        return "Exit successful with int " + to_string(arg1) + " and double " + to_string(arg2);
    };

    ConsoleCommand consoleCommand{
        {"exit", regexInt, regexDouble},
        callback};

    console.addCommand(consoleCommand);

    string consoleContent;
    while (getline(cin, consoleContent))
    {
        cout << console.submitCommand(consoleContent) << endl;
    }

    return 0;
}