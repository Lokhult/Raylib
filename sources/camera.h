#pragma once

#include <raylib.h>

class camera
{
private:
    Camera2D _camera;

public:
    camera(Camera2D camera) : _camera(camera) {}

    camera(int screenWidth, int screenHeight)
    {
        _camera = Camera2D{
            .offset = {static_cast<float>(screenWidth / 2), static_cast<float>(screenHeight / 2)},
            .target = {0, 0},
            .rotation = 0,
            .zoom = 1};
    }

    void begin()
    {
        BeginMode2D(_camera);
    }

    void end()
    {
        EndMode2D();
    }
};