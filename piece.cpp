// piece.cpp
#include "piece.hpp"
#include <stdexcept>


/*
Conséquent : une Piece
Rôle : effectuer une rotation de la pièce
*/
Piece Piece::rotate() const {
    int rows = getRows();
    int cols = getColumns();
    std::vector<std::vector<int>> rotated(cols, std::vector<int>(rows));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            rotated[j][rows - 1 - i] = piece[i][j];
        }
    }
    return Piece(rotated);
}


/*
Conséquent : un vecteur de Pieces
Rôle : Liste toutes les rotations possibles d'une même pièce dans un vecteur
*/
std::vector<Piece> Piece::getAllRotations() const {
    std::vector<Piece> rotations;
    Piece rotatedPiece = *this;
    for (int i = 0; i < 4; ++i) {
        rotations.push_back(rotatedPiece);
        rotatedPiece = rotatedPiece.rotate();
    }
    return rotations;
}


//Rôle : Renvoie le nombre de lignes de la Piece
int Piece::getRows() const {
    return piece.size();
}

//Rôle : Renvoie le nombre de colonnes de la Piece
int Piece::getColumns() const {
    if (piece.empty()) {
        return 0;
    }
    return piece[0].size();
}

//Rôle : Pour une Piece, renvoie la valeur de la case dont les coordonnées sont passées en paramètres 
int Piece::getCellValue(int row, int col) const {
    return piece[row][col];
}

