#include "Components/DroneController.h"

#include <ScarlEnt/ComponentManager.h>

#include <ScarletReflect/ReflectType.h>

namespace Scarlet::Component
{

#ifdef DEV_CONFIGURATION

void DroneController::GenerateProperties()
{
    mProperties.clear();
    mProperties["speed"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::FLOAT,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<DroneController>(),
        [this] { return ReflectType::GetStringFromValue(this->speed); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->speed, stringValue); }
    };

    mProperties["damagePlayerCooldown"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::FLOAT,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<DroneController>(),
        [this] { return ReflectType::GetStringFromValue(this->damagePlayerCooldown); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->damagePlayerCooldown, stringValue); }
    };

    mProperties["damagePlayerCooldownTimer"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::FLOAT,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<DroneController>(),
        [this] { return ReflectType::GetStringFromValue(this->damagePlayerCooldownTimer); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->damagePlayerCooldownTimer, stringValue); }
    };
};

#endif // DEV_CONFIGURATION.

} // Namespace Scarlet::Component.
