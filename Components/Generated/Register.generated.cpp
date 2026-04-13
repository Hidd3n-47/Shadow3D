#include "Register.generated.h"

#ifdef DEV_CONFIGURATION

void Register::RegisterComponents()
{
    ScarlEnt::Registry& registry = ScarlEnt::Registry::Instance();

    RegisterComponentTypeAndFunctionPointer<Scarlet::Component::Bullet>(registry);
    RegisterComponentTypeAndFunctionPointer<Scarlet::Component::DroneController>(registry);
    RegisterComponentTypeAndFunctionPointer<Scarlet::Component::DroneSpawner>(registry);
    RegisterComponentTypeAndFunctionPointer<Scarlet::Component::Gun>(registry);
    RegisterComponentTypeAndFunctionPointer<Scarlet::Component::Health>(registry);
    RegisterComponentTypeAndFunctionPointer<Scarlet::Component::PlayerController>(registry);
    RegisterComponentTypeAndFunctionPointer<Scarlet::Component::WaveManager>(registry);

}

void Register::UnregisterComponents()
{
    ScarlEnt::Registry& registry = ScarlEnt::Registry::Instance();

    UnregisterComponentType<Scarlet::Component::Bullet>(registry);
    UnregisterComponentType<Scarlet::Component::DroneController>(registry);
    UnregisterComponentType<Scarlet::Component::DroneSpawner>(registry);
    UnregisterComponentType<Scarlet::Component::Gun>(registry);
    UnregisterComponentType<Scarlet::Component::Health>(registry);
    UnregisterComponentType<Scarlet::Component::PlayerController>(registry);
    UnregisterComponentType<Scarlet::Component::WaveManager>(registry);

}

#endif // DEV_CONFIGURATION.
