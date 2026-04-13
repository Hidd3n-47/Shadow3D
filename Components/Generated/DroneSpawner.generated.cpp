#include "Components/DroneSpawner.h"

#include <ScarlEnt/ComponentManager.h>

#include <ScarletReflect/ReflectType.h>

namespace Scarlet::Component
{

#ifdef DEV_CONFIGURATION

void DroneSpawner::GenerateProperties()
{
    mProperties.clear();
};

#endif // DEV_CONFIGURATION.

} // Namespace Scarlet::Component.
