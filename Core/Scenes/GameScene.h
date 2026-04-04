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
#include <ScarletCoreEcs/Components/DirectionLight.h>

class GameScene : public ScarlEnt::Scene
{
public:
    inline GameScene(const std::string_view friendlyName) : Scene(friendlyName) { }

    inline void Init() override final
    {
        // Register the engine systems. Leave this for default engine systems such as rendering, physics etc..
        Scarlet::Engine::Instance().RegisterEngineSystems(Scarlet::WeakHandle<Scene>{ this });

        mCameraEntity = AddMutableEntity();
#ifdef DEV_CONFIGURATION
        auto& info     = mCameraEntity.AddComponent<Scarlet::Component::EditorInfo>();
        info.isMutable = true;
        info.name      = "PlayerEntity";
#endif // DEV_CONFIGURATION.
        mCameraEntity.AddComponent<Scarlet::Component::Transform>();
        mCameraEntity.AddComponent<Scarlet::Component::Camera>();
        mCameraEntity.AddComponent<Scarlet::Component::DirectionLight>();
        auto& pc = mCameraEntity.AddComponent<Scarlet::Component::PlayerController>();
        pc.speed = 0.05f;

        SetCameraEntityHandle(&mCameraEntity);

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

        RegisterSystem<Scarlet::Component::Transform, Scarlet::Component::Camera, Scarlet::Component::PlayerController>(PlayerControllerSystem);
    }

    inline void Destroy() override
    {
        mCameraEntity.DestroyEntity();
    }
private:
    ScarlEnt::MutableEntityHandle mCameraEntity;
};

