#pragma once

#include <vector>
#include "piece.hpp"


class PieceFactory {
public:
    static Piece* createPiece(const std::vector<std::vector<int>>& pieceData);
};
