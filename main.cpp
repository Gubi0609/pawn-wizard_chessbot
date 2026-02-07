#include "pawnWizard.hpp"
#include <iostream>

/*
This will be used as a test file.
*/

int main() {

    pawnWizard chessbot;

    chessbot.printBoard();

    std::cout << chessbot.uci2index("a1") << "\n";

    return 0;
}