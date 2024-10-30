#pragma once

#include <array>
#include <functional>
#include <string>

template <int N>
class numeric_array
{
public:
    enum blend_mode
    {
        open,
        closed
    };

protected:
    std::array<double, N> _elements{};

public:
    static numeric_array merge(numeric_array &leftArray, numeric_array &rightArray, const std::function<double(double, double)> transformation);
    static numeric_array blend(std::vector<numeric_array> arrays, numeric_array &weights, blend_mode mode = open);
    static numeric_array blend(std::vector<numeric_array> arrays, double weight, blend_mode mode = closed);

    numeric_array() = default;
    numeric_array(std::array<double, N> elements)
    {
        _elements = elements;
    }

    numeric_array(std::initializer_list<double> init_list)
    {
        for (int i = 0; i < init_list.size(); i++)
        {
            _elements[i] = *(init_list.begin() + i);
        }
    }

    std::array<double, N>::iterator begin();
    std::array<double, N>::iterator end();

    double &operator[](int i);

    const size_t size();

    numeric_array immutable_transform(const std::function<double(double)> &transformation);
    numeric_array mutable_transform(const std::function<double(double)> &transformation);

    numeric_array operator+();
    numeric_array operator+(const double term);
    numeric_array operator+(numeric_array &array);
    void operator+=(const double term);
    void operator+=(numeric_array &array);

    numeric_array operator-();
    numeric_array operator-(const double term);
    numeric_array operator-(numeric_array &array);
    void operator-=(const double term);
    void operator-=(numeric_array &array);

    numeric_array operator*(const double term);
    numeric_array operator*(numeric_array &array);
    void operator*=(const double term);
    void operator*=(numeric_array &array);

    numeric_array operator/(const double term);
    numeric_array operator/(numeric_array &array);
    void operator/=(const double term);
    void operator/=(numeric_array &array);

    std::string to_string();
};

typedef numeric_array<4> vec4;
typedef numeric_array<4> hsla;
typedef numeric_array<4> rgba;
typedef numeric_array<3> vec3;
typedef numeric_array<2> vec2;
typedef numeric_array<1> scalar;

#include <iostream>

template <int N>
numeric_array<N> numeric_array<N>::blend(std::vector<numeric_array> arrays, numeric_array<N> &weights, blend_mode mode)
{
    std::array<double, N> result;

    if (mode == blend_mode::closed)
    {
        arrays.push_back(arrays[0]);
    }

    double delta = 1.0 / (arrays.size() - 1.0);
    for (int i = 0; i < weights.size(); i++)
    {
        double weight = weights[i];
        if (weight < 0)
            weight = 0;
        if (weight > 0.99995)
            weight = 1;

        if (weight == 1)
        {
            result[i] = arrays[arrays.size() - 1][i];
            continue;
        }

        double x = weight / delta;
        int pairIndex = floor(weight / delta);
        double normalizedFactor = (weight / delta) - pairIndex;

        result[i] = (1 - normalizedFactor) * arrays[pairIndex][i] + normalizedFactor * arrays[pairIndex + 1][i];
    }

    return numeric_array{result};
}

template <int N>
numeric_array<N> numeric_array<N>::blend(std::vector<numeric_array> arrays, double weight, blend_mode mode)
{
    numeric_array<N> weights;

    for (int i = 0; i < N; i++)
    {
        weights[i] = weight;
    }

    return blend(arrays, weights, mode);
}

template <int N>
std::array<double, N>::iterator numeric_array<N>::begin()
{
    return _elements.begin();
}

template <int N>
std::array<double, N>::iterator numeric_array<N>::end()
{
    return _elements.end();
}

template <int N>
double &numeric_array<N>::operator[](int i)
{
    return _elements[i];
}

template <int N>
const size_t numeric_array<N>::size()
{
    return _elements.size();
}

template <int N>
numeric_array<N> numeric_array<N>::merge(numeric_array &leftArray, numeric_array &rightArray, const std::function<double(double, double)> transformation)
{
    std::array<double, N> result;

    for (auto i = 0; i < leftArray.size(); i++)
    {
        result[i] = transformation(leftArray._elements[i], rightArray._elements[i]);
    }

    return numeric_array{result};
}

template <int N>
numeric_array<N> numeric_array<N>::immutable_transform(const std::function<double(double)> &transformation)
{
    std::array<double, N> result;

    for (int i = 0; i < N; i++)
    {
        result[i] = transformation(_elements[i]);
    }

    return numeric_array(result);
}

template <int N>
numeric_array<N> numeric_array<N>::mutable_transform(const std::function<double(double)> &transformation)
{
    for (auto &element : _elements)
    {
        element = transformation(element);
    }

    return *this;
}

// Addition
template <int N>
numeric_array<N> numeric_array<N>::operator+()
{
    return *this;
}

template <int N>
numeric_array<N> numeric_array<N>::operator+(const double term)
{
    return immutable_transform([term](double x)
                               { return x + term; });
}

template <int N>
numeric_array<N> numeric_array<N>::operator+(numeric_array &array)
{
    return merge(*this, array, [](double x, double y)
                 { return x + y; });
}

template <int N>
void numeric_array<N>::operator+=(const double term)
{
    *this = *this + term;
}

template <int N>
void numeric_array<N>::operator+=(numeric_array &array)
{
    *this = *this + array;
}

// Subtraction
template <int N>
numeric_array<N> numeric_array<N>::operator-()
{
    return immutable_transform([](double x)
                               { return -x; });
}

template <int N>
numeric_array<N> numeric_array<N>::operator-(const double term)
{
    return immutable_transform([term](double x)
                               { return x - term; });
}

template <int N>
numeric_array<N> numeric_array<N>::operator-(numeric_array &array)
{
    return merge(*this, array, [](double x, double y)
                 { return x - y; });
}

template <int N>
void numeric_array<N>::operator-=(const double term)
{
    *this = *this - term;
}

template <int N>
void numeric_array<N>::operator-=(numeric_array &array)
{
    *this = *this - array;
}

// Multiplication
template <int N>
numeric_array<N> numeric_array<N>::operator*(const double term)
{
    return immutable_transform([term](double x)
                               { return x * term; });
}

template <int N>
numeric_array<N> numeric_array<N>::operator*(numeric_array &array)
{
    return merge(*this, array, [](double x, double y)
                 { return x * y; });
}

template <int N>
void numeric_array<N>::operator*=(const double term)
{
    *this = *this * term;
}

template <int N>
void numeric_array<N>::operator*=(numeric_array &array)
{
    *this = *this * array;
}

// Division
template <int N>
numeric_array<N> numeric_array<N>::operator/(const double term)
{
    return immutable_transform([term](double x)
                               { return x / term; });
}

template <int N>
numeric_array<N> numeric_array<N>::operator/(numeric_array &array)
{
    return merge(*this, array, [](double x, double y)
                 { return x / y; });
}

template <int N>
void numeric_array<N>::operator/=(const double term)
{
    *this = *this / term;
}

template <int N>
void numeric_array<N>::operator/=(numeric_array &array)
{
    *this = *this / array;
}

template <int N>
std::string numeric_array<N>::to_string()
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