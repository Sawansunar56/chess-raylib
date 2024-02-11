#pragma once

#include <functional>
#include <iostream>
#include "raylib.h"
#include "layer.h"

class Button : public Layer {
  public:
    Button(const std::string &name, Color color, float posx, float posy,
           float roundness = 0.0f);

    virtual void Render() override;
    virtual void OnEvent(Event &event) override;
    void SetEventCallback(std::function<void(Event &)> func);

  private:
    bool containsPoint(int px, int py) {
        return px >= m_Posx && px <= m_Posx + m_Width && py >= m_Posy &&
               py <= m_Posy + m_Height;
    }

  private:
    float m_Width, m_Height;
    float m_Posx, m_Posy, m_Roundess;
    Color m_Color;
    std::function<void(Event &)> callbackFunction;
};
