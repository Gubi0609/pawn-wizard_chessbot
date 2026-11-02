# pawn-wizard_chessbot

A chessbot programmed in C++.

## TODO
- Finish implementation on getLegalMask. Need to identify pinned pieces and also use the recognized attacking pieces to isolate allowed moves.
- Implement getPseudoLegaByIndex in functions otherwise using switchcase
- Evaluate if rookRaysWithEdges and bishopRaysWithEdges are even necessary. Might not be needed.
    - Only idea right now is to use it in getLegalMask. Will need to finish function to evaluate

## Build

Requirements:

- GNU Make
- A C++17-compatible compiler

Build the executable with:

```sh
make
```

The executable is written to `bin/pawn-wizard`. Run it with:

```sh
make run
```

Other available targets:

- `make clean` removes generated build files and the executable.
- `make format` formats the C++ sources with `clang-format`.