#pragma once

#include "raylib.h"
#include "piece.h"
#include <vector>

void SetFlags();
void initBoard(std::vector<int> &board);
void Run();
void initBoardPieces(std::vector<Piece *> &renderPieces, Texture2D pieceAtlus,
                     Rectangle *pieceCoords, Rectangle scaledCoord,
                     WorldPosition moveElements);

struct ActiveRectangle
{
    Rectangle rect;
    Color color;
    WorldPosition moveElements;
    void render(int x, int y)
    {
        rect.x = moveElements.positionX + (x * 90);
        rect.y = moveElements.positionY + (y * 90);
        DrawRectangleRounded(rect, 0.1f, 10, color);
    }
};
