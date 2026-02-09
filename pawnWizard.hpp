// Definition of all files (a - h) as unsigned long int
#define A_FILE 0x0101010101010101ULL
#define B_FILE 0x0202020202020202ULL
#define C_FILE 0x0404040404040404ULL
#define D_FILE 0x0808080808080808ULL
#define E_FILE 0x1010101010101010ULL
#define F_FILE 0x2020202020202020ULL
#define G_FILE 0x4040404040404040ULL
#define H_FILE 0x8080808080808080ULL

// Definition of all rows (1 - 8) as unsigned long int
#define ROW_1 0x00000000000000FFULL
#define ROW_2 0x000000000000FF00ULL
#define ROW_3 0x0000000000FF0000ULL
#define ROW_4 0x00000000FF000000ULL
#define ROW_5 0x000000FF00000000ULL
#define ROW_6 0x0000FF0000000000ULL
#define ROW_7 0x00FF000000000000ULL
#define ROW_8 0xFF00000000000000ULL

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

    bool whiteToMove = true;
    
};
