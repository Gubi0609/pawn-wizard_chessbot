#include "pawnWizard.hpp"
#include <iostream>

/*
This will be used as a test file.
*/

int main() {

    pawnWizard chessbot;

    chessbot.printBoard();

    //chessbot.movePieceByType('P', chessbot.uci2index("a2"), chessbot.uci2index("a3"));
    std::cout << chessbot.pawnMovePseudoLegal(chessbot.uci2index("a2"), chessbot.uci2index("a4")) << std::endl;
    chessbot.movePiece(chessbot.uci2index("a2"), chessbot.uci2index("b6"));
    chessbot.printBoard();
    std::cout << chessbot.pawnMovePseudoLegal(chessbot.uci2index("a7"), chessbot.uci2index("b6")) << std::endl;

    return 0;
}