#pragma once

#include <ScarlEnt/RTTI/Rtti.h>

#include <ScarletMath/Math.h>

namespace Scarlet::Component
{

struct Bullet
{
    float      damage;
    float      speed;
    Math::Vec3 direction;

    SCARLET_COMPONENT(Bullet)
};

} // Namespace Scarlet::Component.
