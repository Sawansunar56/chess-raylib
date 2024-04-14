#include "game.h"
#include "Events/Events.h"
#include "layer.h"
#include "imgui.h"
#include "rlImGui.h"
#include "play_piece.h"
#include <iostream>
#include <string>

#include "components/button_component.h"

void helloFromTrash(Event &e) { std::cout << "Hello from trash \n"; }

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
    rlImGuiSetup(true);

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

    Color activeColor{0, 0, 255, 50};

    Button *red = new Button("Trash", activeColor, 90, 90, 0.1f);
    red->SetEventCallback(helloFromTrash);

    float kingPositionX = 0.0f, kingPositionY = 0.0f;
    float pawnPositionX = -90.0f, pawnPositionY = -15.0f;
    float width = 100, height = 100, distance = 100;
    float makeScale = .24f;

    Rectangle scaledCoord = {kingPositionX, kingPositionY,
                             PIECE_WIDTH * makeScale, PIECE_HEIGHT * makeScale};

    std::vector<Piece *> renderPieces;
    std::vector<PlayPiece *> playingPieces;

    float x = -90.f, y = -5.f, scaleX = 10, scaleY = 10;
    // Render Region
    float scale      = (float)GetScreenHeight() / boardTexture.height;
    float pieceScale = (float)GetScreenHeight() / (PIECE_HEIGHT * 10);
    float pieceJump  = 440.0f;

    float textureHeight = boardTexture.width * scale,
          textureWidth  = boardTexture.height * scale;

    // to divide the world into equal sections
    WorldPosition moveElements;
    moveElements.positionX  = 0.0f;
    moveElements.positionY  = 0.0f;
    moveElements.pieceJump  = pieceJump;
    moveElements.pieceScale = pieceScale;

    // initialize main board pieces to positions like the enum.
    initBoardPieces(renderPieces, pieceAtlus, pieceCoords, scaledCoord,
                    moveElements);

    // adding element into the screen
    subject.addLayer(red);

    // test render variables
    float losx = 3, losy = 2;
    bool activeMode = false;
    int movePiece   = 0;
    int holdPiece   = -1;
    ActiveRectangle boardGlow;
    boardGlow.rect         = {90.f, 90.f, 90.f, 90.f};
    boardGlow.color        = activeColor;
    boardGlow.moveElements = moveElements;

    float test[4]{0};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        rlImGuiBegin();
        //  Setup Drawing Region
        std::string fps = "";
        fps             = std::to_string(GetFPS());
        DrawText(fps.c_str(), SCREEN_WIDTH - 100, 10, 20, LIGHTGRAY);

        // texture board scaled render
        DrawTextureEx(boardTexture, position, 0.0f, scale, WHITE);

        subject.renderLayers();
        if (activeMode)
        {
            boardGlow.render(losx, losy);
        }

        // board rendering
        for (int i = 0; i < board.size(); i += 8)
        {
            for (int j = i; j < i + 8; ++j)
            {
                int yBoardPos = j / 8;
                int xBoardPos = j % 8;

                if (board[j] != -1)
                {
                    renderPieces[board[j]]->render(xBoardPos - 1, yBoardPos);
                }
            }
        }

        /*ImGui::Begin("Settings");*/
        ImGui::ColorEdit4("Power", test);
        /*ImGui::End();*/

        // test piece rendering
        /*renderPieces[movePiece]->render(losx, losy);*/

        /*if (IsKeyPressed(KEY_A) || IsKeyPressedRepeat(KEY_A))*/
        /*{*/
        /*    pieceGap -= 1;*/
        /*    TraceLog(LOG_INFO,*/
        /*             "width: %f, height: %f , scale: %f, pieceGap: %f, "*/
        /*             "pieceScale",*/
        /*             x, y, scale, pieceGap, pieceScale);*/
        /*}*/
        /*if (IsKeyPressed(KEY_D) || IsKeyPressedRepeat(KEY_D))*/
        /*{*/
        /*    pieceGap += 1;*/
        /*    TraceLog(LOG_INFO,*/
        /*             "width: %f, height: %f , scale: %f, pieceGap:%f, "*/
        /*             "pieceScale",*/
        /*             x, y, scale, pieceGap, pieceScale);*/
        /*}*/
        /*if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT))*/
        /*{*/
        /*    losx -= 1;*/
        /*    TraceLog(LOG_INFO,*/
        /*             "width: %f, height: %f , scale: %f, pieceGap: %f, "*/
        /*             "pieceScale",*/
        /*             x, y, scale, pieceGap, pieceScale);*/
        /*}*/
        /*if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT))*/
        /*{*/
        /*    losx += 1;*/
        /*    TraceLog(LOG_INFO,*/
        /*             "width: %f, height: %f , scale: %f, pieceGap: %f, "*/
        /*             "pieceScale",*/
        /*             x, y, scale, pieceGap, pieceScale);*/
        /*}*/
        /*if (IsKeyPressed(KEY_UP) || IsKeyPressedRepeat(KEY_UP))*/
        /*{*/
        /*    losy -= 1;*/
        /*    TraceLog(LOG_INFO, "width: %f, height: %f ", x, y);*/
        /*}*/
        /*if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN))*/
        /*{*/
        /*    losy += 1;*/
        /*    TraceLog(LOG_INFO, "width: %f, height: %f ", x, y);*/
        /*}*/

        // Event Handling
        /*if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))*/
        /*{*/
        /*    Event testEvent;*/
        /*    testEvent.type = EventType::MouseClickEvent;*/
        /*    subject.handleEvent(testEvent);*/
        /*}*/

        // handles clicking and then switching between active mode and passive
        // mode
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (GetMouseX() > 0 && GetMouseX() < textureWidth)
            {
                int numX = (GetMouseX() / 90);
                int numY = (GetMouseY() / 90);

                if (!activeMode)
                {
                    // equation to convert x y position to board position.
                    int cursorBoardPos = numX + (numY * 8);
                    TraceLog(LOG_INFO, "MouseX: %d, MouseY: %d, SingleNum: %d",
                             numX, numY, cursorBoardPos);
                    movePiece  = cursorBoardPos;
                    holdPiece  = board[movePiece];
                    losx       = numX;
                    losy       = numY;
                    activeMode = !activeMode;
                } else
                {
                    if (holdPiece != -1)
                    {
                        TraceLog(LOG_INFO, "MouseX: %d, MouseY: %d", numX,
                                 numY);
                        // equation to convert x y position to board position.
                        int cursorBoardPos    = numX + (numY * 8);
                        board[cursorBoardPos] = holdPiece;
                        board[movePiece]      = -1;
                    }
                    activeMode = !activeMode;
                }
            }
        }
        rlImGuiEnd();
        EndDrawing();
    }
    rlImGuiShutdown();

    CloseWindow();
}

