#include <iostream>
#include <string>
#include <vector>
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

void helloFromTrash(Event &e) { std::cout << "Hello from trash \n"; }

void helloFromshit(Event &e) { std::cout << "Hello from shit \n"; }

// pieces for rendering from the atlus
enum pieces {
    WHITE_PIECE_ROOK,
    WHITE_PIECE_BISHOP,
    WHITE_PIECE_QUEEN,
    WHITE_PIECE_KING,
    WHITE_PIECE_KNIGHT,
    WHITE_PIECE_PAWN,
    BLACK_PIECE_ROOK,
    BLACK_PIECE_BISHOP,
    BLACK_PIECE_QUEEN,
    BLACK_PIECE_KING,
    BLACK_PIECE_KNIGHT,
    BLACK_PIECE_PAWN,
    P_NUM,
};

// 32 pieces on the board
enum boardPiece {
    WHITE_ROOK_LEFT,
    WHITE_KNIGHT_LEFT,
    WHITE_BISHOP_LEFT,
    WHITE_QUEEN,
    WHITE_KING,
    WHITE_BISHOP_RIGHT,
    WHITE_KNIGHT_RIGHT,
    WHITE_ROOK_RIGHT,
    WHITE_PAWN_ONE,
    WHITE_PAWN_TWO,
    WHITE_PAWN_THREE,
    WHITE_PAWN_FOUR,
    WHITE_PAWN_FIVE,
    WHITE_PAWN_SIX,
    WHITE_PAWN_SEVEN,
    WHITE_PAWN_EIGHT,
    BLACK_ROOK_LEFT,
    BLACK_KNIGHT_LEFT,
    BLACK_BISHOP_LEFT,
    BLACK_QUEEN,
    BLACK_KING,
    BLACK_BISHOP_RIGHT,
    BLACK_KNIGHT_RIGHT,
    BLACK_ROOK_RIGHT,
    BLACK_PAWN_ONE,
    BLACK_PAWN_TWO,
    BLACK_PAWN_THREE,
    BLACK_PAWN_FOUR,
    BLACK_PAWN_FIVE,
    BLACK_PAWN_SIX,
    BLACK_PAWN_SEVEN,
    BLACK_PAWN_EIGHT,
};

void initBoard(std::vector<int> &board) {
    int i = 0, j = WHITE_ROOK_LEFT;
    while (i < 16) {
        board[i] = j;
        i++;
    }
    i += 32;
    while (i < 64) {
        i++;
    }
}

void Run() {
    // constants
    constexpr int SCREEN_HEIGHT = 720;
    constexpr int SCREEN_WIDTH = 1280;
    constexpr int PIECE_WIDTH = 305;
    constexpr int PIECE_HEIGHT = 350;
    std::vector<int> board(8 * 8, -1);

    SetFlags();
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess");
    initBoard(board);

    LayerManager subject;

    Texture2D boardTexture = LoadTexture("assets/textures/checkerboard.png");
    Texture2D pieceAtlus = LoadTexture("assets/textures/pieces.png");

    Rectangle pieceCoords[P_NUM];

    // assigning piece coordinates to pieceCoords array
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

    float width = 100, height = 100, distance = 100;
    float scale = .24f;
    Rectangle destSrc = {0, 0, PIECE_WIDTH * scale, PIECE_HEIGHT * scale};
    Rectangle destSrc2 = {-90, -15, PIECE_WIDTH * scale, PIECE_HEIGHT * scale};

    Piece rook(pieceAtlus, pieceCoords[WHITE_PIECE_ROOK], destSrc);
    Piece pawn(pieceAtlus, pieceCoords[BLACK_PIECE_PAWN], destSrc2);
    Piece king(pieceAtlus, pieceCoords[WHITE_PIECE_KING], destSrc);

    // adding element into the screen
    subject.addLayer(red);
    subject.addLayer(yellow);

    float x = -80, y = -5, scaleX = 10, scaleY = 10;

    float pieceGap = 440.0f;
    while (!WindowShouldClose()) {
        BeginDrawing();

        // Setup Drawing Region
        ClearBackground(RAYWHITE);
        std::string fps = "";
        fps = std::to_string(GetFPS());
        DrawText(fps.c_str(), SCREEN_WIDTH - 100, 10, 20, LIGHTGRAY);

        // Render Region
        float scale = (float)GetScreenHeight() / boardTexture.height;
        float pieceScale = (float)GetScreenHeight() / (PIECE_HEIGHT * 10);

        DrawTextureEx(boardTexture, position, 0.0f, scale, WHITE);

        subject.renderLayers();

        // TODO: Scale seems to be working fine but placement seems to be doing 
        // the most problem. When a window resize occurs, it causes the pieces 
        // to move either a little bit left or right.
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                king.render(x + (pieceGap * i * pieceScale),
                            y + (pieceGap * j * pieceScale),
                            PIECE_WIDTH * pieceScale,
                            PIECE_HEIGHT * pieceScale);
            }
        }

        if (IsKeyPressed(KEY_A) || IsKeyPressedRepeat(KEY_A)) {
            pieceGap -= 1;
            TraceLog(
                LOG_INFO,
                "width: %f, height: %f , scale: %f, pieceGap: %f, pieceScale",
                x, y, scale, pieceGap, pieceScale);
        }
        if (IsKeyPressed(KEY_D) || IsKeyPressedRepeat(KEY_D)) {
            pieceGap += 1;
            TraceLog(
                LOG_INFO,
                "width: %f, height: %f , scale: %f, pieceGap:%f, pieceScale", x,
                y, scale, pieceGap, pieceScale);
        }
        if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)) {
            x -= 1;
            TraceLog(
                LOG_INFO,
                "width: %f, height: %f , scale: %f, pieceGap: %f, pieceScale",
                x, y, scale, pieceGap, pieceScale);
        }
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT)) {
            x += 1;
            TraceLog(
                LOG_INFO,
                "width: %f, height: %f , scale: %f, pieceGap: %f, pieceScale",
                x, y, scale, pieceGap, pieceScale);
        }
        if (IsKeyPressed(KEY_UP) || IsKeyPressedRepeat(KEY_UP)) {
            y -= 1;
            TraceLog(LOG_INFO, "width: %f, height: %f ", x, y);
        }
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN)) {
            y += 1;
            TraceLog(LOG_INFO, "width: %f, height: %f ", x, y);
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
