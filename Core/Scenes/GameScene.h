#pragma once

#include <ScarlEnt/Scene.h>

#include <ScarletMath/Trig.h>

#include <ScarletEngine/Core/Time.h>
#include <ScarletEngine/Core/Engine.h>
#include <ScarletEngine/Core/Window/Window.h>
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
#include "Components/Health.h"
#include "Components/Bullet.h"
#include "Components/DroneSpawner.h"
#include "Components/DroneController.h"
#include "Components/PlayerController.h"
#include "Components/PlayerDead.h"
#include "Components/WaveManager.h"

enum class GameCollisionLayers : uint8
{
    DEFAULT = 0,
    BULLET  = 1,
    DRONE   = 2,
    PLAYER  = 3
};

class GameScene : public ScarlEnt::Scene
{
public:
    using BulletEntity = ScarlEnt::EntityHandle<Scarlet::Component::Transform, Scarlet::Component::StaticMesh, Scarlet::Component::SphereCollider, Scarlet::Component::Bullet>;

    inline GameScene(const std::string_view friendlyName) : Scene(friendlyName) { }

    inline void Init() override final
    {
        Scarlet::Engine::Instance().GetMainWindow()->SetShowCursor(false);

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
        mPlayerEntity.AddComponent<Scarlet::Component::Health>().health = 100.0f;
        Scarlet::Component::PlayerController& pc = mPlayerEntity.AddComponent<Scarlet::Component::PlayerController>();
        pc.speed = 0.125f;

        SetCameraEntityHandle(&mPlayerEntity);

        auto PlayerControllerSystem = [&] (Scarlet::Component::Transform& transform, Scarlet::Component::Camera& camera, const Scarlet::Component::PlayerController& controller)
        {
            if (dynamic_cast<ScarlEnt::MutableEntityHandle*>(GetIEntityHandle(transform.GetEntityUniqueId()))->HasComponent<Scarlet::Component::PlayerDead>())
            {
                // Don't allow for player movement if the player is dead.
                return;
            }

            Scarlet::Math::Vec3 direction{ 0.0f };

            if (Scarlet::InputManager::IsKeyDown(Scarlet::KeyCode::KEY_W))
            {
                direction.y += -1.0f;
            }
            if (Scarlet::InputManager::IsKeyDown(Scarlet::KeyCode::KEY_S))
            {
                direction.y += 1.0f;
            }
            if (Scarlet::InputManager::IsKeyDown(Scarlet::KeyCode::KEY_A))
            {
                direction.x += -1.0f;
            }
            if (Scarlet::InputManager::IsKeyDown(Scarlet::KeyCode::KEY_D))
            {
                direction.x += 1.0f;
            }

            constexpr float SPEED_SCALING_FACTOR_YAW   = 0.45f;
            constexpr float SPEED_SCALING_FACTOR_PITCH = 0.35f;

            const Scarlet::Math::Vec2 moveDelta = Scarlet::InputManager::GetMouseDeltaThisFrame();

            const float magnitudeSquared = Scarlet::Math::MagnitudeSquared(direction);
            direction = magnitudeSquared > 0.0f ? direction / Scarlet::Math::Sqrt(magnitudeSquared) : direction;

            const Scarlet::Math::Vec3 forwardVector = Scarlet::Math::Normalize(Scarlet::Math::Vec3{ camera.forwardVector.x, camera.forwardVector.y, 0.0f });

            transform.rotation.z += -moveDelta.x * SPEED_SCALING_FACTOR_YAW;
            transform.rotation.x += -moveDelta.y * SPEED_SCALING_FACTOR_PITCH;

            transform.rotation.x = transform.rotation.x > 0.0f ? std::min(transform.rotation.x, 45.0f) : std::max(transform.rotation.x, -60.0f);

            transform.translation += camera.rightVector * direction.x * controller.speed
                                  -  forwardVector      * direction.y * controller.speed;

            // Fix position to be within the wall bounds.
            // Western wall.
            if (const float delta = controller.xCenterPosition - controller.xHalfWidth + controller.paddingFromWall - transform.translation.x; delta > 0)
            {
                transform.translation.x += delta;
            }
            // Eastern wall.
            if (const float delta = controller.xCenterPosition + controller.xHalfWidth - controller.paddingFromWall - transform.translation.x; delta < 0)
            {
                transform.translation.x += delta;
            }
            // Northern wall.
            if (const float delta = controller.yCenterPosition + controller.yHalfWidth - controller.paddingFromWall - transform.translation.y; delta < 0)
            {
                transform.translation.y += delta;
            }
            // Southern wall.
            if (const float delta = controller.yCenterPosition - controller.yHalfWidth + controller.paddingFromWall - transform.translation.y; delta > 0)
            {
                transform.translation.y += delta;
            }

            camera.dirty = true;
        };

        auto PlayerGunSystem = [&](const Scarlet::Component::Transform& transform, const Scarlet::Component::Camera& camera, Scarlet::Component::Gun& gun)
        {
            if (gun.reloadTimer > 0.0f)
            {
                // We are reloading.
                gun.reloadTimer -= static_cast<float>(Scarlet::Time::GetFrameDelta());

                if (gun.reloadTimer <= 0.0f)
                {
                    gun.reloadTimer    = 0.0f;
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
            sphere.layer = static_cast<uint32>(GameCollisionLayers::BULLET);

            Scarlet::Component::Bullet b{};
            b.speed     = 1.0f;
            b.damage    = gun.damage;
            b.direction = camera.forwardVector;

            BulletEntity entity = AddEntity<Scarlet::Component::Transform, Scarlet::Component::StaticMesh, Scarlet::Component::SphereCollider, Scarlet::Component::Bullet>
                        (std::move(t), std::move(sm), std::move(sphere), std::move(b));

            entity.GetComponent<Scarlet::Component::SphereCollider>().onCollisionCallback = [entity](const Scarlet::Component::SphereCollider&) mutable
            {
                if (entity.IsValid())
                {
                    entity.DestroyEntity();
                }
            };
        };

        auto MoveDroneSystem = [&](Scarlet::Component::Transform& transform, Scarlet::Component::DroneController& controller)
        {
            if (mPlayerEntity.HasComponent<Scarlet::Component::PlayerDead>())
            {
                // Don't move th drones if the player is dead.
                return;
            }

            const Scarlet::Math::Vec3 playerPosition = mPlayerEntity.GetComponent<Scarlet::Component::Transform>().translation;
            const Scarlet::Math::Vec3 direction      = Scarlet::Math::Normalize(playerPosition - transform.translation);

            const float yaw   = Scarlet::Math::Degrees(static_cast<float>(Scarlet::Math::Trig::Atan2(direction.x, direction.y)));
            const float pitch = Scarlet::Math::Degrees(static_cast<float>(Scarlet::Math::Trig::Atan2(direction.z, sqrt(direction.x * direction.x + direction.y * direction.y))));

            transform.translation += direction * controller.speed;
            transform.rotation     = Scarlet::Math::Vec3{ pitch, 0.0f, yaw };

            // Check if the drone is close enough to the player to damage them.
            const Scarlet::Math::Vec2 xyPosition{ transform.translation - playerPosition };
            constexpr float distanceToPlayerSquared = 1.0f * 1.0f;

            controller.damagePlayerCooldownTimer -= static_cast<float>(Scarlet::Time::GetFixedFrameDelta());

            if (controller.damagePlayerCooldownTimer <= 0.0f && Scarlet::Math::MagnitudeSquared(xyPosition) <= distanceToPlayerSquared)
            {
                controller.damagePlayerCooldownTimer = controller.damagePlayerCooldown;
                Scarlet::Component::Health& playerHealth = mPlayerEntity.GetComponent<Scarlet::Component::Health>();
                playerHealth.health -= 20.0f;
                if (playerHealth.health <= 0.0f)
                {
                    mPlayerEntity.AddComponent<Scarlet::Component::PlayerDead>();
                }
            }
        };

        auto MoveBulletSystem = [&](Scarlet::Component::Transform& transform, Scarlet::Component::Bullet& bullet) 
        {
            transform.translation += bullet.direction * bullet.speed;
            bullet.lifetime       -= static_cast<float>(Scarlet::Time::GetFixedFrameDelta());

            if (bullet.lifetime <= 0)
            {
                if (BulletEntity* entity = dynamic_cast<BulletEntity*>(GetIEntityHandle(bullet.GetEntityUniqueId())); entity->IsValid())
                {
                    entity->DestroyEntity();
                }
            }
        };

        auto WaveManagerSystem = [&](Scarlet::Component::WaveManager& waveManager)
        {
            waveManager.currentTimer -= static_cast<float>(Scarlet::Time::GetFrameDelta());

            // All the enemies have been spawned, therefore look if they have been killed and a new wave needs to start.
            if (waveManager.numberOfSpawnedEnemies == waveManager.numberOfEnemiesToSpawn)
            {
                const auto drones = GetComponents<Scarlet::Component::DroneController>();

                // All drones are killed, thus start new wave.
                if (drones.empty())
                {
                    ++waveManager.wave;

                    waveManager.numberOfEnemiesToSpawn = static_cast<uint32>(static_cast<float>(waveManager.numberOfEnemiesToSpawn) * 1.5f);

                    waveManager.startingEnemyHealth *= 1.3f;
                    waveManager.startingEnemySpeed = std::min(waveManager.startingEnemySpeed + 0.01f, waveManager.maxEnemySpeed);

                    waveManager.currentTimer = waveManager.timeBetweenWaves + waveManager.timeBetweenSpawns;
                    waveManager.numberOfSpawnedEnemies = 0;
                }

                return;
            }

            // All the enemies haven't been spawned, so spawn if the timer has elapsed.
            if (waveManager.currentTimer > 0.0f)
            {
                return;
            }

            if (GetComponents<Scarlet::Component::DroneController>().size() == waveManager.maxNumberOfEnemies)
            {
                // The maximum number of enemies have been spawned in, wait until they are reduced to spawn in a new enemy.
                return;
            }

            // Spawn Enemy.
            ++waveManager.numberOfSpawnedEnemies;
            waveManager.currentTimer = waveManager.timeBetweenSpawns;

            const auto spawnPoints = GetComponents<Scarlet::Component::Transform, Scarlet::Component::DroneSpawner>();
            const Scarlet::Math::Vec3 spawnPosition = std::get<Scarlet::Component::Transform&>(spawnPoints[rand() % spawnPoints.size()]).translation;

            Scarlet::Component::Transform t{};
            t.translation = spawnPosition;
            t.rotation    = Scarlet::Math::Vec3{ 0.0f };
            t.scale       = Scarlet::Math::Vec3{ 0.5f };

            Scarlet::Component::StaticMesh sm;
            sm.mesh     = Scarlet::AssetRef{ Scarlet::AssetType::MESH    , 34764804665973553 };
            sm.material = Scarlet::AssetRef{ Scarlet::AssetType::MATERIAL, 34775035533044079 };

            Scarlet::Component::DroneController dc;
            dc.speed = waveManager.startingEnemySpeed;

            Scarlet::Component::SphereCollider sphere;
            sphere.radius = 1.25f;
            sphere.layer  = static_cast<uint32>(GameCollisionLayers::DRONE);

            Scarlet::Component::Health hp{};
            hp.health = waveManager.startingEnemyHealth;

            auto entity = AddEntity<Scarlet::Component::Transform, Scarlet::Component::StaticMesh, Scarlet::Component::DroneController,
                Scarlet::Component::SphereCollider, Scarlet::Component::Health>
                (std::move(t), std::move(sm), std::move(dc), std::move(sphere), std::move(hp));

            Scarlet::Component::SphereCollider& sphereComp = entity.GetComponent<Scarlet::Component::SphereCollider>();
            sphereComp.onCollisionCallback = [&, entity](const Scarlet::Component::SphereCollider& other) mutable
            {
                if (other.layer == static_cast<uint32>(GameCollisionLayers::BULLET))
                {
                    Scarlet::Component::Health& health = entity.GetComponent<Scarlet::Component::Health>();

                    BulletEntity* bullet = dynamic_cast<BulletEntity*>(GetIEntityHandle(other.GetEntityUniqueId()));
                    const float bulletDamage = bullet->GetComponent<Scarlet::Component::Bullet>().damage;

                    health.health -= bulletDamage;
                    if (health.health <= 0.0f && health.onHealthReachZeroCallback)
                    {
                        health.onHealthReachZeroCallback();
                    }
                }
            };

            Scarlet::Component::Health& healthComp = entity.GetComponent<Scarlet::Component::Health>();
            healthComp.onHealthReachZeroCallback = [entity]() mutable
            {
                if (entity.IsValid())
                {
                    entity.DestroyEntity();
                }
            };
        };

        RegisterFixedUpdateSystem<Scarlet::Component::Transform, Scarlet::Component::Camera, Scarlet::Component::PlayerController>(PlayerControllerSystem);
        RegisterFixedUpdateSystem<Scarlet::Component::Transform, Scarlet::Component::DroneController>(MoveDroneSystem);
        RegisterFixedUpdateSystem<Scarlet::Component::Transform, Scarlet::Component::Bullet>(MoveBulletSystem);

        RegisterSystem<Scarlet::Component::Transform, Scarlet::Component::Camera, Scarlet::Component::Gun>(PlayerGunSystem);
        RegisterSystem<Scarlet::Component::WaveManager>(WaveManagerSystem);
    }

    inline void Destroy() override
    {
        mPlayerEntity.DestroyEntity();
    }
private:
    ScarlEnt::MutableEntityHandle mPlayerEntity;
};

