#pragma once

#include "raylib.h"

class Piece {
  public:
    Piece(Texture2D &atlus, Rectangle src, Rectangle dest);
    virtual void render();

  protected:
    Rectangle m_PieceDestSize;
    Rectangle m_PieceSrcSize;
    Texture2D &m_PieceAtlus;
};

