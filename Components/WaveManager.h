#pragma once

#include <ScarlEnt/RTTI/Rtti.h>

namespace Scarlet::Component
{

struct WaveManager
{
    uint32 wave = 0;

    uint32 numberOfEnemiesToSpawn = 5;
    uint32 numberOfSpawnedEnemies = 0;
    uint32 maxNumberOfEnemies     = 100;

    float timeBetweenWaves    =  2.0f;
    float timeBetweenSpawns   =  2.0f;
    float startingEnemyHealth = 40.0f;
    float startingEnemySpeed  =  0.02f;
    float maxEnemySpeed       =  0.1f;

    float currentTimer = timeBetweenWaves;

    SCARLET_COMPONENT(WaveManager)
};

} // Namespace Scarlet::Component.