void initBoardPieces(std::vector<Piece *> &renderPieces, Texture2D pieceAtlus,
                     Rectangle *pieceCoords, Rectangle scaledCoord,
                     WorldPosition moveElements)
{
    renderPieces.push_back(new Piece(pieceAtlus, pieceCoords[WHITE_PIECE_ROOK],
                                     scaledCoord, moveElements));
    renderPieces.push_back(new Piece(pieceAtlus,
                                     pieceCoords[WHITE_PIECE_KNIGHT],
                                     scaledCoord, moveElements));
    renderPieces.push_back(new Piece(pieceAtlus,
                                     pieceCoords[WHITE_PIECE_BISHOP],
                                     scaledCoord, moveElements));
    renderPieces.push_back(new Piece(pieceAtlus, pieceCoords[WHITE_PIECE_QUEEN],
                                     scaledCoord, moveElements));
    renderPieces.push_back(new Piece(pieceAtlus, pieceCoords[WHITE_PIECE_KING],
                                     scaledCoord, moveElements));
    renderPieces.push_back(new Piece(pieceAtlus,
                                     pieceCoords[WHITE_PIECE_BISHOP],
                                     scaledCoord, moveElements));
    renderPieces.push_back(new Piece(pieceAtlus,
                                     pieceCoords[WHITE_PIECE_KNIGHT],
                                     scaledCoord, moveElements));
    renderPieces.push_back(new Piece(pieceAtlus, pieceCoords[WHITE_PIECE_ROOK],
                                     scaledCoord, moveElements));

    for (int i = 0; i < 8; i++)
    {
        renderPieces.push_back(new Piece(pieceAtlus,
                                         pieceCoords[WHITE_PIECE_PAWN],
                                         scaledCoord, moveElements));
    }
    for (int i = 0; i < 8; i++)
    {
        renderPieces.push_back(new Piece(pieceAtlus,
                                         pieceCoords[BLACK_PIECE_PAWN],
                                         scaledCoord, moveElements));
    }

    renderPieces.push_back(new Piece(pieceAtlus, pieceCoords[BLACK_PIECE_ROOK],
                                     scaledCoord, moveElements));
    renderPieces.push_back(new Piece(pieceAtlus,
                                     pieceCoords[BLACK_PIECE_KNIGHT],
                                     scaledCoord, moveElements));
    renderPieces.push_back(new Piece(pieceAtlus,
                                     pieceCoords[BLACK_PIECE_BISHOP],
                                     scaledCoord, moveElements));
    renderPieces.push_back(new Piece(pieceAtlus, pieceCoords[BLACK_PIECE_QUEEN],
                                     scaledCoord, moveElements));
    renderPieces.push_back(new Piece(pieceAtlus, pieceCoords[BLACK_PIECE_KING],
                                     scaledCoord, moveElements));
    renderPieces.push_back(new Piece(pieceAtlus,
                                     pieceCoords[BLACK_PIECE_BISHOP],
                                     scaledCoord, moveElements));
    renderPieces.push_back(new Piece(pieceAtlus,
                                     pieceCoords[BLACK_PIECE_KNIGHT],
                                     scaledCoord, moveElements));
    renderPieces.push_back(new Piece(pieceAtlus, pieceCoords[BLACK_PIECE_ROOK],
                                     scaledCoord, moveElements));
}

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

void SetFlags()
{
    SetTraceLogLevel(LOG_TRACE);
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);
}
