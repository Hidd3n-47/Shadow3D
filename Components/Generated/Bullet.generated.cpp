#include "Components/Bullet.h"

#include <ScarlEnt/ComponentManager.h>

#include <ScarletReflect/ReflectType.h>

namespace Scarlet::Component
{

#ifdef DEV_CONFIGURATION

void Bullet::GenerateProperties()
{
    mProperties.clear();
    mProperties["damage"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::FLOAT,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<Bullet>(),
        [this] { return ReflectType::GetStringFromValue(this->damage); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->damage, stringValue); }
    };

    mProperties["speed"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::FLOAT,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<Bullet>(),
        [this] { return ReflectType::GetStringFromValue(this->speed); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->speed, stringValue); }
    };

    mProperties["direction"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::VEC3,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<Bullet>(),
        [this] { return ReflectType::GetStringFromValue(this->direction); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->direction, stringValue); }
    };
};

#endif // DEV_CONFIGURATION.

} // Namespace Scarlet::Component.
