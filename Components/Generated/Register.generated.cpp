#include "Register.generated.h"

#ifdef DEV_CONFIGURATION

void Register::RegisterComponents()
{
    ScarlEnt::Registry& registry = ScarlEnt::Registry::Instance();

    RegisterComponentTypeAndFunctionPointer<Scarlet::Component::PlayerController>(registry);

}

void Register::UnregisterComponents()
{
    ScarlEnt::Registry& registry = ScarlEnt::Registry::Instance();

    UnregisterComponentType<Scarlet::Component::PlayerController>(registry);

}

#endif // DEV_CONFIGURATION.
