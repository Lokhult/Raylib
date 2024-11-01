#pragma once

#include <cmath>
#include <functional>
#include <algorithm>
#include <optional>
#include <iostream>

const double pi = 3.141592653589793238462643383279502884197;
typedef std::function<std::vector<double>(std::vector<double>)> VectorFn;

class VectorFunction
{
private:
    VectorFunction *_innerFunction;
    VectorFn _function;
    size_t _inDim;
    size_t _outDim;

public:
    VectorFunction(size_t inDim, size_t outDim, VectorFn function, VectorFunction *innerFunction = nullptr)
    {
        _inDim = inDim;
        _outDim = outDim;
        _function = function;
        _innerFunction = innerFunction;
    }

    std::vector<double> operator()(std::vector<double> t)
    {
        auto result = _function(t);
        if (_innerFunction == nullptr)
            return result;

        std::cout << "calling next function\n";

        return (*_innerFunction)(result);
    }
};

// namespace FunctionGenerators
// {
//     template <size_t InDim, size_t OutDim>
//     std::function<std::array<double, OutDim>(std::array<double, InDim>)> constant(
//         std::array<double, OutDim> c)
//     {
//         return [c](std::array<double, InDim> t)
//         {
//             return c;
//         };
//     }

//     template <size_t InDim, size_t OutDim>
//     std::function<std::array<double, OutDim>(std::array<double, InDim>)> add(
//         std::function<std::array<double, OutDim>(std::array<double, InDim>)> function,
//         std::array<std::function<std::array<double, OutDim>(std::array<double, InDim>)>, OutDim> term)
//     {
//         return [function, translation](std::array<double, InDim> t)
//         {
//             auto result = function(t);
//             for (int i = 0; i < OutDim; i++)
//             {
//                 result[i] += term(t)[i];
//             }
//             return result;
//         };
//     }

//     template <size_t InDim, size_t OutDim>
//     std::function<std::array<double, OutDim>(std::array<double, InDim>)> multiply(
//         std::function<std::array<double, OutDim>(std::array<double, InDim>)> function,
//         std::array<std::function<std::array<double, OutDim>(std::array<double, InDim>)>, OutDim> factor)
//     {
//         return [function, translation](std::array<double, InDim> t)
//         {
//             auto result = function(t);
//             for (int i = 0; i < OutDim; i++)
//             {
//                 result[i] *= factor(t)[i];
//             }
//             return result;
//         };
//     }

//     template <size_t InDim, size_t OutDim>
//     std::function<std::array<double, OutDim>(std::array<double, InDim>)> raise(
//         std::function<std::array<double, OutDim>(std::array<double, InDim>)> function,
//         std::array<std::function<std::array<double, OutDim>(std::array<double, InDim>)>, OutDim> exponent)
//     {
//         return [function, translation](std::array<double, InDim> t)
//         {
//             auto result = function(t);
//             for (int i = 0; i < OutDim; i++)
//             {
//                 result[i] = pow(result[i], factor(t)[i]);
//             }
//             return result;
//         };
//     }

//     template <size_t InDim, size_t OutDim>
//     std::function<std::array<double, OutDim>(std::array<double, InDim>)> sinus(
//         std::function<std::array<double, OutDim>(std::array<double, InDim>)> function)
//     {
//         return [function, translation](std::array<double, InDim> t)
//         {
//             auto result = function(t);
//             for (int i = 0; i < OutDim; i++)
//             {
//                 result[i] = sin(result[i]);
//             }
//             return result;
//         };
//     }

//     template <size_t InDim, size_t OutDim>
//     std::function<std::array<double, OutDim>(std::array<double, InDim>)> cos(
//         std::function<std::array<double, OutDim>(std::array<double, InDim>)> function)
//     {
//         auto negatedFn = multiply(function, constant({-1}));
//         auto scalarConstant = constant({pi * 0.5});
//         auto result = function(t);
//         for (int i = 0; i < OutDim; i++)
//         {
//             result[i] = sin(result[i]);
//         }
//         return result;
//         return sinus(add(scalarConstant, ))
//     }

//     template <size_t N, int StartExponent>
//     F1_1 polynomial(std::array<F1_1, N> coefficients)
//     {
//         return [coefficients, startExponent](double t)
//         {
//             double result = 0;
//             for (int i = 0; i < coefficients.size(); i++)
//             {
//                 result += pow(t, i + StartExponent) * coefficients[i](t);
//             }
//             return result;
//         };
//     }
// }

// namespace Functions
// {
//     const auto linear = FunctionGenerators::polynomial(1, 0);
// }