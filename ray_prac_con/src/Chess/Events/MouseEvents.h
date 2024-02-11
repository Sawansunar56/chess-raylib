#include "Events.h"

class MousePressedEvent : public Event {
    public:
        MousePressedEvent(int x, int y) :  m_MouseX(x), m_MouseY(y) {}
    private:
        int m_MouseX, m_MouseY;
};
