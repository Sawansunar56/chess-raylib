class PlayPiece
{
  public:
    PlayPiece(int type) : m_pieceType(type) {}

  private:
    float m_boardPosition;
    int m_pieceType;
};
