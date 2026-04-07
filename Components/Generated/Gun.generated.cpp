#include "Components/Gun.h"

#include <ScarlEnt/ComponentManager.h>

#include <ScarletReflect/ReflectType.h>

namespace Scarlet::Component
{

#ifdef DEV_CONFIGURATION

void Gun::GenerateProperties()
{
    mProperties.clear();
    mProperties["magSize"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::UINT32,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<Gun>(),
        [this] { return ReflectType::GetStringFromValue(this->magSize); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->magSize, stringValue); }
    };

    mProperties["currentMagSize"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::UINT32,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<Gun>(),
        [this] { return ReflectType::GetStringFromValue(this->currentMagSize); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->currentMagSize, stringValue); }
    };

    mProperties["damage"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::FLOAT,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<Gun>(),
        [this] { return ReflectType::GetStringFromValue(this->damage); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->damage, stringValue); }
    };

    mProperties["reloadTime"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::FLOAT,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<Gun>(),
        [this] { return ReflectType::GetStringFromValue(this->reloadTime); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->reloadTime, stringValue); }
    };

    mProperties["reloadTimer"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::FLOAT,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<Gun>(),
        [this] { return ReflectType::GetStringFromValue(this->reloadTimer); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->reloadTimer, stringValue); }
    };
};

#endif // DEV_CONFIGURATION.

} // Namespace Scarlet::Component.
