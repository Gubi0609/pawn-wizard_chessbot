#ifndef PAWNWIZARD_HPP
#define PAWNWIZARD_HPP

#include <string>
#include <bits/stdc++.h> // For popcount
#include <iostream> // For printing bitboard
#include <stdexcept> // For throwing exceptions
#include <cstdint> // For 64 bit integers

// Definition of all files (a - h) as uint64_t
#define A_FILE 0x0101010101010101ULL
#define B_FILE 0x0202020202020202ULL
#define C_FILE 0x0404040404040404ULL
#define D_FILE 0x0808080808080808ULL
#define E_FILE 0x1010101010101010ULL
#define F_FILE 0x2020202020202020ULL
#define G_FILE 0x4040404040404040ULL
#define H_FILE 0x8080808080808080ULL

// Definition of all rows (1 - 8) as uint64_t
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
    uint64_t& getBitboardByType(const char pieceType);
    void printBoard();
    void printSingleBitBoard(const uint64_t &board);
    int uci2index(const std::string uci);
    std::string index2uci(const int index);
    void movePieceByType(const char pieceType, const int fromIndex, const int toIndex);
    void movePiece(const int fromIndex, const int toIndex);

    // Sliding piece functions
    uint64_t rookRay(const int fromIndex);
    uint64_t bishopRay(const int fromIndex);
    uint64_t getRelevantOccupancy(const uint64_t movementRay, const uint64_t occupancy);
    uint64_t walkRookRay(const int fromIndex, const uint64_t occupancy);
    uint64_t walkBishopRay(const int fromIndex, const uint64_t occupancy);

    // Magic Bitboard init
    void initRookShifts();
    void initBishopShifts();
    void initRookTable();
    void initBishopTable();

    // Jumping piece init
    void initKnightTable();
    void initKingTable();

    // Legal move functions
    uint64_t pawnMovePseudoLegal(const int fromIndex);
    uint64_t knightLookupTableGeneration(const int fromIndex);
    uint64_t knightMovePseudoLegal(const int fromIndex);
    uint64_t kingLookupTableGeneration(const int fromIndex);
    uint64_t kingMovePseudoLegal(const int fromIndex);

