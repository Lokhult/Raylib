#include <iostream>
#include "../sources/console.h"
#include "../sources/functions.h"

using namespace std;

int main()
{
    auto vf = VectorFunction(1, 1, [](vector<double> t) -> vector<double>
                             { return {t[0] + 1}; });

    auto vf2 = VectorFunction(1, 1, [](vector<double> t) -> vector<double>
                              { return {t[0] + 1}; }, &vf);

    cout << "vf({0}) = " << vf2({0})[0] << endl;
    return 0;
}