#pragma once

#include <vector>
#include <functional>
#include <cmath>
#include <numbers>

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
    std::function<double(double)> _interpolation;
    std::function<double(double)> _overflow;

public:
    transition(
        double duration,
        std::vector<numeric_array<N>> frames,
        std::function<double(double)> interpolation = interpolations::linear,
        std::function<double(double)> overflow = overflows::clamp) : _duration(duration),
                                                                     _frames(frames),
                                                                     _interpolation(interpolation),
                                                                     _overflow(overflow) {}

    numeric_array<N> update(double deltaSeconds)
    {
        _seconds += deltaSeconds;
        double t = _interpolation(_overflow(_seconds / _duration));
        return numeric_array<N>::blend(_frames, t, numeric_array<N>::blend_mode::linear);
    }

    double seconds()
    {
        return _seconds;
    }

    double t()
    {
        return (_seconds / _duration);
    }

    double interpolated_t()
    {
        return _interpolation(_overflow(_seconds / _duration));
    }
};