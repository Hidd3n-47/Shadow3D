#pragma once

#include <ScarlEnt/RTTI/Rtti.h>

namespace Scarlet::Component
{

struct DroneController
{
    float speed = 1.0f;

    SCARLET_COMPONENT(DroneController)
};

} // Namespace Scarlet::Component.
