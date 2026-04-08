#include "Components/Health.h"

#include <ScarlEnt/ComponentManager.h>

#include <ScarletReflect/ReflectType.h>

namespace Scarlet::Component
{

#ifdef DEV_CONFIGURATION

void Health::GenerateProperties()
{
    mProperties.clear();
    mProperties["health"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::FLOAT,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<Health>(),
        [this] { return ReflectType::GetStringFromValue(this->health); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->health, stringValue); }
    };
};

#endif // DEV_CONFIGURATION.

} // Namespace Scarlet::Component.
