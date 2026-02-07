#include <cstdint>
#include <string>
#include <cctype>

class pawnWizard {

public:
    pawnWizard();
    ~pawnWizard();

    // Helper functions
    char getPieceAtSquare(const int index);
    uint64_t* getBitboardByType(const char pieceType);
    void printBoard();
    void printSingleBitBoard(uint64_t &board);
    int uci2index(const char* uci);
    void movePieceByType(char pieceType, int fromIndex, int toIndex);
    void movePiece(int fromIndex, int toIndex);

protected:
    uint64_t whitePawns = 0x000000000000FF00;
    uint64_t whiteRooks = 0x0000000000000081;
    uint64_t whiteKnights = 0x0000000000000042;
    uint64_t whiteBishops = 0x0000000000000024;
    uint64_t whiteKing = 0x0000000000000008;
    uint64_t whiteQueens = 0x0000000000000010;

    uint64_t blackPawns = 0x00FF000000000000;
    uint64_t blackRooks = 0x8100000000000000;
    uint64_t blackKnights = 0x4200000000000000;
    uint64_t blackBishops = 0x2400000000000000;
    uint64_t blackKing = 0x0800000000000000;
    uint64_t blackQueens = 0x1000000000000000;

    bool whiteToMove = true;
    
};
