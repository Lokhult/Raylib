#include <iostream>
#include "../sources/numeric_array.h"

using namespace std;

int main()
{
    scalar v1{0};
    scalar v2{1};
    scalar v3{2};
    for (double v = 0.0; v <= 1.0; v += 0.1)
    {
        cout << "v: " << v << endl;
        cout << scalar::blend({v1, v2, v3}, v, scalar::blend_mode::closed).to_string() << endl;
    }

    return 0;
}