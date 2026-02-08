#include <iostream>
#include <stdexcept>

#include "pawnWizard.hpp"

pawnWizard::pawnWizard() {}

pawnWizard::~pawnWizard() {}


/*
    === HELPER FUNCTIONS ===
*/

char pawnWizard::getPieceAtSquare(const int index) {
    /*
    Helper function to get the piece type at a bitindexed square.
    :param index: The bit indexed (0-63) square to query.
    :return: A char representing the piece. lowercase is black, uppercase is white.
    */

    unsigned long int mask = 1ULL << index;

    if (whitePawns & mask) return 'P';
    if (whiteKnights & mask) return 'N';
    if (whiteBishops & mask) return 'B';
    if (whiteRooks & mask) return 'R';
    if (whiteQueens & mask) return 'Q';
    if (whiteKing & mask) return 'K';
    
    if (blackPawns & mask) return 'p';
    if (blackKnights & mask) return 'n';
    if (blackBishops & mask) return 'b';
    if (blackRooks & mask) return 'r';
    if (blackQueens & mask) return 'q';
    if (blackKing & mask) return 'k';

    return '.'; // Empty square
}

unsigned long int& pawnWizard::getBitboardByType(const char pieceType) {
    /*
    Function to get the corresponding bitboard for a type of piece.
    :param pieceType: The type of piece represented by a char. Lowercase for black, uppercase for white.
    :return: The 64-bit bitboard representation of the pieces' of pieceType placement.
    */

    if (pieceType == 'p') return blackPawns;
    else if (pieceType == 'r') return blackRooks;
    else if (pieceType == 'n') return blackKnights;
    else if (pieceType == 'b') return blackBishops;
    else if (pieceType == 'q') return blackQueens;
    else if (pieceType == 'k') return blackKing;
    else if (pieceType == 'P') return whitePawns;
    else if (pieceType == 'R') return whiteRooks;
    else if (pieceType == 'N') return whiteKnights;
    else if (pieceType == 'B') return whiteBishops;
    else if (pieceType == 'Q') return whiteQueens;
    else if (pieceType == 'K') return whiteKing;
    
    throw std::invalid_argument("Not a valid pieceType.");

}

void pawnWizard::printBoard() {
    /*
    Helper function to print the current board layout to terminal.
    */

    for(int row = 7; row >= 0; row--){
        std::cout << (row + 1) << "| ";
        for(int file = 0; file < 8; file++){
            int bitSquare = row * 8 + file;
            std::cout << getPieceAtSquare(bitSquare) << " ";
        }
        std::cout << "|" << "\n";
    }

    std::cout << "  -----------------\n";
    std::cout << "   a b c d e f g h\n";
}

