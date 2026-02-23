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


// Starting positions
#define WHITE_PAWNS_START   0x000000000000FF00
#define WHITE_ROOKS_START   0x0000000000000081
#define WHITE_KNIGHTS_START 0x0000000000000042
#define WHITE_BISHOPS_START 0x0000000000000024
#define WHITE_KING_START    0x0000000000000010
#define WHITE_QUEENS_START  0x0000000000000008

#define BLACK_PAWNS_START   0x00FF000000000000
#define BLACK_ROOKS_START   0x8100000000000000
#define BLACK_KNIGHTS_START 0x4200000000000000
#define BLACK_BISHOPS_START 0x2400000000000000
#define BLACK_KING_START    0x1000000000000000
#define BLACK_QUEEN_START   0x0800000000000000

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

    // Sliding piece functions
    unsigned long int rookOccupancyRay(const int fromIndex);

    // Legal move functions
    unsigned long int pawnMovePseudoLegal(const int fromIndex);
    unsigned long int knightMovePseudoLegal(const int fromIndex);
    unsigned long int kingMovePseudoLegal(const int fromIndex);

protected:
    unsigned long int whitePawns = WHITE_PAWNS_START;
    unsigned long int whiteRooks = WHITE_ROOKS_START;
    unsigned long int whiteKnights = WHITE_KNIGHTS_START;
    unsigned long int whiteBishops = WHITE_BISHOPS_START;
    unsigned long int whiteKing = WHITE_KING_START;
    unsigned long int whiteQueens = WHITE_QUEENS_START;
    unsigned long int whitePieces = whitePawns | whiteRooks | whiteKnights | whiteBishops | whiteKing | whiteQueens;

    unsigned long int blackPawns = BLACK_PAWNS_START;
    unsigned long int blackRooks = BLACK_ROOKS_START;
    unsigned long int blackKnights = BLACK_KNIGHTS_START;
    unsigned long int blackBishops = BLACK_BISHOPS_START;
    unsigned long int blackKing = BLACK_KING_START;
    unsigned long int blackQueens = BLACK_QUEEN_START;
    unsigned long int blackPieces = blackPawns | blackRooks | blackKnights | blackBishops | blackKing | blackQueens;

    unsigned long int enPassant = 0x0000000000000000;
    bool whiteCastleWest = true;
    bool whiteCastleEast = true;
    bool blackCastleWest = true;
    bool blackCastleEast = true;

    bool whiteToMove = true;
    
};
