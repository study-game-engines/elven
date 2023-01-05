#include <json.hpp>

#include "Scene.h"

#include "SceneSerializer.h"

#include "Components/SceneComponents.h"
#include "Core/FileSystem.h"
#include "Renderer/Helpers2d.h"

namespace Elven {
using json = nlohmann::json;

void SceneSerializer::Init(Scene* scene)
{
    m_pScene = scene;
}

void SceneSerializer::LoadScene(const std::string& sceneName)
{
    EL_CORE_INFO("Scene loading...");
    json j;
    {
        std::ifstream in(FileSystem::GetScenesPath() + sceneName + ".scene");
        if (in.is_open()) {
            in >> j;
        } else {
            EL_CORE_ERROR("Failed to load scene. File - {0}.scene", sceneName);
            return;
        }
    }

    for (const auto& entityObj : j.at("entities")) {
        const ecs::Entity entity = m_pScene->CreateEntity();
        LoadEntity(entity, entityObj);
    }
    EL_CORE_INFO("Scene loaded");
}

void SceneSerializer::SaveScene(const std::string& sceneName)
{
    std::ofstream out(FileSystem::GetScenesPath() + sceneName + ".scene");
    json j;

    j["name"] = sceneName;

    auto entities = json::array();
    for (ecs::Entity entity : m_pScene->GetEntities()) {
        auto entityObj = json::object();
        SaveEntity(entity, entityObj);
        entities.push_back(entityObj);
    }
    j["entities"] = entities;
    out << std::setfill(' ') << std::setw(2) << j;
}

void SceneSerializer::LoadEntity(ecs::Entity entity, const nlohmann::json& jObj)
{
    auto transform = jObj.at("TransformComponent").get<TransformComponent>();
    auto sprite = jObj.at("SpriteComponent").get<SpriteComponent>();
    m_pScene->AddComponent(entity, std::move(transform));
    m_pScene->AddComponent(entity, std::move(sprite));

    SpriteComponent& spriteComponentRef = m_pScene->GetComponent<SpriteComponent>(entity);
    helpers2d::LoadSprite(spriteComponentRef);
}

void SceneSerializer::SaveEntity(ecs::Entity entity, nlohmann::json& jObj)
{
    if (m_pScene->HasComponent<TransformComponent>(entity)) {

        jObj["TransformComponent"] = m_pScene->GetComponent<TransformComponent>(entity);
    }
    if (m_pScene->HasComponent<SpriteComponent>(entity)) {

        jObj["SpriteComponent"] = m_pScene->GetComponent<SpriteComponent>(entity);
    }
}

} // namespace Elven