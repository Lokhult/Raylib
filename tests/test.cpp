#include <iostream>
#include "../sources/numericArray.h"

using namespace std;

int main()
{
    Scalar v1{0};
    Scalar v2{1};
    Scalar v3{2};
    for (double v = 0.0; v <= 1.0; v += 0.1)
    {
        cout << "v: " << v << endl;
        cout << Scalar::blend({v1, v2, v3}, v, Scalar::BlendMode::closed).toString() << endl;
    }

    return 0;
}