#pragma once
#include <vector>
#include "piece.hpp"

class Tole {
private:
    std::vector<std::vector<int>> tole;
public:
    Tole(const std::vector<std::vector<int>>& t) : tole(t) {}
    bool isSolvable(const Piece& piece) const;
    bool isValidPlacement(const Piece& piece, int row, int col) const;
    void placePiece(const Piece& piece, int row, int col, int pieceNum);
    void removePiece(int pieceNum);
    bool isFull() const;
    int getRows() const;
    int getColumns() const;
    int getCellValue(int row, int col) const;
    void set_data(const std::vector<std::vector<int>>& data);
    std::vector<std::vector<int>> get_data() const;


};
