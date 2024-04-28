#include "solver.hpp"
#include <iostream>


/*
Antécédent : la Tole, une Piece, et un entier représentant le numéro de la pièce
Conséquent : un booléen
Rôle : Découpe la tôle avec la pièce, si c'est possible. Renvoie True si c'est le cas.
*/
bool Solver::solve(Tole& tole, Piece& piece, int pieceNum) {
        
    int rows = tole.getRows();
    int cols = tole.getColumns();
    std::vector<Piece> rotations = piece.getAllRotations();
    
    // Parcourir toutes les cases du plateau
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            // Essayer toutes les orientations possibles de la pièce
            
            for (const Piece& rotatedPiece : rotations) {
                // Si le placement est valide, on place la pièce en question
                if (tole.isValidPlacement(rotatedPiece, row, col)) {
                    tole.placePiece(rotatedPiece, row, col, pieceNum);
                // Récursivité, on recommence avec la pièce suivante    
                if (solve(tole, piece, pieceNum + 1))
                    return true;
                // Si ca n'a pas fonctionné, on supprime la pièce et on revient en arrière    
                tole.removePiece(pieceNum);
                }
            }
        }
    }
    // Vérifier si le plateau est entièrement rempli
    return tole.isFull();
}

/*
Antécédent : la Tole, la Piece, et deux entiers pour les coordonnées d'une case
Conséquent : un booléen
Rôle : Essayer de placer une pièce à toutes les positions possibles autour d’une case spécifique
*/
bool Solver::tryAllPositions(Tole& tole, const Piece& piece, int adjRow, int adjCol) {
    int rows = tole.getRows();
    int cols = tole.getColumns();
     // Parcours de toutes les lignes possibles pour placer la pièce autour de la position adjacente
    for (int r = -piece.getRows()+1; r < piece.getRows(); ++r) {
         // Parcours de toutes les colonnes possibles pour placer la pièce autour de la position adjacente
        for (int c = -piece.getColumns()+1; c < piece.getColumns(); ++c) {
            int placeRow = adjRow + r;
            int placeCol = adjCol + c;
            // Vérifie si la position calculée est valide pour placer la pièce
            if (placeRow >= 0 && placeRow + piece.getRows() <= rows && placeCol >= 0 && placeCol + piece.getColumns() <= cols && tole.isValidPlacement(piece, placeRow, placeCol)) {
                tole.placePiece(piece, placeRow, placeCol, 1);
                return true; 
            }
        }
    }
    return false;
}



/*
Antécédent : la Tole, et la Piece
Conséquent : un booléen
Rôle : Parcours une copie de la tôle pour essayer d'y placer la piece dans toutes ses orientations, en incrémentant les cases de la tôle
       S'il existe après ça au moins une case à 0, alors il n'y a pas de solutions. S'il existe une case à 1, on y place une pièce.
*/
bool Solver::preprocess(Tole& tole, Piece& piece) {
    int rows = tole.getRows();
    int cols = tole.getColumns();
    std::vector<Piece> rotations = piece.getAllRotations();

    // Créer une copie de la tôle pour compter les placements possibles
    std::vector<std::vector<int>> placementCounts(rows, std::vector<int>(cols, 0));
    std::vector<std::vector<const Piece*>> placementPieces(rows, std::vector<const Piece*>(cols, nullptr));

    for (const Piece &rotatedPiece : rotations) {
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (tole.isValidPlacement(rotatedPiece, row, col)) {
                    // Incrémenter les cases occupées par la pièce
                    for (int i = 0; i < rotatedPiece.getRows(); ++i) {
                        for (int j = 0; j < rotatedPiece.getColumns(); ++j) {
                            if (rotatedPiece.getCellValue(i, j) == 1) {
                                placementCounts[row+i][col+j]++;
                                placementPieces[row+i][col+j] = &rotatedPiece;
                            }
                        }
                    }
                }
            }
        }
    }

    // Vérifier si toutes les cases peuvent être remplies
    // Parcourir la tôle pour trouver une case à 0
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (placementCounts[row][col] == 0 && tole.getCellValue(row, col) != -1) {
                // Cette case ne peut pas être remplie
                return false;
            }
        }
    }

    // Vérifier si une case peut être remplie par une seule configuration de pièce
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (placementCounts[row][col] == 1 && tole.getCellValue(row, col) != -1) {
                // Essayer de placer la pièce sur cette case
                if (tryAllPositions(tole, *placementPieces[row][col], row, col)) {
		  //On place la pièce, mais pas de return ici car il y a peut être plusieurs pièces à placer
                }
            }
        }
    }
    //Toutes les cases peuvent être remplies
    return true;
}



