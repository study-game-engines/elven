#include "Texture2D.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"
#include "Renderer/Renderer.h"

#include "Core/FileSystem.h"

namespace Elven {
SharedPtr<Texture2D> Texture2D::Create(const std::string& filename)
{
    const std::string filepath = FileSystem::GetImagesPath() + filename;

    switch (Renderer::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return MakeSharedPtr<OpenGLTexture2D>(filepath);
    }

    EL_CORE_ASSERT(false, "Unknown Renderer API!");

    return nullptr;
}

SharedPtr<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return MakeSharedPtr<OpenGLTexture2D>(width, height);
    }

    EL_CORE_ASSERT(false, "Unknown Renderer API!");

    return nullptr;
}

} // namespace Elven
