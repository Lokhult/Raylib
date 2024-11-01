#pragma once

#include <array>
#include <functional>
#include <string>

namespace NumericArrayEnums
{
    enum BlendMode
    {
        open,
        closed
    };
}

template <typename T>
concept IsArithmetic = requires(T t, double d) {
    { +t } -> std::convertible_to<T>;
    { t + t } -> std::convertible_to<T>;
    { t ++= t } -> std::convertible_to<T>;
    { -t } -> std::convertible_to<T>;
    { t - t } -> std::convertible_to<T>;
    { t -= t } -> std::convertible_to<T>;
    { t * t } -> std::convertible_to<T>;
    { t *= t } -> std::convertible_to<T>;
    { t / t } -> std::convertible_to<T>;
    { t /= t } -> std::convertible_to<T>;
};

template <size_t N, IsArithmetic V = double>
class NumericArray
{
public:
protected:
    std::array<V, N> _elements{};

public:
    static NumericArray merge(NumericArray &leftArray, NumericArray &rightArray, const std::function<double(double, double)> transformation)
    {
        std::array<double, N> result;

        for (auto i = 0; i < leftArray.size(); i++)
        {
            result[i] = transformation(leftArray._elements[i], rightArray._elements[i]);
        }

        return NumericArray{result};
    }

    static NumericArray average(std::vector<NumericArray> arrays)
    {
        NumericArray<N> result;
        for (auto array : arrays)
        {
            result += array;
        }
        result /= arrays.size();
        return result;
    }

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

    std::array<double, N>::iterator begin()
    {
        return _elements.begin();
    }
    std::array<double, N>::iterator end()
    {
        return _elements.end();
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

    NumericArray<N> immutableTransform(const std::function<double(double)> &transformation)
    {
        std::array<double, N> result;

        for (int i = 0; i < N; i++)
        {
            result[i] = transformation(_elements[i]);
        }

        return NumericArray(result);
    }

    NumericArray<N> mutableTransform(const std::function<double(double)> &transformation)
    {
        for (auto &element : _elements)
        {
            element = transformation(element);
        }

        return *this;
    }

    // Addition
    NumericArray<N> operator+()
    {
        return *this;
    }

    NumericArray<N> operator+(const double term)
    {
        return immutableTransform([term](double x)
                                  { return x + term; });
    }

    NumericArray<N> operator+(NumericArray &array)
    {
        return merge(*this, array, [](double x, double y)
                     { return x + y; });
    }

    void operator+=(const double term)
    {
        *this = *this + term;
    }

    void operator+=(NumericArray &array)
    {
        *this = *this + array;
    }

    // Subtraction
    NumericArray<N> operator-()
    {
        return immutableTransform([](double x)
                                  { return -x; });
    }

    NumericArray<N> operator-(const double term)
    {
        return immutableTransform([term](double x)
                                  { return x - term; });
    }

    NumericArray<N> operator-(NumericArray &array)
    {
        return merge(*this, array, [](double x, double y)
                     { return x - y; });
    }

    void operator-=(const double term)
    {
        *this = *this - term;
    }

    void operator-=(NumericArray &array)
    {
        *this = *this - array;
    }

    // Multiplication
    NumericArray<N> operator*(const double term)
    {
        return immutableTransform([term](double x)
                                  { return x * term; });
    }

    NumericArray<N> operator*(NumericArray &array)
    {
        return merge(*this, array, [](double x, double y)
                     { return x * y; });
    }

    void operator*=(const double term)
    {
        *this = *this * term;
    }

    void operator*=(NumericArray &array)
    {
        *this = *this * array;
    }

    // Division
    NumericArray<N> operator/(const double term)
    {
        return immutableTransform([term](double x)
                                  { return x / term; });
    }

    NumericArray<N> operator/(NumericArray &array)
    {
        return merge(*this, array, [](double x, double y)
                     { return x / y; });
    }

    void operator/=(const double term)
    {
        *this = *this / term;
    }

    void operator/=(NumericArray &array)
    {
        *this = *this / array;
    }

    std::string toString()
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
};

typedef NumericArray<4> Vec4;
typedef NumericArray<4> Hsla;
typedef NumericArray<4> Rgba;
typedef NumericArray<3> Vec3;
typedef NumericArray<2> Vec2;
typedef NumericArray<1> Scalar;