class pawnWizard {

public:
    pawnWizard();
    ~pawnWizard();

    // Helper functions
    char getPieceAtSquare(const int index);
    unsigned long int& getBitboardByType(const char pieceType);
    void printBoard();
    void printSingleBitBoard(unsigned long int &board);
    int uci2index(const char* uci);
    void movePieceByType(char pieceType, int fromIndex, int toIndex);
    void movePiece(int fromIndex, int toIndex);

protected:
    unsigned long int whitePawns = 0x000000000000FF00;
    unsigned long int whiteRooks = 0x0000000000000081;
    unsigned long int whiteKnights = 0x0000000000000042;
    unsigned long int whiteBishops = 0x0000000000000024;
    unsigned long int whiteKing = 0x0000000000000008;
    unsigned long int whiteQueens = 0x0000000000000010;

    unsigned long int blackPawns = 0x00FF000000000000;
    unsigned long int blackRooks = 0x8100000000000000;
    unsigned long int blackKnights = 0x4200000000000000;
    unsigned long int blackBishops = 0x2400000000000000;
    unsigned long int blackKing = 0x0800000000000000;
    unsigned long int blackQueens = 0x1000000000000000;

    bool whiteToMove = true;
    
};
