#include <iostream>

#include "pawnWizard.hpp"

pawnWizard::pawnWizard() {}

pawnWizard::~pawnWizard() {}

char pawnWizard::getPieceAtSquare(const int index) {
    /*
    Helper function to get the piece type at a bitindexed square.
    :param index: The bit indexed (0-63) square to query.
    :return: A char representing the piece. lowercase is black, uppercase is white.
    */

    uint64_t mask = 1ULL << index;

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

void pawnWizard::printSingleBitBoard(uint64_t &board) {
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

    return 8 * (row - 1) + (file - 'a');
}