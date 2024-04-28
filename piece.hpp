#pragma once

#include <vector>


class Piece {
protected:
    std::vector<std::vector<int>> piece;

public:
    Piece(const std::vector<std::vector<int>> &piece) : piece(piece) {}
    virtual ~Piece() {}
    Piece rotate() const;
    virtual std::vector<Piece> getAllRotations() const;
    int getRows() const;
    int getColumns() const;
    int getCellValue(int row, int col) const;
    int getData();
};


class SquarePiece : public Piece {
public:
    SquarePiece(const std::vector<std::vector<int>> &pieceData) : Piece(pieceData) {}

    std::vector<Piece> getAllRotations() const override {
        // Pour une pièce carrée, toutes les rotations sont identiques
        // Donc on retourne un vecteur contenant une seule rotation
        return {*this};
    }
   
};


class RectangularPiece : public Piece {
public:
    RectangularPiece(const std::vector<std::vector<int>> &pieceData) : Piece(pieceData) {}

    std::vector<Piece> getAllRotations() const override {
        // Pour une pièce rectangulaire, il y a seulement deux rotations uniques
        // Donc on retourne un vecteur contenant ces deux rotations
        return {*this, this->rotate()};
    }
};
