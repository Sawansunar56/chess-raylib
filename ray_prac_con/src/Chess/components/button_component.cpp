#include "button_component.h"

Button::Button(const std::string &name, Color color, float posx, float posy,
               float roundness)
    : m_Width(100.0f), m_Height(100.0f), m_Color(color), m_Posx(posx),
      m_Roundess(roundness), m_Posy(posy), Layer(name) {}

void Button::Render() {
    DrawRectangleRounded({m_Posx, m_Posy, m_Width, m_Height}, m_Roundess, 10,
                         m_Color);
}
void Button::OnEvent(Event &event) {
    if(containsPoint(GetMouseX(),  GetMouseY())) {
        callbackFunction(event);
        event.m_Handled = true;
    }
}

void Button::SetEventCallback(std::function<void(Event &)> func) {
    callbackFunction = func;
}

