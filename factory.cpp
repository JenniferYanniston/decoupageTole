#include "factory.hpp"
#include "piece.hpp"
#include <algorithm>
#include <iostream>

/*
Antécédent : un vecteur d'entiers
Conséquent : un booleén
Rôle : Vérifie si la pièce est remplie de 1
*/
bool isFullyFilled(const std::vector<int> &row) {
    for (int val : row) {
        if (val != 1)
            return false;
    }
    return true;
}



/*
Antécédent : un vecteur de vecteurs d'entiers, qui représente les données de la pièce
Conséquent : un pointeur sur pièce
Rôle : Attribue dynamiquement la classe adaptée à l'objet, s'il s'agit d'une pièce carrée, rectangulaire, ou quelconque
*/
Piece* PieceFactory::createPiece(const std::vector<std::vector<int>>& pieceData) {
    int rows = pieceData.size();
    int cols = pieceData[0].size();

    // Trouver les indices des lignes et colonnes avec des éléments de valeur 1
    std::vector<int> rowIndices;
    std::vector<int> colIndices;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (pieceData[i][j] == 1) {
                rowIndices.push_back(i);
                colIndices.push_back(j);
            }
        }
    }

    // Trouver les dimensions de la sous-matrice rectangulaire minimale
    int minRow = *std::min_element(rowIndices.begin(), rowIndices.end());
    int maxRow = *std::max_element(rowIndices.begin(), rowIndices.end());
    int minCol = *std::min_element(colIndices.begin(), colIndices.end());
    int maxCol = *std::max_element(colIndices.begin(), colIndices.end());

    int newRows = maxRow - minRow + 1;
    int newCols = maxCol - minCol + 1;

    // Créer la nouvelle matrice avec les dimensions minimales
    std::vector<std::vector<int>> minimizedPiece(newRows, std::vector<int>(newCols, 0));
    for (int i = minRow; i <= maxRow; ++i) {
        for (int j = minCol; j <= maxCol; ++j) {
            minimizedPiece[i - minRow][j - minCol] = pieceData[i][j];
        }
    }
    
     // On vérifie si la pièce est entièrement remplie de 1
    bool isFullyFilledPiece = true;
    for (const auto& row : minimizedPiece) {
        if (!isFullyFilled(row)) {
            isFullyFilledPiece = false;
            break;
        }
    }

    // Si la pièce est un carré
    if (isFullyFilledPiece && newRows == newCols) {
        std::cout<<"Création de la pièce carré terminée"<<std::endl;
        return new SquarePiece(minimizedPiece);
    }
    // Si la pièce est un rectangle (mais pas un carré)
    else if (isFullyFilledPiece && newRows != newCols) {
        std::cout<<"Création de la pièce rectangulaire terminée"<<std::endl;
        return new RectangularPiece(minimizedPiece);
    }
    // Pour toutes les autres formes
    else {
        std::cout<<"Création de la pièce terminée"<<std::endl;
        return new Piece(minimizedPiece);
    }

}
