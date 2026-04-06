#include "Components/DroneSpawner.h"

#include <ScarlEnt/ComponentManager.h>

#include <ScarletReflect/ReflectType.h>

namespace Scarlet::Component
{

#ifdef DEV_CONFIGURATION

void DroneSpawner::GenerateProperties()
{
    mProperties.clear();
    mProperties["spawnCooldown"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::FLOAT,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<DroneSpawner>(),
        [this] { return ReflectType::GetStringFromValue(this->spawnCooldown); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->spawnCooldown, stringValue); }
    };

    mProperties["currentTimer"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::FLOAT,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<DroneSpawner>(),
        [this] { return ReflectType::GetStringFromValue(this->currentTimer); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->currentTimer, stringValue); }
    };
};

#endif // DEV_CONFIGURATION.

} // Namespace Scarlet::Component.
