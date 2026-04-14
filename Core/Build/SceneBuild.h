#pragma once

#ifndef DEV_CONFIGURATION

#include <ScarletCore/Defines.h>

#include <ScarlEnt/Scene.h>
#include <ScarlEnt/Registry.h>
#include <ScarlEnt/MutableEntityHandle.h>

#include <ScarletEngine/Core/Filepath.h>

#include <ScarletCoreEcs/Components/Generated/Register.generated.h>

namespace Scarlet
{

inline void InitGameScene()
{
    Filepath::SetEngineDirectory("C:/Users/chris/Downloads/Shadow3D/EngineResources");
    Filepath::SetProjectDirectory("C:/Users/chris/Downloads/Shadow3D/GameResources");

    Engine::Instance().LoadScarletAssets();
    
    WeakHandle<ScarlEnt::Scene> scene = ScarlEnt::Registry::Instance().GetScene("GameScene");

   {
        Component::Transform Transform{};
        Transform.translation = Math::Vec3{ 0.000000,35.000000,-1.500000 };
        Transform.rotation = Math::Vec3{ 0.000000,0.000000,0.000000 };
        Transform.scale = Math::Vec3{ 1.000000,1.000000,1.000000 };
        Component::StaticMesh StaticMesh{};
        StaticMesh.mesh = AssetRef{ 0,37310013715408072 };
        StaticMesh.material = AssetRef{ 2,33630958529845530 };

        scene->AddEntity<Component::Transform, Component::StaticMesh>(std::move(Transform), std::move(StaticMesh));
    }

   {
        Component::Transform Transform{};
        Transform.translation = Math::Vec3{ -14.500000,0.500000,2.000000 };
        Transform.rotation = Math::Vec3{ 0.000000,0.000000,0.000000 };
        Transform.scale = Math::Vec3{ 0.200000,1.000000,1.000000 };
        Component::DroneSpawner DroneSpawner{};
        Component::StaticMesh StaticMesh{};
        StaticMesh.mesh = AssetRef{ 0,0 };
        StaticMesh.material = AssetRef{ 2,0 };

        scene->AddEntity<Component::Transform, Component::DroneSpawner, Component::StaticMesh>(std::move(Transform), std::move(DroneSpawner), std::move(StaticMesh));
    }

   {
        Component::Transform Transform{};
        Transform.translation = Math::Vec3{ 0.000000,0.000000,-0.850000 };
        Transform.rotation = Math::Vec3{ 0.000000,0.000000,0.000000 };
        Transform.scale = Math::Vec3{ 1.000000,1.000000,1.000000 };
        Component::StaticMesh StaticMesh{};
        StaticMesh.mesh = AssetRef{ 0,37314080891006766 };
        StaticMesh.material = AssetRef{ 2,37314269018342713 };

        scene->AddEntity<Component::Transform, Component::StaticMesh>(std::move(Transform), std::move(StaticMesh));
    }

   {
        Component::Transform Transform{};
        Transform.translation = Math::Vec3{ 0.000000,-3.000000,-33.000000 };
        Transform.rotation = Math::Vec3{ 90.000000,0.000000,0.000000 };
        Transform.scale = Math::Vec3{ 1.000000,1.000000,1.000000 };
        Component::StaticMesh StaticMesh{};
        StaticMesh.mesh = AssetRef{ 0,37310013715408072 };
        StaticMesh.material = AssetRef{ 2,37322288106903960 };

        scene->AddEntity<Component::Transform, Component::StaticMesh>(std::move(Transform), std::move(StaticMesh));
    }

   {
        Component::Transform Transform{};
        Transform.translation = Math::Vec3{ 0.000000,25.000000,-33.000000 };
        Transform.rotation = Math::Vec3{ 90.000000,0.000000,0.000000 };
        Transform.scale = Math::Vec3{ 1.000000,1.000000,1.000000 };
        Component::StaticMesh StaticMesh{};
        StaticMesh.mesh = AssetRef{ 0,37310013715408072 };
        StaticMesh.material = AssetRef{ 2,37322288106903960 };

        scene->AddEntity<Component::Transform, Component::StaticMesh>(std::move(Transform), std::move(StaticMesh));
    }

   {
        Component::Transform Transform{};
        Transform.translation = Math::Vec3{ 15.000000,0.000000,-33.000000 };
        Transform.rotation = Math::Vec3{ 90.000000,0.000000,90.000000 };
        Transform.scale = Math::Vec3{ 1.000000,1.000000,1.000000 };
        Component::StaticMesh StaticMesh{};
        StaticMesh.mesh = AssetRef{ 0,37310013715408072 };
        StaticMesh.material = AssetRef{ 2,37322288106903960 };

        scene->AddEntity<Component::Transform, Component::StaticMesh>(std::move(Transform), std::move(StaticMesh));
    }

   {
        Component::Transform Transform{};
        Transform.translation = Math::Vec3{ -15.000000,0.000000,-33.000000 };
        Transform.rotation = Math::Vec3{ 90.000000,0.000000,90.000000 };
        Transform.scale = Math::Vec3{ 1.000000,1.000000,1.000000 };
        Component::StaticMesh StaticMesh{};
        StaticMesh.mesh = AssetRef{ 0,37310013715408072 };
        StaticMesh.material = AssetRef{ 2,37322288106903960 };

        scene->AddEntity<Component::Transform, Component::StaticMesh>(std::move(Transform), std::move(StaticMesh));
    }

   {
        Component::Transform Transform{};
        Transform.translation = Math::Vec3{ 12.000000,-2.500000,2.000000 };
        Transform.rotation = Math::Vec3{ 0.000000,0.000000,0.000000 };
        Transform.scale = Math::Vec3{ 1.000000,0.200000,1.000000 };
        Component::DroneSpawner DroneSpawner{};
        Component::StaticMesh StaticMesh{};
        StaticMesh.mesh = AssetRef{ 0,0 };
        StaticMesh.material = AssetRef{ 2,0 };

        scene->AddEntity<Component::Transform, Component::DroneSpawner, Component::StaticMesh>(std::move(Transform), std::move(DroneSpawner), std::move(StaticMesh));
    }

   {
        Component::Transform Transform{};
        Transform.translation = Math::Vec3{ 0.000000,24.500000,2.000000 };
        Transform.rotation = Math::Vec3{ 0.000000,0.000000,0.000000 };
        Transform.scale = Math::Vec3{ 1.000000,0.200000,1.000000 };
        Component::DroneSpawner DroneSpawner{};
        Component::StaticMesh StaticMesh{};
        StaticMesh.mesh = AssetRef{ 0,0 };
        StaticMesh.material = AssetRef{ 2,0 };

        scene->AddEntity<Component::Transform, Component::DroneSpawner, Component::StaticMesh>(std::move(Transform), std::move(DroneSpawner), std::move(StaticMesh));
    }

   {
        Component::Transform Transform{};
        Transform.translation = Math::Vec3{ 0.000000,0.000000,0.000000 };
        Transform.rotation = Math::Vec3{ 0.000000,0.000000,0.000000 };
        Transform.scale = Math::Vec3{ 1.000000,1.000000,1.000000 };
        Component::WaveManager WaveManager{};
        WaveManager.wave = uint32{ 0 };
        WaveManager.numberOfEnemiesToSpawn = uint32{ 5 };
        WaveManager.numberOfSpawnedEnemies = uint32{ 0 };
        WaveManager.maxNumberOfEnemies = uint32{ 30 };
        WaveManager.maxEnemySpeed = float{ 0.100000 };
        WaveManager.startingEnemySpeed = float{ 0.020000 };
        WaveManager.timeBetweenWaves = float{ 2.000000 };
        WaveManager.timeBetweenSpawns = float{ 2.000000 };
        WaveManager.startingEnemyHealth = float{ 40.000000 };
        WaveManager.currentTimer = float{ 2.000000 };

        scene->AddEntity<Component::Transform, Component::WaveManager>(std::move(Transform), std::move(WaveManager));
    }

}

} // Namespace Scarlet.

#endif // DEV_CONFIGURATION.

