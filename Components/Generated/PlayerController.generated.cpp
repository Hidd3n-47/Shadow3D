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

    mProperties["xCenterPosition"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::FLOAT,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<PlayerController>(),
        [this] { return ReflectType::GetStringFromValue(this->xCenterPosition); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->xCenterPosition, stringValue); }
    };

    mProperties["xHalfWidth"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::FLOAT,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<PlayerController>(),
        [this] { return ReflectType::GetStringFromValue(this->xHalfWidth); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->xHalfWidth, stringValue); }
    };

    mProperties["yCenterPosition"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::FLOAT,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<PlayerController>(),
        [this] { return ReflectType::GetStringFromValue(this->yCenterPosition); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->yCenterPosition, stringValue); }
    };

    mProperties["yHalfWidth"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::FLOAT,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<PlayerController>(),
        [this] { return ReflectType::GetStringFromValue(this->yHalfWidth); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->yHalfWidth, stringValue); }
    };

    mProperties["paddingFromWall"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::FLOAT,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<PlayerController>(),
        [this] { return ReflectType::GetStringFromValue(this->paddingFromWall); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->paddingFromWall, stringValue); }
    };
};

#endif // DEV_CONFIGURATION.

} // Namespace Scarlet::Component.
