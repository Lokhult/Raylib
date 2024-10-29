#pragma once

#include <vector>
#include <functional>
#include <string>

class numeric_array
{
protected:
    std::vector<double> _elements{};

public:
    numeric_array(std::vector<double> elements)
    {
        _elements = elements;
    }

    numeric_array(std::initializer_list<double> init_list)
    {
        _elements = init_list;
    }

    const size_t size();

    static numeric_array merge(numeric_array &leftArray, numeric_array &rightArray, const std::function<double(double, double)> transformation);
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