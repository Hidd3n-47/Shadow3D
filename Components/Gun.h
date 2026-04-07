#pragma once

#include <ScarlEnt/RTTI/Rtti.h>

namespace Scarlet::Component
{

struct Gun
{
    uint32 magSize        = 12;
    uint32 currentMagSize = magSize;
    float  damage         = 20.0f;
    float  reloadTime     = 2.0f;
    float  reloadTimer    = 0.0f;

    SCARLET_COMPONENT(Gun)
};

} // Namespace Scarlet::Component.
