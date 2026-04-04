#pragma once

#include <Scarlet/Core/IGame.h>

#include "Defines.h"

#ifdef DEV_CONFIGURATION
#include "Components/Generated/Register.generated.h"
#endif // DEV_CONFIGURATION

class GAME_API Game : public Scarlet::IGame
{
public:
    void Init() override;
    void Terminate() override;
};

extern "C" inline GAME_API Scarlet::IGame* CreateGameInstance() 
{
#ifdef DEV_CONFIGURATION
    Register::RegisterComponents();
#endif // DEV_CONFIGURATION
    return new Game();
}