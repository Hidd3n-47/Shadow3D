#pragma once

#include <ScarlEnt/RTTI/Rtti.h>
#include <ScarletMath/Math.h>

namespace Scarlet::Component
{

struct PlayerController
{
    float speed = 1.0f;

    SCARLET_COMPONENT(PlayerController)
};

} // Namespace Scarlet::Component.
