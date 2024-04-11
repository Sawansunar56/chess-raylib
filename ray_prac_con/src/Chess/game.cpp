#include "game.h"
#include "Events/Events.h"
#include "layer.h"
#include "piece.h"
#include "raylib.h"
#include <iostream>
#include <string>
#include <vector>

#include "components/button_component.h"

void SetFlags()
{
    SetTraceLogLevel(LOG_TRACE);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    // SetTargetFPS(60);
}

void helloFromTrash(Event &e) { std::cout << "Hello from trash \n"; }

void helloFromshit(Event &e) { std::cout << "Hello from shit \n"; }

void initBoard(std::vector<int> &board)
{
    int i = 0, j = WHITE_ROOK_LEFT;
    while (i < 16)
    {
        board[i] = j;
        i++;
        j++;
    }
    i += 32;
    while (i < 64)
    {
        board[i] = j;
        j++;
        i++;
    }
}

void Run()
{
    // constants
    constexpr int SCREEN_HEIGHT = 720;
    constexpr int SCREEN_WIDTH  = 1280;
    constexpr int PIECE_WIDTH   = 305;
    constexpr int PIECE_HEIGHT  = 350;
    std::vector<int> board(8 * 8, -1);

    // init
    SetFlags();
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess");
    initBoard(board);

    LayerManager subject;
    Rectangle pieceCoords[P_NUM];

    // load textures
    Texture2D boardTexture = LoadTexture("assets/textures/checkerboard.png");
    Texture2D pieceAtlus   = LoadTexture("assets/textures/pieces.png");

    // assigning piece coordinates to pieceCoords array
    for (int i = 0; i < P_NUM / 2; i++)
    {
        pieceCoords[i].x      = i * PIECE_WIDTH;
        pieceCoords[i].y      = 0;
        pieceCoords[i].width  = PIECE_WIDTH;
        pieceCoords[i].height = PIECE_HEIGHT;
    }
    for (int i = 6; i < P_NUM; i++)
    {
        pieceCoords[i].x      = (i - 6) * PIECE_WIDTH;
        pieceCoords[i].y      = PIECE_HEIGHT;
        pieceCoords[i].width  = PIECE_WIDTH;
        pieceCoords[i].height = PIECE_HEIGHT;
    }

    Vector2 position = {0.0f, 0.0f};

    Button *red = new Button("Trash", RED, 100, 100, 0.3f);
    red->SetEventCallback(helloFromTrash);
    Button *yellow = new Button("shit", YELLOW, 400, 100, 0.3f);
    yellow->SetEventCallback(helloFromshit);

    float kingPositionX = 0.0f, kingPositionY = 0.0f;
    float pawnPositionX = -90.0f, pawnPositionY = -15.0f;
    float width = 100, height = 100, distance = 100;
    float scale = .24f;

    Rectangle scaledCoord  = {kingPositionX, kingPositionY, PIECE_WIDTH * scale,
                              PIECE_HEIGHT * scale};
    Rectangle scaledCoord2 = {pawnPositionX, pawnPositionY, PIECE_WIDTH * scale,
                              PIECE_HEIGHT * scale};

    std::vector<Piece *> renderPieces;
    std::vector<int> playingPieces;

    for (int i = 0; i < P_NUM; ++i)
    {
        renderPieces.push_back(
            new Piece(pieceAtlus, pieceCoords[i], scaledCoord));
    }

    // adding element into the screen
    subject.addLayer(red);
    subject.addLayer(yellow);

    float x = -85, y = -5, scaleX = 10, scaleY = 10;

    float pieceGap = 440.0f;
    while (!WindowShouldClose())
    {
        BeginDrawing();

        // Setup Drawing Region
        ClearBackground(RAYWHITE);
        std::string fps = "";
        fps             = std::to_string(GetFPS());
        DrawText(fps.c_str(), SCREEN_WIDTH - 100, 10, 20, LIGHTGRAY);

        // Render Region
        float scale      = (float)GetScreenHeight() / boardTexture.height;
        float pieceScale = (float)GetScreenHeight() / (PIECE_HEIGHT * 10);

        DrawTextureEx(boardTexture, position, 0.0f, scale, WHITE);

        subject.renderLayers();

        // TODO: Scale seems to be working fine but placement seems to be
        // doing the most problem. When a window resize occurs, it causes
        // the pieces to move either a little bit left or right.
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                renderPieces[WHITE_PIECE_ROOK]->render(x + (pieceGap * i * pieceScale),
                                 y + (pieceGap * j * pieceScale),
                                 PIECE_WIDTH * pieceScale,
                                 PIECE_HEIGHT * pieceScale);
            }
        }
        renderPieces[BLACK_PIECE_QUEEN]->render(x + (pieceGap * 1 * pieceScale),
                         y + (pieceGap * 0 * pieceScale),
                         PIECE_WIDTH * pieceScale, PIECE_HEIGHT * pieceScale);

        for (int i = 0; i < board.size(); i += 8)
        {
            for (int j = i; j < i + 8; ++j)
            {
                std::cout << board[j] << " ";
            }
            std::cout << "\n";
        }

        if (IsKeyPressed(KEY_A) || IsKeyPressedRepeat(KEY_A))
        {
            pieceGap -= 1;
            TraceLog(LOG_INFO,
                     "width: %f, height: %f , scale: %f, pieceGap: %f, "
                     "pieceScale",
                     x, y, scale, pieceGap, pieceScale);
        }
        if (IsKeyPressed(KEY_D) || IsKeyPressedRepeat(KEY_D))
        {
            pieceGap += 1;
            TraceLog(LOG_INFO,
                     "width: %f, height: %f , scale: %f, pieceGap:%f, "
                     "pieceScale",
                     x, y, scale, pieceGap, pieceScale);
        }
        if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT))
        {
            x -= 1;
            TraceLog(LOG_INFO,
                     "width: %f, height: %f , scale: %f, pieceGap: %f, "
                     "pieceScale",
                     x, y, scale, pieceGap, pieceScale);
        }
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT))
        {
            x += 1;
            TraceLog(LOG_INFO,
                     "width: %f, height: %f , scale: %f, pieceGap: %f, "
                     "pieceScale",
                     x, y, scale, pieceGap, pieceScale);
        }
        if (IsKeyPressed(KEY_UP) || IsKeyPressedRepeat(KEY_UP))
        {
            y -= 1;
            TraceLog(LOG_INFO, "width: %f, height: %f ", x, y);
        }
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN))
        {
            y += 1;
            TraceLog(LOG_INFO, "width: %f, height: %f ", x, y);
        }

        // Event Handling
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Event testEvent;
            testEvent.type = EventType::MouseClickEvent;
            subject.handleEvent(testEvent);
        }
        EndDrawing();
    }

    CloseWindow();
}
