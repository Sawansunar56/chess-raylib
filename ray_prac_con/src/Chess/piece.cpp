#include "piece.h"

Piece::Piece(Texture2D &atlus, Rectangle src, Rectangle dest)
    : m_PieceAtlus(atlus), m_PieceSrcSize(src), m_PieceDestSize(dest) {}

void Piece :: render() {
    DrawTexturePro(m_PieceAtlus, m_PieceSrcSize, m_PieceDestSize,
                   {(float)-100, (float)0}, (float)0, WHITE);
}
