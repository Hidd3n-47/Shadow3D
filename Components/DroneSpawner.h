#pragma once

#include <ScarlEnt/RTTI/Rtti.h>

namespace Scarlet::Component
{

struct DroneSpawner
{
    float spawnCooldown = 2.0f;
    float currentTimer  = spawnCooldown;

    SCARLET_COMPONENT(DroneSpawner)
};

} // Namespace Scarlet::Component.
