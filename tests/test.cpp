#include <iostream>
#include "../sources/hsla/numeric_array.h"

using namespace std;

int main()
{
    numeric_array color1{150, 150, 255, 2500};
    cout << color1.to_string() << endl;
    return 0;
}