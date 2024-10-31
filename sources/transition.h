#pragma once

#include <vector>
#include <functional>
#include <cmath>
#include <numbers>
#include <random>

// A set of function from [0, 1] to [0, 1]
namespace Interpolations
{
    double linear(double t)
    {
        return t;
    }

    double ease_in_ease_out(double t)
    {
        return 0.5 * (sin((t - 0.5) * std::numbers::pi) + 1);
    }

    double random(double t)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> distr(0, 1);
        return distr(gen);
    }
}

// A set of functions to handle overflow of range [0, 1]
namespace Overflows
{
    double clamp(double t)
    {
        if (t <= 0)
            return 0;
        if (t > 1)
            return 1;
        return t;
    }

    double repeat(double t)
    {
        return t - floor(t);
    }
}

template <int N>
class Transition
{
private:
    double _duration;
    double _seconds = 0;
    std::vector<NumericArray<N>> _frames;
    NumericArray<N> &_boundArray;
    std::array<std::function<double(double)>, N> _interpolations;
    std::array<std::function<double(double)>, N> _overflows;

public:
    Transition(
        NumericArray<N> &boundArray,
        double duration,
        std::vector<NumericArray<N>> frames,
        std::function<double(double)> interpolation = Interpolations::linear,
        std::function<double(double)> overflow = Overflows::clamp) : _boundArray(boundArray),
                                                                     _duration(duration),
                                                                     _frames(frames)
    {
        for (int i = 0; i < N; i++)
        {
            _interpolations[i] = interpolation;
            _overflows[i] = overflow;
        }
    }

    Transition(
        NumericArray<N> &boundArray,
        double duration,
        std::vector<NumericArray<N>> frames,
        std::array<std::function<double(double)>, N> interpolations,
        std::function<double(double)> overflow = Overflows::clamp) : _boundArray(boundArray),
                                                                     _duration(duration),
                                                                     _interpolations(interpolations),
                                                                     _frames(frames)
    {
        for (int i = 0; i < N; i++)
        {
            _overflows[i] = overflow;
        }
    }

    Transition(
        NumericArray<N> &boundArray,
        double duration,
        std::vector<NumericArray<N>> frames,
        std::array<std::function<double(double)>, N> interpolations,
        std::array<std::function<double(double)>, N> overflows) : _boundArray(boundArray),
                                                                  _duration(duration),
                                                                  _frames(frames),
                                                                  _interpolations(interpolations),
                                                                  _overflows(overflows)
    {
    }

    void update(double deltaSeconds)
    {
        _seconds += deltaSeconds;

        std::array<double, N> t;
        for (int i = 0; i < N; i++)
        {
            t[i] = _interpolations[i](_overflows[i](_seconds / _duration));
        }
        auto weights = NumericArray<N>{t};

        auto result = NumericArray<N>::blend(_frames, weights, NumericArray<N>::BlendMode::open);

        for (int i = 0; i < N; i++)
        {
            _boundArray[i] = result[i];
        }
    }
};