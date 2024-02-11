#include <iostream>
#include <string>
#include "game.h"
#include "raylib.h"
#include "Layer.h"

void SetFlags() {
    SetTraceLogLevel(LOG_TRACE);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    // SetTargetFPS(60);
}

class DrawRect : public Layer {
  public:
    DrawRect(Color color, float x, float y, const std::string &name)
        : m_Width(100.0f), m_Height(100.0f), m_Color(color), x(x), y(y),
          Layer(name) {}
    virtual void Render() override {
        DrawRectangleRounded({x, y, m_Width, m_Height}, 0.2f, 10, m_Color);
    }
    virtual void OnEvent(Event &event) override {
        handleForBox(event, GetMouseX(), GetMouseY());
    }

    bool containsPoint(int px, int py) {
        return px >= x && px <= x + m_Width && py >= y && py <= y + m_Height;
    }

    void handleForBox(Event &event, int px, int py) {
        if (containsPoint(px, py)) {
            std::cout << "Hello from " << GetName() << std::endl;
            event.m_Handled = true;
        }
    }

  private:
    float m_Width, m_Height;
    float x, y;
    Color m_Color;
};

void Run() {
    SetFlags();
    InitWindow(1280, 720, "Chess");

    // SetWindowState(FLAG_WINDOW_MAXIMIZED);

    LayerManager subject;

    float width = 100, height = 100;
    DrawRect *yellowBox = new DrawRect(GOLD, 100.0f, 80.0f, "Yellow Box");
    DrawRect *redBox = new DrawRect(RED, 150.0f, 200.0f, "Red Box");
    ;

    subject.addLayer(redBox);
    subject.addLayer(yellowBox);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        std::string fps = "";
        fps = std::to_string(GetFPS());
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT)) {
            width += 10.0f;
            TraceLog(LOG_TRACE, "KEY RIGHT: WIDTH: %d", width);
        } else if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)) {
            width -= 10.0f;
            TraceLog(LOG_TRACE, "KEY LEFT: WIDTH: %d", width);
        } else if (IsKeyPressed(KEY_UP) || IsKeyPressedRepeat(KEY_UP)) {
            height -= 10.0f;
            TraceLog(LOG_TRACE, "KEY TOP: WIDTH: %d", width);
        } else if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN)) {
            height += 10.0f;
            TraceLog(LOG_TRACE, "KEY DOWN: WIDTH: %d", width);
        }
        DrawText(fps.c_str(), 400, 200, 20, LIGHTGRAY);

        subject.renderLayers();
        DrawRectangleRounded({10, 10, width, height}, 0.2f, 10,
                             {200, 200, 200, 255});

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Event testEvent;
            testEvent.type = EventType::MouseClickEvent;
            subject.handleEvent(testEvent);
        }
        EndDrawing();
    }

    CloseWindow();
}
