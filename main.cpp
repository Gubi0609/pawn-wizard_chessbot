#include "pawnWizard.hpp"
#include <iostream>


using namespace std;

/*
This will be used as a test file.
*/

int main() {

    pawnWizard chessbot;

    // chessbot.printBoard();
    // chessbot.printSingleBitBoard(chessbot.pawnMovePseudoLegal(8));
    // chessbot.movePiece(11, 11+16);
    // chessbot.printBoard();
    // chessbot.movePiece(chessbot.uci2index("e7"), chessbot.uci2index("e5"));
    // chessbot.printSingleBitBoard(chessbot.pawnMovePseudoLegal(11+16));
    // chessbot.movePiece(27, 36);
    // chessbot.printBoard();
    // chessbot.movePiece(chessbot.uci2index("d7"), chessbot.uci2index("d5"));
    // chessbot.printBoard();
    // chessbot.printSingleBitBoard(chessbot.pawnMovePseudoLegal(36));
    // chessbot.movePiece(36, 36+8);
    // chessbot.printBoard();

    chessbot.printSingleBitBoard(chessbot.rookOccupancyRay(3));

    return 0;
}