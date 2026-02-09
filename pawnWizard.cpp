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

void pawnWizard::printSingleBitBoard(const unsigned long int &board) {
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

void pawnWizard::movePieceByType(const char pieceType, const int fromIndex, const int toIndex) {
    /*
    Function that moves a piece from one square to another
    :param pieceType: The type of piece to move represented by a char. Lowercase is black, uppercase is white.
    :param fromIndex: The bit indexed (0-63) square to move from.
    :param toIndex: The bit indexed (0-63) square to move to.
    */

    char pieceAtToSquare = getPieceAtSquare(toIndex);
    unsigned long int& bitboard = getBitboardByType(pieceType);
    unsigned long int startpos = 1ULL << fromIndex;
    bool pawnDoublePush = false;

    if ((!whiteToMove && (((1ULL << fromIndex) & whitePieces) != 0)) || (whiteToMove && (((1ULL << fromIndex) & blackPieces) != 0))) {
        throw std::invalid_argument("fromIndex occupied by enemy piece.");
    }
    if ((whiteToMove && (((1ULL << toIndex) & whitePieces) != 0)) || (!whiteToMove && (((1ULL << toIndex) & blackPieces) != 0))) {
        throw std::invalid_argument("toIndex occupied by friendly piece.");
    }

    unsigned long int movementMask = 0;

    switch (pieceType) {
        case 'p':
        case 'P':
            movementMask = pawnMovePseudoLegal(fromIndex);
            break;
        case 'n':
        case 'N':
            movementMask = knightMovePseudoLegal(fromIndex);
            break;
        // case 'b':
        // case 'B':
        //    movementMask = bishopMovePseudoLegal(fromIndex);
        //    break;
        // case 'r':
        // case 'R':
        //    movementMask = rookMovePseudoLegal(fromIndex);
        //    break;
        // case 'q':
        // case 'Q':
        //    movementMask = queenMovePseudoLegal(fromIndex);
        //    break;
        // case 'k':
        // case 'K':
        //    movementMask = kingMovePseudoLegal(fromIndex);
        //    break;
        default:
            break;
    }

    if ((startpos << toIndex) & ~movementMask != 0) return; // If not in movementMask, we just return.

    // Remove the piece occupying the toIndex square.
    switch (pieceAtToSquare) {
        case 'p':
            blackPawns &= ~(1ULL << toIndex);
            break;
        case 'n':
            blackKnights &= ~(1ULL << toIndex);
            break;
        case 'b':
            blackBishops &= ~(1ULL << toIndex);
            break;
        case 'r':
            blackRooks &= ~(1ULL << toIndex);
            break;
        case 'q':
            blackQueens &= ~(1ULL << toIndex);
            break;
        case 'k':
            blackKing &= ~(1ULL << toIndex);
            break;
        case 'P':
            whitePawns &= ~(1ULL << toIndex);
            break;
        case 'N':
            whiteKnights &= ~(1ULL << toIndex);
            break;
        case 'B':
            whiteBishops &= ~(1ULL << toIndex);
            break;
        case 'R':
            whiteRooks &= ~(1ULL << toIndex);
            break;
        case 'Q':
            whiteQueens &= ~(1ULL << toIndex);
            break;
        case 'K':
            whiteKing &= ~(1ULL << toIndex);
            break;
        default:
            break;
    }

    bitboard &= ~(1ULL << fromIndex); // Remove piece from "from" square

    if ((startpos & whitePawns) != 0 && (toIndex - fromIndex) == 16) {
        pawnDoublePush = true;
        enPassant |= startpos << 8;
    } else if (((startpos & blackPawns) != 0 && (fromIndex - toIndex) == 16)) {
        pawnDoublePush = true;
        enPassant |= startpos >> 8;
    }

    bitboard |= (1ULL << toIndex);    // Place piece on "to" square
    
    // Update the color bitboards to match newest placements.
    whitePieces = whitePawns | whiteRooks | whiteKnights | whiteBishops | whiteKing | whiteQueens;
    blackPieces = blackPawns | blackRooks | blackKnights | blackBishops | blackKing | blackQueens;

    whiteToMove = !whiteToMove;

    if(!pawnDoublePush) enPassant = 0x0000000000000000;
    
}

void pawnWizard::movePiece(const int fromIndex, const int toIndex) {
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

unsigned long int pawnWizard::pawnMovePseudoLegal(const int fromIndex) {
    /*
    Generates all possible psuedo legal moves for a pawn at position fromIndex.
    :param fromIndex: The bit indexed (0-63) square to move from.
    :return: unsigned long int with a binary value corresponding to the moveable squares.
    */

    // TODO: 
    // - En pasant
    // - Promotion


    unsigned long int startPos = 1ULL << fromIndex;

    if ((startPos & ~(whitePawns | blackPawns)) != 0) {
        throw std::invalid_argument("fromIndex not occupied by pawn.");
    }

    unsigned long int moves = 0;

    if ((startPos & whitePawns) != 0) {
        if (((startPos << 8) & ~(whitePieces | blackPieces)) != 0) moves |= startPos << 8; // Can't push forward into other piece
        
        if ((startPos & (ROW_2)) != 0 && 
            (((startPos << 16) & ~(whitePieces | blackPieces)) != 0)) moves |= startPos << 16; // Double push if first move
        
        if ((startPos & ~(A_FILE)) != 0 && ((startPos << 7) & blackPieces) != 0) moves |= startPos << 7; // Attack West if not on a file
        if ((startPos & ~(H_FILE)) != 0 && ((startPos << 9) & blackPieces) != 0) moves |= startPos << 9; // Attack East if not on h file

        if ((startPos & ~(A_FILE)) != 0 && ((startPos << 7) & enPassant) != 0) moves |= startPos << 7; // En passant west if not on a file
        if ((startPos & ~(H_FILE)) != 0 && ((startPos << 9) & enPassant) != 0) moves |= startPos << 9; // En passant east if not on h file
    
    } else if ((startPos & blackPawns) != 0) {
        if (((startPos >> 8) & ~(whitePieces | blackPieces)) != 0) moves |= startPos >> 8; // Can't push forward into other piece
        
        if ((startPos & (ROW_7)) != 0 && 
            (((startPos >> 16) & ~(whitePieces | blackPieces)) != 0)) moves |= startPos >> 16; // Double push if first move
        
        if ((startPos & ~(A_FILE)) != 0 && ((startPos >> 9) & whitePieces) != 0) moves |= startPos >> 9; // Attack West if not on a file
        if ((startPos & ~(H_FILE)) != 0 && ((startPos >> 7) & whitePieces) != 0) moves |= startPos >> 7; // Attack East if not on h file

        if ((startPos & ~(A_FILE)) != 0 && ((startPos >> 9) & enPassant) != 0) moves |= startPos >> 9; // En passant west if not on a file
        if ((startPos & ~(H_FILE)) != 0 && ((startPos >> 7) & enPassant) != 0) moves |= startPos >> 7; // En passant east if not on h file
    }

    return moves;
}

unsigned long int pawnWizard::knightMovePseudoLegal(const int fromIndex) {
    /*
    Generates all possible pseudo legal moves for a knight at position fromIndex.
    :param fromIndex: The bit indexed (0-63) square to move from.
    :return: unsigned long int with a binary value corresponding to the moveable squares.
    */

    unsigned long int startPos = 1ULL << fromIndex;

    if ((startPos & ~(whiteKnights | blackKnights)) != 0) throw std::invalid_argument("fromIndex not occupied by knight.");

    unsigned long int attacks = 0; // Will store possible attacks.


    if ((startPos & ~(A_FILE)) != 0 && (startPos & ~(ROW_7)) != 0 && (startPos & ~(ROW_8)) != 0) attacks |= startPos << 15; // Move 2 up and 1 left
    if ((startPos & ~(A_FILE)) != 0 && (startPos & ~(B_FILE)) != 0 && (startPos & ~(ROW_8)) != 0) attacks |= startPos << 6; // Move 1 up and 2 left
    if ((startPos & ~(H_FILE)) != 0 && (startPos & ~(ROW_7)) != 0 && (startPos & ~(ROW_8)) != 0) attacks |= startPos << 17; // Move 2 up and 1 right
    if ((startPos & ~(H_FILE)) != 0 && (startPos & ~(G_FILE)) != 0 && (startPos & ~(ROW_8)) != 0) attacks |= startPos << 10; // Move 1 up and 2 right
    if ((startPos & ~(A_FILE)) != 0 && (startPos & ~(ROW_2)) != 0 && (startPos & ~(ROW_1)) != 0) attacks |= startPos >> 17; // Move 2 down and 1 left
    if ((startPos & ~(A_FILE)) != 0 && (startPos & ~(B_FILE)) != 0 && (startPos & ~(ROW_1)) != 0) attacks |= startPos >> 10; // Move 1 down and 2 left
    if ((startPos & ~(H_FILE)) != 0 && (startPos & ~(ROW_2)) != 0 && (startPos & ~(ROW_1)) != 0) attacks |= startPos >> 15; // Move 2 down and 1 right
    if ((startPos & ~(H_FILE)) != 0 && (startPos & ~(G_FILE)) != 0 && (startPos & ~(ROW_1)) != 0) attacks |= startPos >> 6; // Move 1 down and 2 right

    if ((startPos & whiteKnights) != 0) attacks &= ~(whitePieces); // Remove friendly pieces from attack options
    else if ((startPos & blackKnights) != 0) attacks &= ~(blackPieces); // Remove friendly pieces from attack options

    return attacks;

}