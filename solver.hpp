
#pragma once
#include "tole.hpp"
#include "piece.hpp"

class Solver {
public:
    bool solve(Tole& tole, Piece& piece, int pieceNum);
    bool preprocess(Tole& tole, Piece& piece);
    bool tryAllPositions(Tole& tole, const Piece& piece, int adjRow, int adjCol);
};
