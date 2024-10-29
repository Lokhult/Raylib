#pragma once

#include <vector>
#include <functional>
#include <string>

class numeric_array
{
    enum blend_mode
    {
        linear,
        cyclical
    };

protected:
    std::vector<double> _elements{};

public:
    static numeric_array linear_range(double start, double end, double count);
    static numeric_array merge(numeric_array &leftArray, numeric_array &rightArray, const std::function<double(double, double)> transformation);
    static numeric_array blend(vector<numeric_array> arrays, numeric_array &weight, blend_mode mode = linear);

    numeric_array() = default;
    numeric_array(std::vector<double> elements)
    {
        _elements = elements;
    }

    numeric_array(std::initializer_list<double> init_list)
    {
        _elements = init_list;
    }

    std::vector<double>::iterator begin();
    std::vector<double>::iterator end();

    double& operator[](int i);

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