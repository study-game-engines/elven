#include <json.hpp>

#include "SceneComponents.h"

#include "Scene/Behavior.h"

// SpriteComponent
#include "Core/StringId.h"
#include "Events/EventManager.h"
#include "Events/TextureEvent.h"
#include "Renderer/TextureManager.h"

namespace lia {
using json = nlohmann::json;

void to_json(json& j, const lia::vec4& vec)
{
    j["x"] = vec.x;
    j["y"] = vec.y;
    j["z"] = vec.z;
    j["w"] = vec.w;
}

void from_json(const nlohmann::json& j, lia::vec4& vec)
{
    j.at("x").get_to(vec.x);
    j.at("y").get_to(vec.y);
    j.at("z").get_to(vec.z);
    j.at("w").get_to(vec.w);
}

void to_json(json& j, const lia::vec3& vec)
{
    j["x"] = vec.x;
    j["y"] = vec.y;
    j["z"] = vec.z;
}

void from_json(const nlohmann::json& j, lia::vec3& vec)
{
    j.at("x").get_to(vec.x);
    j.at("y").get_to(vec.y);
    j.at("z").get_to(vec.z);
}

void to_json(json& j, const lia::vec2& vec)
{
    j["x"] = vec.x;
    j["y"] = vec.y;
}

void from_json(const nlohmann::json& j, lia::vec2& vec)
{
    j.at("x").get_to(vec.x);
    j.at("y").get_to(vec.y);
}
} // namespace lia

namespace elv {

void to_json(nlohmann::json& j, const TransformComponent& t)
{
    j["position"] = t.pos;
    j["rotation"] = t.rotation;
    j["scale"] = t.scale;
}

void from_json(const nlohmann::json& j, TransformComponent& t)
{
    j.at("position").get_to(t.pos);
    j.at("rotation").get_to(t.rotation);
    j.at("scale").get_to(t.scale);
}

void to_json(nlohmann::json& j, const QuadComponent& t)
{
    j["color"] = t.color;
}

void from_json(const nlohmann::json& j, QuadComponent& t)
{
    j.at("color").get_to(t.color);
}

void to_json(nlohmann::json& j, const SpriteComponent& t)
{
    j["texture_name"] = t.textureName;
    j["texture_path"] = t.texturePath;
}

void from_json(const nlohmann::json& j, SpriteComponent& t)
{
    j.at("texture_name").get_to<std::string>(t.textureName);
    j.at("texture_path").get_to<std::string>(t.texturePath);
}

void SpriteComponent::LoadTexture()
{
    if (!textureName.empty() && !texturePath.empty()) {
        auto texturePtr = textures::Get(textureName);
        if (texturePtr) {
            texture = texturePtr;
        } else {
            textures::Load(textureName, texturePath);

            events::Subscribe<events::TextureLoadedEvent>([&](const events::TextureLoadedEvent& e) {
                if (e.textureName == textureName) {
                    texture = textures::Get(textureName);
                }
            },
                                                          string_id(textureName));
        }
    } else {
        EL_CORE_WARN("Texture loading is failed. Please call SetTexture function first or set members using ctor.")
    }
}
} // namespace elv
