#include "tole.hpp"
#include "piece.hpp" 

//Rôle : Retourne le nombre de lignes de la tôle
int Tole::getRows() const {
    return tole.size();
}

//Rôle : Retourne le nombre de colonnes de la tôle
int Tole::getColumns() const {
    if (tole.empty()) {
        return 0;
    }
    return tole[0].size();
}



void Tole::set_data(const std::vector<std::vector<int>>& data) {
        this->tole = data;
    }

std::vector<std::vector<int>> Tole::get_data() const {
  return this->tole;
}


//Rôle : retourne la valeur de la cellule de la tôle dont les coordonnées sont passées en paramètres
int Tole::getCellValue(int row, int col) const {
    return tole[row][col];
}


/*
Antécédent : une Piece
Conséquent : un booléen
Rôle : Vérifier si le nombre de cases de la tôle est divisible par le nombre de cases de la pièce
*/
bool Tole::isSolvable(const Piece &piece) const {
    int emptyCells = 0;
    int pieceCells = 0;
    
    // Compte le nombre de cases vides dans la tôle
    for (const auto &row : tole) {
        for (int val : row) {
            if (val == 0)
                emptyCells++;
        }
    }
    
    // Compte le nombre de cases dans la pièce
    for (int i = 0; i < piece.getRows(); ++i) {
        for (int j = 0; j < piece.getColumns(); ++j) {
            if (piece.getCellValue(i, j) == 1)
                pieceCells++;
        }
    }
    
    // Vérifie si le nombre de cases vides est divisible par le nombre de cases dans la pièce
    return emptyCells % pieceCells == 0;
}



/*
Antécédent : une Piece, et deux entiers représentant des coordonnées (ligne,colonne)
Conséquent : un booléen
Rôle : Vérifie si la pièce peut être placée sur les coordonnées de la tôle
*/
bool Tole::isValidPlacement(const Piece &piece, int row, int col) const {
    int rows = getRows();
    int cols = getColumns();
    int pieceRows = piece.getRows();
    int pieceCols = piece.getColumns();
    
    // Test de la validité des coordonnées, pour ne pas dépasser la tôle
    if (row + pieceRows > rows || col + pieceCols > cols)
        return false;
    
    // Vérifie si la pièce chevauche une autre pièce ou un trou (-1 dans la tôle)
    for (int i = 0; i < pieceRows; ++i) {
        for (int j = 0; j < pieceCols; ++j) {
            if (piece.getCellValue(i, j) == 1) { 
                int toleRow = row + i;
                int toleCol = col + j;
                // Vérifie si la pièce chevauche un trou
                if (tole[toleRow][toleCol] == -1)
                    return false;
                // Vérifie si la pièce chevauche une autre pièce déjà placée
                if (tole[toleRow][toleCol] != 0)
                    return false;
            }
        }
    }
    return true;
}


/*
Antécédent : une Piece, deux entiers représentants des coordonnées, et le numéro de la pièce (entier)
Rôle : place la pièce numérotée sur les coordonnées de la tôle
*/
void Tole::placePiece(const Piece &piece, int row, int col, int pieceNum) {
    int pieceRows = piece.getRows();
    int pieceCols = piece.getColumns();
    for (int i = 0; i < pieceRows; ++i) {
        for (int j = 0; j < pieceCols; ++j) {
            if (piece.getCellValue(i, j) == 1)
                tole[row+i][col+j] = pieceNum;
        }
    }
}


/*
Antécédent : un entier représentant le numéro de la pièce
Rôle : enlève la pièce dont le numéro est passé en paramètre
*/
void Tole::removePiece(int pieceNum) {
    int rows = getRows();
    int cols = getColumns();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (tole[i][j] == pieceNum)
                tole[i][j] = 0;
        }
    }
}



//Rôle : Renvoie True si la tôle est entièrement remplie (plus aucun 0)
bool Tole::isFull() const {
    for (const auto& row : tole) {
        for (int val : row) {
            if (val == 0)
                return false;
        }
    }
    return true;
}
