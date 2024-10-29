#include <iostream>
#include "../sources/numeric_array/numeric_array.h"

using namespace std;

int main()
{
    numeric_array color1{150, 150, 255, 2500};
    numeric_array color2{150, 150, 255, 2500};
    color1 *= 2;
    color1 += color2;
    cout << color1.to_string() << endl;
    return 0;
}