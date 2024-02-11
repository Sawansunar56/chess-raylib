#include <iostream>
#include <string>
#include "game.h"
#include "raylib.h"
#include "Layer.h"

#include "components/button_component.h"

void SetFlags() {
    SetTraceLogLevel(LOG_TRACE);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    // SetTargetFPS(60);
}

void helloFromTrash(Event &e) { std::cout << "HEllo from trash \n"; }

void helloFromshit(Event &e) { std::cout << "HEllo from shit \n"; }

void Run() {
    constexpr int SCREEN_HEIGHT = 720;
    constexpr int SCREEN_WIDTH = 1280;
    SetFlags();
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess");

    // SetWindowState(FLAG_WINDOW_MAXIMIZED);

    LayerManager subject;

    float width = 100, height = 100;

    Texture2D texture = LoadTexture("assets/textures/checkerboard.png");

    Vector2 position = { 0.0f, 0.0f };

    Button *red = new Button("Trash", RED, 100, 100, 0.3f);
    red->SetEventCallback(helloFromTrash);
    Button *yellow = new Button("shit", YELLOW, 400, 100, 0.3f);
    yellow->SetEventCallback(helloFromshit);

    subject.addLayer(red);
    subject.addLayer(yellow);


    while (!WindowShouldClose()) {
        BeginDrawing();

        // Setup Drawing Region
        ClearBackground(RAYWHITE);
        std::string fps = "";
        fps = std::to_string(GetFPS());
        DrawText(fps.c_str(), SCREEN_WIDTH - 100, 10, 20, LIGHTGRAY);

        // Render Region
        float scale = (float)GetScreenHeight() / texture.height;

        DrawTextureEx(texture, position, 0.0f, scale, WHITE);

        subject.renderLayers();

        // Event Handling
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Event testEvent;
            testEvent.type = EventType::MouseClickEvent;
            subject.handleEvent(testEvent);
        }
        EndDrawing();
    }

    CloseWindow();
}
