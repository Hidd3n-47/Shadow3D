#pragma once

#include <ScarlEnt/Scene.h>

#include <ScarletEngine/Core/Engine.h>

#include <ScarletEngine/Core/Input/KeyCodes.h>
#include <ScarletEngine/Core/Input/InputManager.h>

#ifdef DEV_CONFIGURATION
#include <ScarletCoreEcs/Components/EditorInfo.h>
#endif // DEV_CONFIGURATION.

#include <ScarletCoreEcs/Components/Camera.h>
#include <ScarletCoreEcs/Components/Transform.h>
#include <ScarletCoreEcs/Components/StaticMesh.h>
#include <ScarletCoreEcs/Components/DirectionLight.h>

#include "Components/DroneSpawner.h"
#include "Components/DroneController.h"
#include "Components/PlayerController.h"

class GameScene : public ScarlEnt::Scene
{
public:
    inline GameScene(const std::string_view friendlyName) : Scene(friendlyName) { }

    inline void Init() override final
    {
        // Register the engine systems. Leave this for default engine systems such as rendering, physics etc..
        Scarlet::Engine::Instance().RegisterEngineSystems(Scarlet::WeakHandle<Scene>{ this });

        mPlayerEntity = AddMutableEntity();
#ifdef DEV_CONFIGURATION
        auto& info     = mPlayerEntity.AddComponent<Scarlet::Component::EditorInfo>();
        info.isMutable = true;
        info.name      = "PlayerEntity";
#endif // DEV_CONFIGURATION.
        mPlayerEntity.AddComponent<Scarlet::Component::Transform>();
        mPlayerEntity.AddComponent<Scarlet::Component::Camera>();
        mPlayerEntity.AddComponent<Scarlet::Component::DirectionLight>();
        auto& pc = mPlayerEntity.AddComponent<Scarlet::Component::PlayerController>();
        pc.speed = 0.05f;

        SetCameraEntityHandle(&mPlayerEntity);

        auto PlayerControllerSystem = [] (Scarlet::Component::Transform& transform, Scarlet::Component::Camera& camera, Scarlet::Component::PlayerController& controller)
        {
            Scarlet::Math::Vec3 horizontalDirection = { }, forwardDirection = { };

            if (Scarlet::InputManager::IsKeyDown(Scarlet::KeyCode::KEY_W))
            {
                forwardDirection += -1.0f;
            }
            if (Scarlet::InputManager::IsKeyDown(Scarlet::KeyCode::KEY_S))
            {
                forwardDirection += 1.0f;
            }
            if (Scarlet::InputManager::IsKeyDown(Scarlet::KeyCode::KEY_A))
            {
                horizontalDirection += -1.0f;
            }
            if (Scarlet::InputManager::IsKeyDown(Scarlet::KeyCode::KEY_D))
            {
                horizontalDirection += 1.0f;
            }

            constexpr float SPEED_SCALING_FACTOR_YAW   = 0.45f;
            constexpr float SPEED_SCALING_FACTOR_PITCH = 0.35f;

            const Scarlet::Math::Vec2 moveDelta = Scarlet::InputManager::GetMouseDeltaThisFrame();

            const Scarlet::Math::Vec3 forwardVector = Scarlet::Math::Normalize(Scarlet::Math::Vec3{ camera.forwardVector.x, camera.forwardVector.y, 0.0f });

            transform.rotation.z += -moveDelta.x * SPEED_SCALING_FACTOR_YAW;
            transform.rotation.x += -moveDelta.y * SPEED_SCALING_FACTOR_PITCH;

            transform.translation += camera.rightVector * horizontalDirection * controller.speed
                                  -  forwardVector      * forwardDirection    * controller.speed;

            camera.dirty = true;
        };

        auto MoveDroneSystem = [&](Scarlet::Component::Transform& transform, const Scarlet::Component::DroneController& controller)
        {
            const Scarlet::Math::Vec3 playerPosition = mPlayerEntity.GetComponent<Scarlet::Component::Transform>().translation;
            const Scarlet::Math::Vec3 direction      = Scarlet::Math::Normalize(playerPosition - transform.translation);

            transform.translation += direction * controller.speed;
        };

        auto SpawnDroneSystem = [&] (const Scarlet::Component::Transform& transform, Scarlet::Component::DroneSpawner& droneSpawner)
        {
            droneSpawner.currentTimer -= 0.01f;

            if (droneSpawner.currentTimer <= 0.0f)
            {
                Scarlet::Component::Transform t = transform;
                t.scale = Scarlet::Math::Vec3{ 0.5f };

                Scarlet::Component::StaticMesh sm;
                sm.mesh     = Scarlet::AssetRef{ Scarlet::AssetType::MESH    , 34764804665973553 };
                sm.material = Scarlet::AssetRef{ Scarlet::AssetType::MATERIAL, 34775035533044079 };

                Scarlet::Component::DroneController dc;
                dc.speed = 0.02f;

                auto entity = AddEntity<Scarlet::Component::Transform, Scarlet::Component::StaticMesh, Scarlet::Component::DroneController>(std::move(t), std::move(sm), std::move(dc));

                droneSpawner.currentTimer = droneSpawner.spawnCooldown;
            }
        };

        RegisterSystem<Scarlet::Component::Transform, Scarlet::Component::Camera, Scarlet::Component::PlayerController>(PlayerControllerSystem);
        RegisterSystem<Scarlet::Component::Transform, Scarlet::Component::DroneController>(MoveDroneSystem);
        RegisterSystem<Scarlet::Component::Transform, Scarlet::Component::DroneSpawner>(SpawnDroneSystem);
    }

    inline void Destroy() override
    {
        mPlayerEntity.DestroyEntity();
    }
private:
    ScarlEnt::MutableEntityHandle mPlayerEntity;
};

