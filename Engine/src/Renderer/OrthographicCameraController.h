#pragma once

#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Renderer/Camera.h"

#include "Events/EventHandler.h"

namespace Elven {

class OrthographicCameraController {
public:
    OrthographicCameraController(float aspectRatio);
    ~OrthographicCameraController() = default;

    void OnUpdate(float dt);

    Camera& GetCamera() { return m_camera; }
    const Camera& GetCamera() const { return m_camera; }

    void SetZoomLevel(float zoomLevel) { m_zoomLevel = zoomLevel; }
    float GetZoomLevel() const { return m_zoomLevel; }

private:
    void OnMouseScrolled(const events::MouseScrolledEvent& e);
    void OnWindowResized(const events::WindowResizeEvent& e);

private:
    lia::vec3 m_position;

    float m_aspectRatio { 0.0f };
    float m_zoomLevel { 1.0f };
    float m_rotation { 0.0f };
    float m_translationSpeed { 5.0f };
    float m_rotationSpeed { 180.0f };

    Camera m_camera;

    events::EventHandler<events::WindowResizeEvent> m_windowResizeCallback;
    events::EventHandler<events::MouseScrolledEvent> m_mouseScrolledCallback;
};

} // namespace Elven
