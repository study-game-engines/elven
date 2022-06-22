#pragma once

#include <Core/StringId.h>
#include <sstream>
#include <string>

namespace Elven::Events {

class Event {
public:
    virtual std::uint32_t GetEventType() const = 0;
    virtual std::string ToString() const { return std::to_string(GetEventType()); };

    bool Handled = false;
};

#define EVENT_TYPE(event_type)                                                  \
    static std::uint32_t GetStaticEventType() { return STRING_ID(event_type); } \
    std::uint32_t GetEventType() const override { return GetStaticEventType(); }

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
    return os << e.ToString();
}

} // namespace Elven::Events
