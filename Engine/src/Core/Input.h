#pragma once

#include "Core/Core.h"

#include "Core/KeyCodes.h"
#include "Core/MouseCodes.h"

namespace Elven
{
    class Input
    {
    public:
        static bool IsKeyPressed(KeyCode key);

        static bool IsMousePressed(MouseCode button);
        static std::pair<float, float> GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();
    };


}