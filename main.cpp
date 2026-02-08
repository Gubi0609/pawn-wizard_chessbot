#include "pawnWizard.hpp"
#include <iostream>

/*
This will be used as a test file.
*/

int main() {

    pawnWizard chessbot;

    chessbot.printBoard();

    //chessbot.movePieceByType('P', chessbot.uci2index("a2"), chessbot.uci2index("a3"));
    chessbot.movePiece(chessbot.uci2index("a2"), chessbot.uci2index("a3"));
    chessbot.printBoard();

    chessbot.movePiece(chessbot.uci2index("a8"), chessbot.uci2index("a7"));
    chessbot.printBoard();

    return 0;
}