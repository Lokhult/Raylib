#pragma once

#include <vector>
#include <functional>
#include <cmath>
#include <numbers>
#include <random>

// A set of function from [0, 1] to [0, 1]
namespace interpolations
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
namespace overflows
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
class transition
{
private:
    double _duration;
    double _seconds = 0;
    std::vector<numeric_array<N>> _frames;
    std::array<std::function<double(double)>, N> _interpolations;
    std::array<std::function<double(double)>, N> _overflows;

public:
    transition(
        double duration,
        std::vector<numeric_array<N>> frames,
        std::function<double(double)> interpolation = interpolations::linear,
        std::function<double(double)> overflow = overflows::clamp) : _duration(duration),
                                                                     _frames(frames)
    {
        for (int i = 0; i < N; i++)
        {
            _interpolations[i] = interpolation;
            _overflows[i] = overflow;
        }
    }

    transition(
        double duration,
        std::vector<numeric_array<N>> frames,
        std::array<std::function<double(double)>, N> interpolations,
        std::function<double(double)> overflow = overflows::clamp) : _duration(duration),
                                                                     _interpolations(interpolations),
                                                                     _frames(frames)
    {
        for (int i = 0; i < N; i++)
        {
            _overflows[i] = overflow;
        }
    }

    transition(
        double duration,
        std::vector<numeric_array<N>> frames,
        std::array<std::function<double(double)>, N> interpolations,
        std::array<std::function<double(double)>, N> overflows) : _duration(duration),
                                                                  _frames(frames),
                                                                  _interpolations(interpolations),
                                                                  _overflows(overflows)
    {
    }

    numeric_array<N> update(double deltaSeconds)
    {
        _seconds += deltaSeconds;

        std::array<double, N> t;
        for (int i = 0; i < N; i++)
        {
            t[i] = _interpolations[i](_overflows[i](_seconds / _duration));
        }
        auto weights = numeric_array<N>{t};

        return numeric_array<N>::blend(_frames, weights, numeric_array<N>::blend_mode::open);
    }
};