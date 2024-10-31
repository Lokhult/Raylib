#include <iostream>
#include "../sources/console.h"

using namespace std;

int main()
{
    Console console;
    console.addCommand({{"circle", Types::Double},
                        [](vector<string> args)
                        {
                            return "Circle created: " + to_string(stod(args[0]));
                        }});

    string consoleContent;
    while (getline(cin, consoleContent))
    {
        cout << console.submitCommand(consoleContent) << endl;
    }

    return 0;
}