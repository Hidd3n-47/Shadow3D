#include "Game.h"

#include <ScarlEnt/Registry.h>

#include "Scenes/GameScene.h"

#ifndef DEV_CONFIGURATION
#include "Build/SceneBuild.h"
#endif // DEV_CONFIGURATION.

void Game::Init()
{
    ScarlEnt::Registry& registry = ScarlEnt::Registry::Instance();

    // Initialise and register scenes.
    Scarlet::WeakHandle<ScarlEnt::Scene> baseScene = registry.GetOrCreateScene<GameScene>("GameScene");

    // This will register and create the game scenes in release builds. This is generated from the built scenes.
#ifndef DEV_CONFIGURATION
    Scarlet::InitGameScene();

    // Set the active scene. This can safely be done as this is the entry scene.
    registry.SetActiveScene(baseScene);
#endif // !DEV_CONFIGURATION.
}

void Game::Terminate()
{
    // Terminate and remove scenes added for the project.
    ScarlEnt::Registry::Instance().RemoveScene("GameScene");

#ifdef DEV_CONFIGURATION
    Register::UnregisterComponents();
#endif // DEV_CONFIGURATION.
}
