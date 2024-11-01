#pragma once

#include <vector>
#include "numericArray.h"
#include <numeric>
#include <algorithm>

template <int N>
class NumericArrays
{
    typedef NumericArray<N> ArrayType;
    typedef std::vector<NumericArray<N>> CollectionType;
    typedef std::function<NumericArray<N>(NumericArray<N>)> ArrayToArray;

protected:
    CollectionType _elements;

public:
    NumericArrays(CollectionType arrays) : _elements(arrays) {}

    ArrayType &immutableTransform(const ArrayToArray &transformation)
    {
        NumericArrays<N> result;

        for (const auto &arr : _elements)
        {
            result.push_back(transformation(arr));
        }

        return result;
    }

    void mutableTransform(const ArrayToArray &transformation)
    {
        for (auto &arr : _elements)
        {
            arr.mutableTransform(transformation(arr));
        }

        return *this;
    }

    void subdivide(int partitions)
    {
        std::vector<Vec2> newelements;

        for (int i = 0; i < _elements.size(); i++)
        {
            NumericArrays<2> vertexPair{{_elements[i],
                                         _elements[(i + 1) % _elements.size()]}};

            double delta = 1.0 / partitions;

            for (int j = 0; j < partitions; j++)
            {
                double t = j * delta;
                newelements.push_back(vertexPair.blend(t));
            }
        }

        _elements = newelements;
    }

    ArrayType blend(ArrayType &weights, NumericArrayEnums::BlendMode mode = NumericArrayEnums::BlendMode::open)
    {
        std::array<double, N> result;

        if (mode == NumericArrayEnums::BlendMode::closed)
        {
            _elements.push_back(_elements[0]);
        }

        double delta = 1.0 / (_elements.size() - 1.0);
        for (int i = 0; i < weights.size(); i++)
        {
            double weight = weights[i];
            if (weight < 0)
                weight = 0;
            if (weight > 0.99995)
                weight = 1;

            if (weight == 1)
            {
                result[i] = _elements[_elements.size() - 1][i];
                continue;
            }

            double x = weight / delta;
            int pairIndex = floor(weight / delta);
            double normalizedFactor = (weight / delta) - pairIndex;

            result[i] = (1 - normalizedFactor) * _elements[pairIndex][i] + normalizedFactor * _elements[pairIndex + 1][i];
        }

        return ArrayType{result};
    }

    NumericArray<N> blend(double weight, NumericArrayEnums::BlendMode mode = NumericArrayEnums::BlendMode::open)
    {
        NumericArray<N> weights;
        std::fill(weights.begin(), weights.end(), weight);
        return blend(weights, mode);
    }

    NumericArray<N> average()
    {
        return std::accumulate(_elements.begin(), _elements.end()) / _elements.size();
    }

    double &operator[](int i)
    {
        auto mod = i % _elements.size();
        if (mod < 0)
            mod += _elements.size();
        return _elements[mod];
    }

    const size_t size()
    {
        return _elements.size();
    }

    // Addition
    NumericArrays<N> &operator+()
    {
        return *this;
    }

    NumericArrays<N> operator+(const double term)
    {
        return immutableTransform([term](double x)
                                  { return x + term; });
    }

    NumericArrays<N> operator+(NumericArrays &array)
    {
        return merge(*this, array, [](double x, double y)
                     { return x + y; });
    }

    void operator+=(const double term)
    {
        *this = *this + term;
    }

    void operator+=(NumericArrays &array)
    {
        *this = *this + array;
    }

    // Subtraction
    NumericArrays<N> operator-()
    {
        return immutableTransform([](double x)
                                  { return -x; });
    }

    NumericArrays<N> operator-(const double term)
    {
        return immutableTransform([term](double x)
                                  { return x - term; });
    }

    NumericArrays<N> operator-(NumericArrays &array)
    {
        return merge(*this, array, [](double x, double y)
                     { return x - y; });
    }

    void operator-=(const double term)
    {
        *this = *this - term;
    }

    void operator-=(NumericArrays &array)
    {
        *this = *this - array;
    }

    // Multiplication
    NumericArrays<N> operator*(const double term)
    {
        return immutableTransform([term](double x)
                                  { return x * term; });
    }

    NumericArrays<N> operator*(NumericArrays &array)
    {
        return merge(*this, array, [](double x, double y)
                     { return x * y; });
    }

    void operator*=(const double term)
    {
        *this = *this * term;
    }

    void operator*=(NumericArrays &array)
    {
        *this = *this * array;
    }

    // Division
    NumericArrays<N> operator/(const double term)
    {
        return immutableTransform([term](double x)
                                  { return x / term; });
    }

    NumericArrays<N> operator/(NumericArrays &array)
    {
        return merge(*this, array, [](double x, double y)
                     { return x / y; });
    }

    void operator/=(const double term)
    {
        *this = *this / term;
    }

    void operator/=(NumericArrays &array)
    {
        *this = *this / array;
    }
};