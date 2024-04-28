#pragma once

#include "factory.hpp"
#include "solver.hpp"
#include "tole.hpp"
#include "piece.hpp"

class Modele {
private:
  Solver solver;
  Tole tole;
  Piece piece;
  
public:
  Modele(const Tole &t, const Piece &p) : tole(t), piece(p) {}

  std::vector<std::vector<int>> getToleData() const {
    return tole.get_data();
  }
  

  int Decoupage(const std::vector<std::vector<int>>& toleData, const std::vector<std::vector<int>>& pieceData){
    // Pour initialiser la tôle
    tole = Tole(toleData);
    
    // Pour initialiser la pièce
    Piece* piece = PieceFactory::createPiece(pieceData);
    
    // Pour initialiser le solveur
    solver = Solver();
    
    // On vérifie d'abord si le problème est solvable
    if (!tole.isSolvable(*piece)) {
      return 3;
    }
    
    // Prétraitement de la tôle 
    if (!solver.preprocess(tole, *piece)) {
      return 2;
    }
    
    // Découpage, on part de la pièce numéro 2 pour se distinguer des pièces posées par preprocess
    if (solver.solve(tole, *piece, 2)) {
      return 0;
    } else {
      return 1;
    }
  }
};


  
