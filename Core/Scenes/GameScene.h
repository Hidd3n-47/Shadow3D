#pragma once

#include <ScarlEnt/Scene.h>

#include <ScarletMath/Trig.h>

#include <ScarletEngine/Core/Time.h>

#include <ScarletEngine/Core/Engine.h>

#include <ScarletEngine/Core/Input/KeyCodes.h>
#include <ScarletEngine/Core/Input/InputManager.h>

#ifdef DEV_CONFIGURATION
#include <ScarletCoreEcs/Components/EditorInfo.h>
#endif // DEV_CONFIGURATION.

#include <ScarletCoreEcs/Components/Camera.h>
#include <ScarletCoreEcs/Components/Transform.h>
#include <ScarletCoreEcs/Components/StaticMesh.h>
#include <ScarletCoreEcs/Components/SphereCollider.h>
#include <ScarletCoreEcs/Components/DirectionLight.h>

#include "Components/Gun.h"
#include "Components/Bullet.h"
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
        mPlayerEntity.AddComponent<Scarlet::Component::Gun>();
        Scarlet::Component::PlayerController& pc = mPlayerEntity.AddComponent<Scarlet::Component::PlayerController>();
        pc.speed = 0.125f;

        SetCameraEntityHandle(&mPlayerEntity);

        auto PlayerControllerSystem = [] (Scarlet::Component::Transform& transform, Scarlet::Component::Camera& camera, const Scarlet::Component::PlayerController& controller)
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

        auto PlayerGunSystem = [&](const Scarlet::Component::Transform& transform, const Scarlet::Component::Camera& camera, Scarlet::Component::Gun& gun)
        {
            if (gun.reloadTimer > 0.0f)
            {
                // We are reloading.
                gun.reloadTimer -= static_cast<float>(Scarlet::Time::GetFixedFrameDelta());

                if (gun.reloadTimer <= 0.0f)
                {
                    gun.reloadTimer = 0.0f;
                    gun.currentMagSize = gun.magSize;
                }

                return;
            }

            if (Scarlet::InputManager::IsKeyPressed(Scarlet::KeyCode::KEY_R))
            {
                gun.reloadTimer = gun.reloadTime;
                return;
            }

            if (!Scarlet::InputManager::IsKeyPressed(Scarlet::KeyCode::MOUSE_BUTTON_1) || gun.currentMagSize == 0)
            {
                return;
            }

            --gun.currentMagSize;

            Scarlet::Component::Transform t{};
            t.translation = transform.translation + camera.forwardVector * 0.6f;
            t.scale       = Scarlet::Math::Vec3{ 0.1f };

            Scarlet::Component::StaticMesh sm{};

            Scarlet::Component::SphereCollider sphere{};

            Scarlet::Component::Bullet b{};
            b.speed     = 1.0f;
            b.damage    = gun.damage;
            b.direction = camera.forwardVector;

            (void)AddEntity<Scarlet::Component::Transform, Scarlet::Component::StaticMesh, Scarlet::Component::SphereCollider, Scarlet::Component::Bullet>
                        (std::move(t), std::move(sm), std::move(sphere), std::move(b));
        };

        auto MoveDroneSystem = [&](Scarlet::Component::Transform& transform, const Scarlet::Component::DroneController& controller)
        {
            const Scarlet::Math::Vec3 playerPosition = mPlayerEntity.GetComponent<Scarlet::Component::Transform>().translation;
            const Scarlet::Math::Vec3 direction      = Scarlet::Math::Normalize(playerPosition - transform.translation);

            const float yaw   = Scarlet::Math::Degrees(static_cast<float>(Scarlet::Math::Trig::Atan2(direction.x, direction.y)));
            const float pitch = Scarlet::Math::Degrees(static_cast<float>(Scarlet::Math::Trig::Atan2(direction.z, sqrt(direction.x * direction.x + direction.y * direction.y))));

            transform.translation += direction * controller.speed;
            transform.rotation     = Scarlet::Math::Vec3{ pitch, 0.0f, yaw };
        };

        auto SpawnDroneSystem = [&] (const Scarlet::Component::Transform& transform, Scarlet::Component::DroneSpawner& droneSpawner)
        {
            droneSpawner.currentTimer -= static_cast<float>(Scarlet::Time::GetFixedFrameDelta());

            if (droneSpawner.currentTimer <= 0.0f)
            {
                Scarlet::Component::Transform t{};
                t.translation = transform.translation;
                t.rotation    = Scarlet::Math::Vec3{ 0.0f };
                t.scale       = Scarlet::Math::Vec3{ 0.5f };

                Scarlet::Component::StaticMesh sm;
                sm.mesh     = Scarlet::AssetRef{ Scarlet::AssetType::MESH    , 34764804665973553 };
                sm.material = Scarlet::AssetRef{ Scarlet::AssetType::MATERIAL, 34775035533044079 };

                Scarlet::Component::DroneController dc;
                dc.speed = 0.1f;

                Scarlet::Component::SphereCollider sphere;
                sphere.radius = 1.25f;

                auto entity = AddEntity<Scarlet::Component::Transform, Scarlet::Component::StaticMesh, Scarlet::Component::DroneController, Scarlet::Component::SphereCollider>
                                    (std::move(t), std::move(sm), std::move(dc), std::move(sphere));

                droneSpawner.currentTimer = droneSpawner.spawnCooldown;
            }
        };

        auto MoveBulletSystem = [&](Scarlet::Component::Transform& transform, const Scarlet::Component::Bullet& bullet){
            transform.translation += bullet.direction * bullet.speed;
        };

        RegisterFixedUpdateSystem<Scarlet::Component::Transform, Scarlet::Component::Camera, Scarlet::Component::PlayerController>(PlayerControllerSystem);
        RegisterFixedUpdateSystem<Scarlet::Component::Transform, Scarlet::Component::DroneController>(MoveDroneSystem);
        RegisterFixedUpdateSystem<Scarlet::Component::Transform, Scarlet::Component::DroneSpawner>(SpawnDroneSystem);
        RegisterFixedUpdateSystem<Scarlet::Component::Transform, Scarlet::Component::Bullet>(MoveBulletSystem);

        RegisterFixedUpdateSystem<Scarlet::Component::Transform, Scarlet::Component::Camera, Scarlet::Component::Gun>(PlayerGunSystem);
    }

    inline void Destroy() override
    {
        mPlayerEntity.DestroyEntity();
    }
private:
    ScarlEnt::MutableEntityHandle mPlayerEntity;
};

