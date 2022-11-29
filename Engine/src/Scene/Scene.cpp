#include "Scene.h"
#include "Entity.h"

#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer2D.h"
#include "Renderer/TextureManager.h"

#include "Core/Timer.h"

#include "Events/EventManager.h"
#include "Events/TextureEvent.h"

namespace Elven {

struct TransformComponent {
    lia::vec3 pos { 0.0f, 0.0f, 0.0f };
    lia::vec2 scale { 1.0f, 1.0f };
    lia::vec3 rotation { 0.0f, 0.0f, 0.0f };
};

struct SpriteComponent {
    Elven::SharedPtr<Elven::Texture2D> m_texture;
};

Scene::Scene()
    : m_cameraController(1280.0f / 720.0f)
    , m_textureLoadedCallback([this](const events::TextureLoadedEvent& e) { OnTextureLoaded(e); })
{
    events::Subscribe<events::TextureLoadedEvent>(m_textureLoadedCallback);
}

void Scene::Init()
{
    std::vector<std::pair<std::string, std::string>> texturesLoadList = {
        { "wizard", "wizard.png" },
        { "wizard_fire", "wizard_fire.png" },
        { "wizard_ice", "wizard_ice.png" }
    };

    for (size_t i = 0; i < texturesLoadList.size(); i++) {
        textures::Load(std::move(texturesLoadList[i].first), texturesLoadList[i].second);
    }
}

void Scene::Shutdown()
{
    m_world.OnShutdown();
}

void Scene::OnUpdate(float dt)
{
    m_cameraController.OnUpdate(dt);
}

void Scene::OnRender(float dt)
{
    Elven::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
    Elven::RenderCommand::Clear();

    Elven::Renderer2D::BeginScene(m_cameraController.GetCamera());

    if (m_world.HasComponents<TransformComponent>()) {
        auto transformComponents = m_world.GetComponents<TransformComponent>();
        for (std::uint32_t index = 0; index < transformComponents.size(); ++index) {
            const ecs::EntityId entityid = m_world.GetEntity<TransformComponent>(index);

            auto transformComponent = transformComponents[index];
            if (m_world.HasComponent<SpriteComponent>(entityid)) {
                auto spriteComponent = m_world.GetComponent<SpriteComponent>(entityid);
                Elven::Renderer2D::DrawQuad(spriteComponent.m_texture, transformComponent.pos, transformComponent.scale, 45.0f);
            } else {
                Elven::Renderer2D::DrawQuad(transformComponent.pos, transformComponent.scale, 0.0f, { 0.5f, 0.5f, 0.2f, 1.0f });
            }
        }
    }

    Elven::Renderer2D::EndScene();
}

void Scene::OnTextureLoaded(const events::TextureLoadedEvent& e)
{
    if (e.textureName == "wizard_fire") {

        SharedPtr<Texture2D> texture = textures::Get("wizard_fire");

        for (size_t i = 0; i < 100; ++i) {
            for (size_t j = 0; j < 200; ++j) {

                ecs::EntityId entityQuad = m_world.CreateEntity();

                m_world.AddComponent<TransformComponent>(entityQuad);
                m_world.AddComponent<SpriteComponent>(entityQuad);

                auto& q2 = m_world.GetComponent<TransformComponent>(entityQuad);
                q2.pos = { 0.0f + static_cast<float>(i * 0.3), 0.0f + static_cast<float>(j * 0.3), 0.0f };
                q2.scale = { 0.25f, 0.225f };

                auto& sprite = m_world.GetComponent<SpriteComponent>(entityQuad);
                sprite.m_texture = texture;
            }
        }
    }
}

} // namespace Elven
