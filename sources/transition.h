#pragma once

#include <vector>
#include <functional>

// A set of function from [0, 1] to [0, 1]
namespace interpolations
{
    double linear(double x)
    {
        return x;
    }

    double ease_in_quad(double x)
    {
        return x * x;
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

public:
    transition(double duration, std::vector<numeric_array<N>> frames, std::function<double(double)> interpolation = interpolations::linear) : _duration(duration),
                                                                                                                                              _frames(frames),
                                                                                                                                              _interpolation(interpolation) {}

    numeric_array<N> update(double deltaSeconds)
    {
        _seconds += deltaSeconds;
        double t = _interpolation(_seconds / _duration);
        return numeric_array<N>::blend(_frames, t, numeric_array<N>::blend_mode::linear);
    }
};