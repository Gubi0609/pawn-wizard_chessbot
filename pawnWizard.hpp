class pawnWizard {

public:
    pawnWizard();
    ~pawnWizard();

    // Helper functions
    char getPieceAtSquare(const int index);
    unsigned long int& getBitboardByType(const char pieceType);
    void printBoard();
    void printSingleBitBoard(const unsigned long int &board);
    int uci2index(const char* uci);
    void movePieceByType(const char pieceType, const int fromIndex, const int toIndex);
    void movePiece(const int fromIndex, const int toIndex);

    // Legal move functions
    unsigned long int pawnMovePseudoLegal(const int fromIndex);
    unsigned long int knightMovePseudoLegal(const int fromIndex);

protected:
    unsigned long int whitePawns = 0x000000000000FF00;
    unsigned long int whiteRooks = 0x0000000000000081;
    unsigned long int whiteKnights = 0x0000000000000042;
    unsigned long int whiteBishops = 0x0000000000000024;
    unsigned long int whiteKing = 0x0000000000000010;
    unsigned long int whiteQueens = 0x0000000000000008;
    unsigned long int whitePieces = whitePawns | whiteRooks | whiteKnights | whiteBishops | whiteKing | whiteQueens;

    unsigned long int blackPawns = 0x00FF000000000000;
    unsigned long int blackRooks = 0x8100000000000000;
    unsigned long int blackKnights = 0x4200000000000000;
    unsigned long int blackBishops = 0x2400000000000000;
    unsigned long int blackKing = 0x1000000000000000;
    unsigned long int blackQueens = 0x0800000000000000;
    unsigned long int blackPieces = blackPawns | blackRooks | blackKnights | blackBishops | blackKing | blackQueens;

    unsigned long int enPassant = 0x0000000000000000;

    const unsigned long int aFile = 0x0101010101010101;
    const unsigned long int bFile = 0x0202020202020202;
    const unsigned long int cFile = 0x0404040404040404;
    const unsigned long int dFile = 0x0808080808080808;
    const unsigned long int eFile = 0x1010101010101010;
    const unsigned long int fFile = 0x2020202020202020;
    const unsigned long int gFile = 0x4040404040404040;
    const unsigned long int hFile = 0x8080808080808080;

    const unsigned long int row1 = 0x00000000000000FF;
    const unsigned long int row2 = 0x000000000000FF00;
    const unsigned long int row3 = 0x0000000000FF0000;
    const unsigned long int row4 = 0x00000000FF000000;
    const unsigned long int row5 = 0x000000FF00000000;
    const unsigned long int row6 = 0x0000FF0000000000;
    const unsigned long int row7 = 0x00FF000000000000;
    const unsigned long int row8 = 0xFF00000000000000;

    bool whiteToMove = true;
    
};
