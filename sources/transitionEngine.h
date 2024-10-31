#pragma once

#include "transition.h"

template <int N>
class TransitionEngine
{
private:
    std::vector<Transition<N>> _transitions;

public:
    TransitionEngine() = default;

    void addTransition(Transition<N> transition)
    {
        _transitions.push_back(transition);
    }

    void update(double deltaSeconds)
    {
        for (auto &transition : _transitions)
        {
            transition.update(deltaSeconds);
        }
    }
};