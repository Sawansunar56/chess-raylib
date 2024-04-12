#include "piece.h"

Piece::Piece(Texture2D &atlus, Rectangle src, Rectangle dest,
             WorldPosition moveElements)
    : m_PieceAtlus(atlus), m_PieceSrcSize(src), m_PieceDestSize(dest),
      m_MoveElements(moveElements)
{
}

void Piece::render(int x, int y)
{
    m_PieceDestSize.x =
        m_MoveElements.positionX +
        (m_MoveElements.pieceGap * x * m_MoveElements.pieceScale);
    m_PieceDestSize.y =
        m_MoveElements.positionY +
        (m_MoveElements.pieceGap * y * m_MoveElements.pieceScale);

    DrawTexturePro(m_PieceAtlus, m_PieceSrcSize, m_PieceDestSize,
                   {(float)-100, (float)0}, (float)0, WHITE);
}
