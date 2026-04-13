#include "Components/WaveManager.h"

#include <ScarlEnt/ComponentManager.h>

#include <ScarletReflect/ReflectType.h>

namespace Scarlet::Component
{

#ifdef DEV_CONFIGURATION

void WaveManager::GenerateProperties()
{
    mProperties.clear();
    mProperties["wave"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::UINT32,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<WaveManager>(),
        [this] { return ReflectType::GetStringFromValue(this->wave); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->wave, stringValue); }
    };

    mProperties["numberOfEnemiesToSpawn"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::UINT32,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<WaveManager>(),
        [this] { return ReflectType::GetStringFromValue(this->numberOfEnemiesToSpawn); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->numberOfEnemiesToSpawn, stringValue); }
    };

    mProperties["numberOfSpawnedEnemies"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::UINT32,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<WaveManager>(),
        [this] { return ReflectType::GetStringFromValue(this->numberOfSpawnedEnemies); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->numberOfSpawnedEnemies, stringValue); }
    };

    mProperties["maxNumberOfEnemies"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::UINT32,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<WaveManager>(),
        [this] { return ReflectType::GetStringFromValue(this->maxNumberOfEnemies); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->maxNumberOfEnemies, stringValue); }
    };

    mProperties["timeBetweenWaves"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::FLOAT,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<WaveManager>(),
        [this] { return ReflectType::GetStringFromValue(this->timeBetweenWaves); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->timeBetweenWaves, stringValue); }
    };

    mProperties["timeBetweenSpawns"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::FLOAT,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<WaveManager>(),
        [this] { return ReflectType::GetStringFromValue(this->timeBetweenSpawns); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->timeBetweenSpawns, stringValue); }
    };

    mProperties["startingEnemyHealth"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::FLOAT,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<WaveManager>(),
        [this] { return ReflectType::GetStringFromValue(this->startingEnemyHealth); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->startingEnemyHealth, stringValue); }
    };

    mProperties["startingEnemySpeed"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::FLOAT,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<WaveManager>(),
        [this] { return ReflectType::GetStringFromValue(this->startingEnemySpeed); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->startingEnemySpeed, stringValue); }
    };

    mProperties["maxEnemySpeed"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::FLOAT,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<WaveManager>(),
        [this] { return ReflectType::GetStringFromValue(this->maxEnemySpeed); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->maxEnemySpeed, stringValue); }
    };

    mProperties["currentTimer"] = ScarlEnt::Property {
        ScarlEnt::PropertyType::FLOAT,
        ScarlEnt::Registry::Instance().GetOrRegisterComponentId<WaveManager>(),
        [this] { return ReflectType::GetStringFromValue(this->currentTimer); },
        [this](const std::string_view& stringValue) { ReflectType::SetValueFromString(this->currentTimer, stringValue); }
    };
};

#endif // DEV_CONFIGURATION.

} // Namespace Scarlet::Component.
