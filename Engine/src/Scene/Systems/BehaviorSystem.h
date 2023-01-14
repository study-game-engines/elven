#pragma once
#include "Scene/ComponentSystem.h"

namespace elv {
class Scene;
/* BehaviorSystem responsible for dispatching engine/game events
(like update, render, input, physics collision detection etc.) to the BehaviorComponent's.
*/
class BehaviorSystem final : public ecs::IComponentSystem {
public:
    BehaviorSystem(Scene* scenePtr);

    void OnShutdown() final override;
    void OnUpdate(float dt) final override;
    void OnRender(float dt) final override;

    // Here may be different eventhandlers (mouse/keyboard inputs, on collision etc.)
};
} // namespace elv
