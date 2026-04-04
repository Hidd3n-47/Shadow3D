#include "Register.generated.h"

#ifdef DEV_CONFIGURATION

void Register::RegisterComponents()
{
    ScarlEnt::Registry& registry = ScarlEnt::Registry::Instance();

    RegisterComponentTypeAndFunctionPointer<Scarlet::Component::DroneController>(registry);
    RegisterComponentTypeAndFunctionPointer<Scarlet::Component::DroneSpawner>(registry);
    RegisterComponentTypeAndFunctionPointer<Scarlet::Component::PlayerController>(registry);

}

void Register::UnregisterComponents()
{
    ScarlEnt::Registry& registry = ScarlEnt::Registry::Instance();

    UnregisterComponentType<Scarlet::Component::DroneController>(registry);
    UnregisterComponentType<Scarlet::Component::DroneSpawner>(registry);
    UnregisterComponentType<Scarlet::Component::PlayerController>(registry);

}

#endif // DEV_CONFIGURATION.
