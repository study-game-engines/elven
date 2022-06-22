#pragma once

#include "Renderer/RendererAPI.h"

namespace Elven {

class OpenGLRendererAPI : public RendererAPI {
    void Init() override;
    void SetViewport(std::uint32_t x, std::uint32_t y, std::uint32_t width, std::uint32_t height) override;

    void SetClearColor(const lia::vec4& color) override;
    void Clear() override;

    void EnableDepthTesting(bool enabled) override;

    void DrawIndexed(const SharedPtr<VertexArray>& vertexArray, std::uint32_t indexCount = 0) override;
};

} // namespace Elven
