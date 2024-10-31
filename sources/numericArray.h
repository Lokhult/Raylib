#pragma once

#include <array>
#include <functional>
#include <string>

template <int N>
class NumericArray
{
public:
    enum BlendMode
    {
        open,
        closed
    };

protected:
    std::array<double, N> _elements{};

public:
    static NumericArray merge(NumericArray &leftArray, NumericArray &rightArray, const std::function<double(double, double)> transformation);
    static NumericArray blend(std::vector<NumericArray> arrays, NumericArray &weights, BlendMode mode = open);
    static NumericArray blend(std::vector<NumericArray> arrays, double weight, BlendMode mode = open);

    NumericArray() = default;
    NumericArray(std::array<double, N> elements)
    {
        _elements = elements;
    }

    NumericArray(std::initializer_list<double> init_list)
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

    NumericArray immutableTransform(const std::function<double(double)> &transformation);
    NumericArray mutableTransform(const std::function<double(double)> &transformation);

    NumericArray operator+();
    NumericArray operator+(const double term);
    NumericArray operator+(NumericArray &array);
    void operator+=(const double term);
    void operator+=(NumericArray &array);

    NumericArray operator-();
    NumericArray operator-(const double term);
    NumericArray operator-(NumericArray &array);
    void operator-=(const double term);
    void operator-=(NumericArray &array);

    NumericArray operator*(const double term);
    NumericArray operator*(NumericArray &array);
    void operator*=(const double term);
    void operator*=(NumericArray &array);

    NumericArray operator/(const double term);
    NumericArray operator/(NumericArray &array);
    void operator/=(const double term);
    void operator/=(NumericArray &array);

    std::string toString();
};

typedef NumericArray<4> Vec4;
typedef NumericArray<4> Hsla;
typedef NumericArray<4> Rgba;
typedef NumericArray<3> Vec3;
typedef NumericArray<2> Vec2;
typedef NumericArray<1> Scalar;

template <int N>
NumericArray<N> NumericArray<N>::blend(std::vector<NumericArray> arrays, NumericArray<N> &weights, BlendMode mode)
{
    std::array<double, N> result;

    if (mode == BlendMode::closed)
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

    return NumericArray{result};
}

template <int N>
NumericArray<N> NumericArray<N>::blend(std::vector<NumericArray> arrays, double weight, BlendMode mode)
{
    NumericArray<N> weights;

    for (int i = 0; i < N; i++)
    {
        weights[i] = weight;
    }

    return blend(arrays, weights, mode);
}

template <int N>
std::array<double, N>::iterator NumericArray<N>::begin()
{
    return _elements.begin();
}

template <int N>
std::array<double, N>::iterator NumericArray<N>::end()
{
    return _elements.end();
}

template <int N>
double &NumericArray<N>::operator[](int i)
{
    return _elements[i];
}

template <int N>
const size_t NumericArray<N>::size()
{
    return _elements.size();
}

template <int N>
NumericArray<N> NumericArray<N>::merge(NumericArray &leftArray, NumericArray &rightArray, const std::function<double(double, double)> transformation)
{
    std::array<double, N> result;

    for (auto i = 0; i < leftArray.size(); i++)
    {
        result[i] = transformation(leftArray._elements[i], rightArray._elements[i]);
    }

    return NumericArray{result};
}

template <int N>
NumericArray<N> NumericArray<N>::immutableTransform(const std::function<double(double)> &transformation)
{
    std::array<double, N> result;

    for (int i = 0; i < N; i++)
    {
        result[i] = transformation(_elements[i]);
    }

    return NumericArray(result);
}

template <int N>
NumericArray<N> NumericArray<N>::mutableTransform(const std::function<double(double)> &transformation)
{
    for (auto &element : _elements)
    {
        element = transformation(element);
    }

    return *this;
}

// Addition
template <int N>
NumericArray<N> NumericArray<N>::operator+()
{
    return *this;
}

template <int N>
NumericArray<N> NumericArray<N>::operator+(const double term)
{
    return immutableTransform([term](double x)
                              { return x + term; });
}

template <int N>
NumericArray<N> NumericArray<N>::operator+(NumericArray &array)
{
    return merge(*this, array, [](double x, double y)
                 { return x + y; });
}

template <int N>
void NumericArray<N>::operator+=(const double term)
{
    *this = *this + term;
}

template <int N>
void NumericArray<N>::operator+=(NumericArray &array)
{
    *this = *this + array;
}

// Subtraction
template <int N>
NumericArray<N> NumericArray<N>::operator-()
{
    return immutableTransform([](double x)
                              { return -x; });
}

template <int N>
NumericArray<N> NumericArray<N>::operator-(const double term)
{
    return immutableTransform([term](double x)
                              { return x - term; });
}

template <int N>
NumericArray<N> NumericArray<N>::operator-(NumericArray &array)
{
    return merge(*this, array, [](double x, double y)
                 { return x - y; });
}

template <int N>
void NumericArray<N>::operator-=(const double term)
{
    *this = *this - term;
}

template <int N>
void NumericArray<N>::operator-=(NumericArray &array)
{
    *this = *this - array;
}

// Multiplication
template <int N>
NumericArray<N> NumericArray<N>::operator*(const double term)
{
    return immutableTransform([term](double x)
                              { return x * term; });
}

template <int N>
NumericArray<N> NumericArray<N>::operator*(NumericArray &array)
{
    return merge(*this, array, [](double x, double y)
                 { return x * y; });
}

template <int N>
void NumericArray<N>::operator*=(const double term)
{
    *this = *this * term;
}

template <int N>
void NumericArray<N>::operator*=(NumericArray &array)
{
    *this = *this * array;
}

// Division
template <int N>
NumericArray<N> NumericArray<N>::operator/(const double term)
{
    return immutableTransform([term](double x)
                              { return x / term; });
}

template <int N>
NumericArray<N> NumericArray<N>::operator/(NumericArray &array)
{
    return merge(*this, array, [](double x, double y)
                 { return x / y; });
}

template <int N>
void NumericArray<N>::operator/=(const double term)
{
    *this = *this / term;
}

template <int N>
void NumericArray<N>::operator/=(NumericArray &array)
{
    *this = *this / array;
}

template <int N>
std::string NumericArray<N>::toString()
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