protected:

    // Initiate white piece placement
    uint64_t whitePawns = WHITE_PAWNS_START;
    uint64_t whiteRooks = WHITE_ROOKS_START;
    uint64_t whiteKnights = WHITE_KNIGHTS_START;
    uint64_t whiteBishops = WHITE_BISHOPS_START;
    uint64_t whiteKing = WHITE_KING_START;
    uint64_t whiteQueens = WHITE_QUEENS_START;
    uint64_t whitePieces = whitePawns | whiteRooks | whiteKnights | whiteBishops | whiteKing | whiteQueens;

    // Initiate black piece placement
    uint64_t blackPawns = BLACK_PAWNS_START;
    uint64_t blackRooks = BLACK_ROOKS_START;
    uint64_t blackKnights = BLACK_KNIGHTS_START;
    uint64_t blackBishops = BLACK_BISHOPS_START;
    uint64_t blackKing = BLACK_KING_START;
    uint64_t blackQueens = BLACK_QUEEN_START;
    uint64_t blackPieces = blackPawns | blackRooks | blackKnights | blackBishops | blackKing | blackQueens;

    // Lookup tables for jumping pieces
    uint64_t knightLookupTable[64];
    uint64_t kingLookupTable[64];

    // Bitboard updated every move to keep track of possible en passant moves
    uint64_t enPassant = 0x0000000000000000;

    // Biboards to keep track of possible castle for each color
    bool whiteCastleWest = true;
    bool whiteCastleEast = true;
    bool blackCastleWest = true;
    bool blackCastleEast = true;

    bool whiteToMove = true;

    /* Used for magic bitboard generation */
    uint64_t rookTable[64][4096];
    uint64_t bishopTable[64][512];

    uint64_t rookMagics[64] = {612498416294952992ULL,  2377936612260610304ULL,  36037730568766080ULL,
                                        72075188908654856ULL,   144119655536003584ULL,   5836666216720237568ULL,
                                        9403535813175676288ULL, 1765412295174865024ULL,  3476919663777054752ULL,
                                        288300746238222339ULL,  9288811671472386ULL,     146648600474026240ULL,
                                        3799946587537536ULL,    704237264700928ULL,      10133167915730964ULL,
                                        2305983769267405952ULL, 9223634270415749248ULL,  10344480540467205ULL,
                                        9376496898355021824ULL, 2323998695235782656ULL,  9241527722809755650ULL,
                                        189159985010188292ULL,  2310421375767019786ULL,  4647717014536733827ULL,
                                        5585659813035147264ULL, 1442911135872321664ULL,  140814801969667ULL,
                                        1188959108457300100ULL, 288815318485696640ULL,   758869733499076736ULL,
                                        234750139167147013ULL,  2305924931420225604ULL,  9403727128727390345ULL,
                                        9223970239903959360ULL, 309094713112139074ULL,   38290492990967808ULL,
                                        3461016597114651648ULL, 181289678366835712ULL,   4927518981226496513ULL,
                                        1155212901905072225ULL, 36099167912755202ULL,    9024792514543648ULL,
                                        4611826894462124048ULL, 291045264466247688ULL,   83880127713378308ULL,
                                        1688867174481936ULL,    563516973121544ULL,      9227888831703941123ULL,
                                        703691741225216ULL,     45203259517829248ULL,    693563138976596032ULL,
                                        4038638777286134272ULL, 865817582546978176ULL,   13835621555058516608ULL,
                                        11541041685463296ULL,   288511853443695360ULL,   283749161902275ULL,
                                        176489098445378ULL,     2306124759338845321ULL,  720584805193941061ULL,
                                        4977040710267061250ULL, 10097633331715778562ULL, 325666550235288577ULL,
                                        1100057149646ULL};
    
    uint64_t bishopMagics[64] = {9368648609924554880ULL, 9009475591934976ULL,     4504776450605056ULL,
                                        1130334595844096ULL,    1725202480235520ULL,     288516396277699584ULL,
                                        613618303369805920ULL,  10168455467108368ULL,    9046920051966080ULL,
                                        36031066926022914ULL,   1152925941509587232ULL,  9301886096196101ULL,
                                        290536121828773904ULL,  5260205533369993472ULL,  7512287909098426400ULL,
                                        153141218749450240ULL,  9241386469758076456ULL,  5352528174448640064ULL,
                                        2310346668982272096ULL, 1154049638051909890ULL,  282645627930625ULL,
                                        2306405976892514304ULL, 11534281888680707074ULL, 72339630111982113ULL,
                                        8149474640617539202ULL, 2459884588819024896ULL,  11675583734899409218ULL,
                                        1196543596102144ULL,    5774635144585216ULL,     145242600416216065ULL,
                                        2522607328671633440ULL, 145278609400071184ULL,   5101802674455216ULL,
                                        650979603259904ULL,     9511646410653040801ULL,  1153493285013424640ULL,
                                        18016048314974752ULL,   4688397299729694976ULL,  9226754220791842050ULL,
                                        4611969694574863363ULL, 145532532652773378ULL,   5265289125480634376ULL,
                                        288239448330604544ULL,  2395019802642432ULL,     14555704381721968898ULL,
                                        2324459974457168384ULL, 23652833739932677ULL,    282583111844497ULL,
                                        4629880776036450560ULL, 5188716322066279440ULL,  146367151686549765ULL,
                                        1153170821083299856ULL, 2315697107408912522ULL,  2342448293961403408ULL,
                                        2309255902098161920ULL, 469501395595331584ULL,   4615626809856761874ULL,
                                        576601773662552642ULL,  621501155230386208ULL,   13835058055890469376ULL,
                                        3748138521932726784ULL, 9223517207018883457ULL,  9237736128969216257ULL,
                                        1127068154855556ULL};

    uint64_t rookShifts[64];
    uint64_t bishopShifts[64];
    
};

#endif