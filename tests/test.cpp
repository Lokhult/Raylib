#include <iostream>
#include "../sources/numeric_array/numeric_array.h"

using namespace std;

int main()
{
    auto v = numeric_array::linear_range(0, 10, 5);
    cout << v.to_string() << endl;
    cout << v[0] << v[1] << v[2] << v[3] << endl;
    cout << v.size() << endl;
    return 0;
}