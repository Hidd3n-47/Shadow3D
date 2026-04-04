#include "Components/PlayerController.h"

#include <ScarlEnt/ComponentManager.h>

#include <ScarletReflect/ReflectType.h>

namespace Scarlet::Component
{

#ifdef DEV_CONFIGURATION

void PlayerController::GenerateProperties()
{
    mProperties.clear();
    mProperties["speed"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::FLOAT,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<PlayerController>(),
        [this] { return ReflectType::GetStringFromValue(this->speed); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->speed, stringValue); }
    };
};

#endif // DEV_CONFIGURATION.

} // Namespace Scarlet::Component.