void pawnWizard::printSingleBitBoard(unsigned long int &board) {
    /*
    Helper function to print a single piece-board to terminal.
    */
    
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            int square = rank * 8 + file;
            std::cout << ((board >> square) & 1) << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int pawnWizard::uci2index(const char* uci) {
    /*
    Function to convert from UCI square (e.g. a2) to bit index.
    :param uci: The UCI square to convert.
    :return: The bit indexed UCI square (0-63).
    */

    char file = uci[0];
    char row = uci[1] - '0';

    int bitIndex = 8 * (row - 1) + (file - 'a');
    
    return bitIndex;
}

void pawnWizard::movePieceByType(char pieceType, int fromIndex, int toIndex) {
    /*
    Function that moves a piece from one square to another
    :param pieceType: The type of piece to move represented by a char. Lowercase is black, uppercase is white.
    :param fromIndex: The bit indexed (0-63) square to move from.
    :param toIndex: The bit indexed (0-63) square to move to.
    */

    char pieceAtToSquare = getPieceAtSquare(toIndex);
    unsigned long int& bitboard = getBitboardByType(pieceType);

    if ((!whiteToMove && (((1ULL << fromIndex) & whitePieces) != 0)) || (whiteToMove && (((1ULL << fromIndex) & blackPieces) != 0))) {
        throw std::invalid_argument("fromIndex occupied by enemy piece.");
    }
    if ((whiteToMove && (((1ULL << toIndex) & whitePieces) != 0)) || (!whiteToMove && (((1ULL << toIndex) & blackPieces) != 0))) {
        throw std::invalid_argument("toIndex occupied by friendly piece.");
    }

    // Remove the piece occupying the toIndex square.
    if (pieceAtToSquare == 'p'){
        blackPawns &= ~(1ULL << toIndex);
    } else if (pieceAtToSquare == 'n'){
        blackKnights &= ~(1ULL << toIndex);
    } else if (pieceAtToSquare == 'b'){
        blackBishops &= ~(1ULL << toIndex);
    } else if (pieceAtToSquare == 'r'){
        blackRooks &= ~(1ULL << toIndex);
    } else if (pieceAtToSquare == 'q'){
        blackQueens &= ~(1ULL << toIndex);
    } else if (pieceAtToSquare == 'k'){
        blackKing &= ~(1ULL << toIndex);
    } else if (pieceAtToSquare == 'P'){
        whitePawns &= ~(1ULL << toIndex);
    } else if (pieceAtToSquare == 'N'){
        whiteKnights &= ~(1ULL << toIndex);
    } else if (pieceAtToSquare == 'B'){
        whiteBishops &= ~(1ULL << toIndex);
    } else if (pieceAtToSquare == 'R'){
        whiteRooks &= ~(1ULL << toIndex);
    } else if (pieceAtToSquare == 'Q'){
        whiteQueens &= ~(1ULL << toIndex);
    } else if (pieceAtToSquare == 'K'){
        whiteKing &= ~(1ULL << toIndex);
    }

    bitboard &= ~(1ULL << fromIndex); // Remove piece from "from" square
    bitboard |= (1ULL << toIndex);    // Place piece on "to" square
    
    // Update the color bitboards to match newest placements.
    whitePieces = whitePawns | whiteRooks | whiteKnights | whiteBishops | whiteKing | whiteQueens;
    blackPieces = blackPawns | blackRooks | blackKnights | blackBishops | blackKing | blackQueens;

    whiteToMove = !whiteToMove;
    
}

void pawnWizard::movePiece(int fromIndex, int toIndex) {
    /*
    Function that automatically moves the piece on the from square to the to square.
    :param fromIndex: The bit indexed (0-63) square to move from.
    :param toIndex: The bit indexed (0-63) square to move to.
    */

    char pieceType = getPieceAtSquare(fromIndex);

    if (pieceType == '.') {
        throw std::invalid_argument("Invalid fromIndex. No piece on that square.");
    }

    movePieceByType(pieceType, fromIndex, toIndex);
}

/*
    === LEGAL MOVE FUNCTIONS ===
*/

bool pawnWizard::pawnMovePseudoLegal(int fromIndex, int toIndex) {
    /*
    Function to check if a pawn move is pseudo legal.
    :param fromIndex: The bit indexed (0-63) square to move from.
    :param toIndex: The bit indexed (0-63) square to move to.
    :return: True/False depending on the moves legality.
    */

    // TODO: En pasant

    if ((!whiteToMove && (((1ULL << fromIndex) & whitePieces) != 0)) || (whiteToMove && (((1ULL << fromIndex) & blackPieces) != 0))) {
        throw std::invalid_argument("fromIndex occupied by enemy piece.");
    }
    if ((whiteToMove && (((1ULL << toIndex) & whitePieces) != 0)) || (!whiteToMove && (((1ULL << toIndex) & blackPieces) != 0))) {
        throw std::invalid_argument("toIndex occupied by friendly piece.");
    }
    if ((!whiteToMove && (((1ULL << fromIndex) & whitePawns) != 0)) || (whiteToMove && (((1ULL << fromIndex) & blackPawns) != 0))) {
        throw std::invalid_argument("fromIndex not occupied by pawn.");
    }

    unsigned long int pushFile = 0;
    unsigned long int doublePushFile = 0;
    unsigned long int attackWest = 0;
    unsigned long int attackEast = 0;

    if (whiteToMove) {
        pushFile = (1ULL << fromIndex) << 8;
        if (((1ULL << fromIndex) & (0x000000000000FF00)) != 0) doublePushFile = (1ULL << fromIndex) << 16;
        if (((1ULL << fromIndex) & ~(aFile)) != 0 && ((1ULL << toIndex) & blackPieces) != 0) attackWest = (1ULL << fromIndex) << 7;
        if (((1ULL << fromIndex) & ~(hFile)) != 0 && ((1ULL << toIndex) & blackPieces) != 0) attackEast = (1ULL << fromIndex) << 9;
    } else {
        pushFile = (1ULL << fromIndex) >> 8;
        if (((1ULL << fromIndex) & (0x00FF000000000000)) != 0) doublePushFile = (1ULL << fromIndex) >> 16;
        if (((1ULL << fromIndex) & ~(aFile)) != 0 && ((1ULL << toIndex) & whitePieces) != 0) attackWest = (1ULL << fromIndex) >> 9;
        if (((1ULL << fromIndex) & ~(hFile)) != 0 && ((1ULL << toIndex) & whitePieces) != 0) attackEast = (1ULL << fromIndex) >> 7;
    }

    return ((pushFile | doublePushFile | attackWest | attackEast) & (1ULL << toIndex)) != 0;
}