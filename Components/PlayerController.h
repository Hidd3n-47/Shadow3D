#pragma once

#include <ScarlEnt/RTTI/Rtti.h>

namespace Scarlet::Component
{

struct PlayerController
{
    float speed           =  1.0f;
    float xCenterPosition =  0.0f;
    float xHalfWidth      = 15.0f;
    float yCenterPosition = 11.0f;
    float yHalfWidth      = 14.0f;
    float paddingFromWall =  1.0f;

    SCARLET_COMPONENT(PlayerController)
};

} // Namespace Scarlet::Component.
