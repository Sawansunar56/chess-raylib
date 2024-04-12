#pragma once

#include "raylib.h"

// pieces for rendering from the atlus
enum pieces
{
    BLACK_PIECE_ROOK,
    BLACK_PIECE_BISHOP,
    BLACK_PIECE_QUEEN,
    BLACK_PIECE_KING,
    BLACK_PIECE_KNIGHT,
    BLACK_PIECE_PAWN,
    WHITE_PIECE_ROOK,
    WHITE_PIECE_BISHOP,
    WHITE_PIECE_QUEEN,
    WHITE_PIECE_KING,
    WHITE_PIECE_KNIGHT,
    WHITE_PIECE_PAWN,
    P_NUM,
};

// 32 pieces on the board
// NOTE: order matters
enum boardPiece
{
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
    BOARD_PIECE_NUM
};
struct WorldPosition
{
    float positionX;
    float positionY;
    float pieceGap;
    float pieceScale;
};
class Piece
{
  public:
    Piece(Texture2D &atlus, Rectangle src, Rectangle dest,
          WorldPosition moveElements);
    void render();
    void render(int x, int y);

  private:
    Rectangle m_PieceDestSize;
    Rectangle m_PieceSrcSize;
    Texture2D &m_PieceAtlus;
    WorldPosition m_MoveElements;
};
