#include "pawnWizard.hpp"
#include <iostream>

/*
This will be used as a test file.
*/

int main() {

    pawnWizard chessbot;

    chessbot.printBoard();

    //chessbot.movePieceByType('P', chessbot.uci2index("a2"), chessbot.uci2index("a3"));
    
    std::cout << chessbot.knightMovePseudoLegal(chessbot.uci2index("b1")) << std::endl;
    std::cout << ((1ULL << chessbot.uci2index("a3")) | (1ULL << chessbot.uci2index("c3"))) << std::endl;

    return 0;
}