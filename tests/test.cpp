#include <iostream>
#include "../sources/numeric_array.h"

using namespace std;

int main()
{
    rgba v{150, 150, 255, 2500};
    cout << v[0];
    cout << v.to_string() << endl;
    cout << v[0] << v[1] << v[2] << v[3] << endl;
    cout << v.size() << endl;
    return 0;
}