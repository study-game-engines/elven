#include <Elven.h>

#include "SandboxApp.h"

#include <Core/SettingsConfig.h>
#include <Events/TextureEvent.h>

elv::Application* elv::CreateApplication()
{
    return new Sandbox2D();
}

class TestBehavior : public elv::ecs::IBehavior {
public:
    void OnCreate() override
    {
        EL_INFO("OnCreate of Behavior component...");
    }

    void OnDestroy() override
    {
        EL_INFO("OnDestroy of Behavior component...");
    }

    void OnUpdate(float dt) override
    {
        EL_INFO("OnUpdate of Behavior component...");
    }

    void OnRender(float dt) override
    {
        EL_INFO("OnRender of Behavior component...");
    }
};

Sandbox2D::Sandbox2D()
    : m_textureLoadedCallback([this](const elv::events::TextureLoadedEvent& e) { OnTextureLoaded(e); })
    , m_cameraController(static_cast<float>(elv::gEngineSettings.windowWidth) / static_cast<float>(elv::gEngineSettings.windowHeight))
{
}

void Sandbox2D::OnCreate()
{
    if (!elv::gEngineSettings.loadDefaultScene) {
        elv::events::Subscribe<elv::events::TextureLoadedEvent>(m_textureLoadedCallback, elv::string_id("wizard"));
        elv::events::Subscribe<elv::events::TextureLoadedEvent>(m_textureLoadedCallback, elv::string_id("wizard_fire"));
        elv::events::Subscribe<elv::events::TextureLoadedEvent>(m_textureLoadedCallback, elv::string_id("wizard_ice"));

        std::vector<std::pair<std::string, std::string>> texturesLoadList = {
            { "wizard", "wizard.png" },
            { "wizard_fire", "wizard_fire.png" },
            { "wizard_ice", "wizard_ice.png" }
        };

        for (size_t i = 0; i < texturesLoadList.size(); i++) {
            elv::textures::Load(texturesLoadList[i].first, texturesLoadList[i].second);
        }
    }

    return;
    // another test scene
    elv::Scene& scene = elv::GetScene();

    const elv::ecs::Entity back_entity = scene.CreateEntity();
    auto& back_sprite = scene.AddComponent<elv::SpriteComponent>(back_entity);
    back_sprite.SetTexture("battleground2", "Battleground2.png");
    auto& back_transform = scene.AddComponent<elv::TransformComponent>(back_entity);
    back_transform.scale = { 384.0f, 216.0f, 1.0f };

    const elv::ecs::Entity skeleton_entity = scene.CreateEntity();
    auto& skeleton_sprite = scene.AddComponent<elv::SpriteComponent>(skeleton_entity);
    skeleton_sprite.SetTexture("protect", "Protect.png");
    auto& skeleton_transform = scene.AddComponent<elv::TransformComponent>(skeleton_entity);
    skeleton_transform.scale = { 100.0f, 100.0f, 1.0f };
    skeleton_transform.pos = { 0.0f, -25.0f, 0.0f };

    const elv::ecs::Entity magic_entity = scene.CreateEntity();
    auto& magic_sprite = scene.AddComponent<elv::SpriteComponent>(magic_entity);
    magic_sprite.SetTexture("magic_sphere", "Magic_sphere.png");
    auto& magic_transform = scene.AddComponent<elv::TransformComponent>(magic_entity);
    magic_transform.scale = { 1600.0f, 100.0f, 1.0f };
    magic_transform.pos = { 0.0, -25.0f, 0.0f };
}

void Sandbox2D::OnUpdate(float dt)
{
    m_cameraController.OnUpdate(dt);
}

void Sandbox2D::OnRender(float dt)
{
}

void Sandbox2D::OnDestroy()
{
}

void Sandbox2D::OnTextureLoaded(const elv::events::TextureLoadedEvent& e)
{
    if (e.textureName == "wizard_fire") {

        elv::Scene& scene = elv::GetScene();

        const elv::SharedPtr<elv::Texture2D> texture = elv::textures::Get("wizard_fire");

        for (size_t i = 0; i < 10; ++i) {
            for (size_t j = 0; j < 10; ++j) {
                const elv::ecs::Entity entityQuad = scene.CreateEntity();

                auto& transform = scene.AddComponent<elv::TransformComponent>(
                    entityQuad,
                    lia::vec3(static_cast<float>(i) * 13.0f, static_cast<float>(j) * 13.0f, 0.0f),
                    lia::vec3(10.0f, 10.0f, 1.0f));

                auto& sprite = scene.AddComponent<elv::SpriteComponent>(entityQuad, "wizard_fire", "wizard_fire.png");
                sprite.texture = texture;

                if (true && j == 0 && i == 0) {
                    scene.AddComponent<elv::BehaviorComponent>(entityQuad).Bind<TestBehavior>();
                }
            }
        }
    }
}
