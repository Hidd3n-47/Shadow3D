#pragma once

#include <ScarlEnt/RTTI/Rtti.h>

#include <ScarletMath/Math.h>

namespace Scarlet::Component
{

struct Bullet
{
    float      lifetime = 3.0f;
    float      damage;
    float      speed;
    Math::Vec3 direction;

    SCARLET_COMPONENT(Bullet)
};

} // Namespace Scarlet::Component.
