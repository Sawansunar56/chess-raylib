#pragma once

#include "raylib.h"

class Piece {
  public:
    Piece(Texture2D &atlus, Rectangle src, Rectangle dest);
    void render();
    void render(int x, int y);
    void render(int x, int y, int width, int height);

  private:
    Rectangle m_PieceDestSize;
    Rectangle m_PieceSrcSize;
    Texture2D &m_PieceAtlus;
};

