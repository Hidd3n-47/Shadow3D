#pragma once

#include <functional>

#include <ScarlEnt/RTTI/Rtti.h>

namespace Scarlet::Component
{

struct Health
{
    float health = 100.0f;
    std::function<void()> onHealthReachZeroCallback;

    SCARLET_COMPONENT(Health)
};

} // Namespace Scarlet::Component.