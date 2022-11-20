#pragma once

#include "Core/Window.h"
#include "Renderer/GraphicsContext.h"

struct GLFWwindow;
struct GLFWmonitor;

namespace Elven {

class WindowsWindow : public Window {
private:
    struct WindowData {
        std::string Title;
        unsigned int Width { 0 };
        unsigned int Height { 0 };
        bool VSync { false };
        bool FullScreen { false };
    };

public:
    WindowsWindow(const WindowProps& props);
    ~WindowsWindow() override;

    void OnUpdate() override;

    unsigned int GetWidth() const override { return m_data.Width; }
    unsigned int GetHeight() const override { return m_data.Height; }

    void SetVSync(bool enabled) override;
    bool IsVSync() const override;

    void SetFullScreen(bool enabled) override;
    bool IsFullScreen() const override;

    void* GetNativeWindow() const override { return m_window; }

private:
    void Init(const WindowProps& props);
    void Shutdown();

private:
    GLFWwindow* m_window { nullptr };
    GLFWmonitor* m_monitor { nullptr };
    UniquePtr<GraphicsContext> m_context;

    WindowData m_data;
};

} // namespace Elven
