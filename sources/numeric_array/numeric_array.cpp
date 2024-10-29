#include <vector>
#include <functional>
#include <cmath>
#include "numeric_array.h"

using namespace std;

numeric_array numeric_array::linear_range(double start, double end, double count)
{
    std::vector<double> result;
    double range = end - start;
    double delta = range / (count - 1);

    for (double i = start; i < count; i++)
    {
        result.push_back(start + delta * i);
    }

    return numeric_array(result);
}

numeric_array numeric_array::blend(vector<numeric_array> arrays, numeric_array &weights, blend_mode mode = linear)
{
    vector<double> result;

    const double factorDelta = 1.0 / (arrays.size() - 1 + mode);

    for (int i = 0; i < weights.size(); i++)
    {
        weights[i] -= 1; //-0.1E-10;
        const int pairIndex = floor(weights[i] / factorDelta);
        const double normalizedFactor = (weights[i] / factorDelta) - pairIndex;

        result.push_back(
            (1.0 - normalizedFactor) * arrays[pairIndex % arrays.size()][i] +
            normalizedFactor * arrays[(pairIndex + 1) % arrays.size()][i]);
    }

    return numeric_array{result};
}

std::vector<double>::iterator numeric_array::begin()
{
    return _elements.begin();
}

std::vector<double>::iterator numeric_array::end()
{
    return _elements.end();
}

double &numeric_array::operator[](int i)
{
    return _elements[i];
}

const size_t numeric_array::size()
{
    return _elements.size();
}

numeric_array numeric_array::merge(numeric_array &leftArray, numeric_array &rightArray, const std::function<double(double, double)> transformation)
{
    vector<double> result;

    for (auto i = 0; i < leftArray.size(); i++)
    {
        result.push_back(transformation(leftArray._elements[i], rightArray._elements[i]));
    }

    return numeric_array{result};
}

numeric_array numeric_array::immutable_transform(const std::function<double(double)> &transformation)
{
    vector<double> result;

    for (auto v : _elements)
    {
        result.push_back(transformation(v));
    }

    return numeric_array(result);
}

numeric_array numeric_array::mutable_transform(const function<double(double)> &transformation)
{
    for (auto &element : _elements)
    {
        element = transformation(element);
    }

    return *this;
}

// Addition
numeric_array numeric_array::operator+()
{
    return *this;
}

numeric_array numeric_array::operator+(const double term)
{
    return immutable_transform([term](double x)
                               { return x + term; });
}

numeric_array numeric_array::operator+(numeric_array &array)
{
    return merge(*this, array, [](double x, double y)
                 { return x + y; });
}

void numeric_array::operator+=(const double term)
{
    *this = *this + term;
}

void numeric_array::operator+=(numeric_array &array)
{
    *this = *this + array;
}

// Subtraction
numeric_array numeric_array::operator-()
{
    return immutable_transform([](double x)
                               { return -x; });
}

numeric_array numeric_array::operator-(const double term)
{
    return immutable_transform([term](double x)
                               { return x - term; });
}

numeric_array numeric_array::operator-(numeric_array &array)
{
    return merge(*this, array, [](double x, double y)
                 { return x - y; });
}

void numeric_array::operator-=(const double term)
{
    *this = *this - term;
}

void numeric_array::operator-=(numeric_array &array)
{
    *this = *this - array;
}

// Multiplication
numeric_array numeric_array::operator*(const double term)
{
    return immutable_transform([term](double x)
                               { return x * term; });
}

numeric_array numeric_array::operator*(numeric_array &array)
{
    return merge(*this, array, [](double x, double y)
                 { return x * y; });
}

void numeric_array::operator*=(const double term)
{
    *this = *this * term;
}

void numeric_array::operator*=(numeric_array &array)
{
    *this = *this * array;
}

// Division
numeric_array numeric_array::operator/(const double term)
{
    return immutable_transform([term](double x)
                               { return x / term; });
}

numeric_array numeric_array::operator/(numeric_array &array)
{
    return merge(*this, array, [](double x, double y)
                 { return x / y; });
}

void numeric_array::operator/=(const double term)
{
    *this = *this / term;
}

void numeric_array::operator/=(numeric_array &array)
{
    *this = *this / array;
}

string numeric_array::to_string()
{
    std::string str = "(";

    for (int i = 0; i < _elements.size(); i++)
    {
        str += std::to_string(_elements[i]);
        if (i < _elements.size() - 1)
            str += ", ";
    }

    str += ")";

    return str;
}