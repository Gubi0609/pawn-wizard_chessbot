#include "pawnWizard.hpp"
#include <iostream>

/*
This will be used as a test file.
*/

int main() {

    pawnWizard chessbot;

    chessbot.printBoard();

    //chessbot.movePieceByType('P', chessbot.uci2index("a2"), chessbot.uci2index("a3"));
    std::cout << chessbot.pawnMovePseudoLegal(chessbot.uci2index("a2")) << std::endl;
    chessbot.movePiece(chessbot.uci2index("a2"), chessbot.uci2index("b6"));
    chessbot.printBoard();
    std::cout << chessbot.pawnMovePseudoLegal(chessbot.uci2index("a7")) << std::endl;
    std::cout << ((1ULL << chessbot.uci2index("a6")) | (1ULL << chessbot.uci2index("b6")) | (1ULL << chessbot.uci2index("a5"))) << std::endl;

    return 0;
}