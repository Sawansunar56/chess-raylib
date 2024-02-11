#pragma once

enum class EventType {
    MouseClickEvent,
    KeyPressedEvent,
};

class Event {
public:
    EventType type;
    bool m_Handled = false;
};

