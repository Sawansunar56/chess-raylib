#include <iostream>
#include <string>
#include "game.h"
#include "raylib.h"
#include "layer.h"
#include "Events/Events.h"
#include "piece.h"

#include "components/button_component.h"

void SetFlags() {
    SetTraceLogLevel(LOG_TRACE);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    // SetTargetFPS(60);
}

void helloFromTrash(Event &e) { std::cout << "HEllo from trash \n"; }

void helloFromshit(Event &e) { std::cout << "HEllo from shit \n"; }

enum pieces {
    WHITE_PIECE_ROOK,
    WHITE_PIECE_BISHOP,
    WHITE_PIECE_QUEEN,
    WHITE_PIECE_KING,
    WHITE_PIECE_KNIGHTS,
    WHITE_PIECE_PAWN,
    BLACK_PIECE_ROOK,
    BLACK_PIECE_BISHOP,
    BLACK_PIECE_QUEEN,
    BLACK_PIECE_KING,
    BLACK_PIECE_KNIGHTS,
    BLACK_PIECE_PAWN,
    P_NUM,
};

void Run() {
    // constants
    constexpr int SCREEN_HEIGHT = 720;
    constexpr int SCREEN_WIDTH = 1280;
    constexpr int PIECE_WIDTH = 305;
    constexpr int PIECE_HEIGHT = 350;

    SetFlags();
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess");

    LayerManager subject;

    Texture2D texture = LoadTexture("assets/textures/checkerboard.png");
    Texture2D pieceAtlus = LoadTexture("assets/textures/pieces.png");

    Rectangle pieceCoords[P_NUM];

    for (int i = 0; i < P_NUM / 2; i++) {
        pieceCoords[i].x = i * PIECE_WIDTH;
        pieceCoords[i].y = 0;
        pieceCoords[i].width = PIECE_WIDTH;
        pieceCoords[i].height = PIECE_HEIGHT;
    }
    for (int i = 6; i < P_NUM; i++) {
        pieceCoords[i].x = (i - 6) * PIECE_WIDTH;
        pieceCoords[i].y = PIECE_HEIGHT;
        pieceCoords[i].width = PIECE_WIDTH;
        pieceCoords[i].height = PIECE_HEIGHT;
    }

    Vector2 position = {0.0f, 0.0f};

    Button *red = new Button("Trash", RED, 100, 100, 0.3f);
    red->SetEventCallback(helloFromTrash);
    Button *yellow = new Button("shit", YELLOW, 400, 100, 0.3f);
    yellow->SetEventCallback(helloFromshit);

    subject.addLayer(red);
    subject.addLayer(yellow);

    float width = 100, height = 100, distance = 100;
    float scale = .24f;
    Rectangle destSrc = {0, 0, PIECE_WIDTH * scale, PIECE_HEIGHT * scale};

    Piece rook(pieceAtlus, pieceCoords[WHITE_PIECE_ROOK], destSrc);
    Piece pawn(pieceAtlus, pieceCoords[BLACK_PIECE_PAWN], destSrc);

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

        // for (int i = 0; i < P_NUM / 2; i++) {
        //     DrawTexturePro(pieceAtlus, pieceCoords[i], destSrc,
        //                    {(float)i * -100, (float)0}, (float)0, WHITE);
        // }
        // for (int i = 6; i < P_NUM; i++) {
        //     DrawTexturePro(pieceAtlus, pieceCoords[i], destSrc,
        //                    {(float)(i - 6) * -100, (float)-100}, (float)0,
        //                    WHITE);
        // }
        rook.render();
        pawn.render();

        if (IsKeyPressed(KEY_LEFT)) {
            width -= 10;
            TraceLog(LOG_INFO, "width: %f, height: %f", width, height);
        }

        if (IsKeyPressed(KEY_RIGHT)) {
            width += 10;
            TraceLog(LOG_INFO, "width: %f, height: %f", width, height);
        }

        if (IsKeyPressed(KEY_UP)) {
            height -= 10;
            TraceLog(LOG_INFO, "width: %f, height: %f", width, height);
        }
        if (IsKeyPressed(KEY_DOWN)) {
            height += 10;
            TraceLog(LOG_INFO, "width: %f, height: %f", width, height);
        }
        if (IsKeyPressed(KEY_A)) {
            distance -= 10;
        }
        if (IsKeyPressed(KEY_D)) {
            distance += 10;
        }

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
