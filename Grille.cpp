#include <gtkmm.h>
#include <iostream>
#include "Vue.hpp"

Grille::Grille(int nb_cases_x, int nb_cases_y, bool isPiece) : nb_cases_x(nb_cases_x), nb_cases_y(nb_cases_y), isPiece(isPiece) {
  set_size_request(400, 300);
  add_events(Gdk::BUTTON_PRESS_MASK);
  grille = std::vector<std::vector<int>>(nb_cases_y, std::vector<int>(nb_cases_x, 0));
}

std::vector<std::vector<int>> Grille::get_data() const {
  return grille;
}

void Grille::set_data(const std::vector<std::vector<int>>& data) {
  grille = data;
  queue_draw();
}

int Grille::get_case_value(int row, int col) const {
  return grille[row][col];
}

int Grille::get_nb_cases_x() const {
  return nb_cases_x;
}

int Grille::get_nb_cases_y() const {
  return nb_cases_y;
}

/*
Antécédent : un vecteur de vecteurs d'entiers qui représente les données d'une pièce
Conséquent : un booléen
Rôle : Vérifie si la pièce est valide ( pas une matrice de 0, et les cases sont reliées entre elles)
*/
bool Grille::isValidPiece(const std::vector<std::vector<int>>& pieceData) {
    int sum = 0;
    bool foundOne = false;
    int rows = pieceData.size();
    int cols = (rows > 0) ? pieceData[0].size() : 0;

    // Parcourir la pièce pour calculer la somme et vérifier si un 1 est isolé
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            sum += pieceData[i][j]; // On fait à la somme (pour vérifier qu'il y ait au mois une case à 1)
            if (pieceData[i][j] == 1) {
                foundOne = true; // On a trouvé au moins un 1
                // On vérifie si ce 1 est connecté à d'autres 1
                if ((i > 0 && pieceData[i - 1][j] == 1) || // Haut
                    (i < rows - 1 && pieceData[i + 1][j] == 1) || // Bas
                    (j > 0 && pieceData[i][j - 1] == 1) || // Gauche
                    (j < cols - 1 && pieceData[i][j + 1] == 1)) { // Droite
                    continue; // Connecté, on passe au suivant
                } else {
		  if (sum==1){
		    continue;//Les pièces composées d'une seule case sont, certes peu intéressantes, mais valides
		  }
                    return false; // Non connecté, pièce invalide
                }
            }
        }
    }

    return foundOne && sum>0; // On retourne true s'il la pièce est non vide, et que ses éléments son reliés entre eux
}



bool Grille::on_draw(const Cairo::RefPtr<Cairo::Context>& cr){
  // Définir la taille de la fenêtre
  int fenetre_largeur = 400; // Largeur de la fenêtre
  int fenetre_hauteur = 300; // Hauteur de la fenêtre
  set_size_request(fenetre_largeur, fenetre_hauteur);
  
  // Utiliser get_size_request pour obtenir la taille de la fenêtre
  int largeur, hauteur;
  get_size_request(largeur, hauteur);
  
  // Calculer la taille des cases
  double case_width = static_cast<double>(largeur) / nb_cases_x;
  double case_height = static_cast<double>(hauteur) / nb_cases_y;
  
  for (int i = 0; i < nb_cases_x; ++i) {
    for (int j = 0; j < nb_cases_y; ++j) {
      double x = i * case_width;
      double y = j * case_height;
      
      // Pour changer la couleur des grilles (tole et piece)
      if (grille[j][i]) {
	if (isPiece) {
	  cr->set_source_rgb(0.0, 0.0, 1.0);  // Bleu pour la pièce (c'est pour les cases à mettre)
	} else {
	  cr->set_source_rgb(1.0, 0.0, 0.0);  // Rouge pour la tole (c'est pour les cases à enlever)
	}
      } else {
	cr->set_source_rgb(0.8, 0.8, 0.8);  // Gris pour celles qu'on ne touche pas
      }
      
      cr->rectangle(x, y, case_width, case_height);
      cr->fill();
      
      cr->set_source_rgb(0, 0, 0);
      cr->set_line_width(1.0);
      cr->rectangle(x, y, case_width, case_height);
      cr->stroke();
    }
  }
  
  return true;
}

bool Grille::on_button_press_event(GdkEventButton* button_event){
  // Définir la taille de la fenêtre
  int fenetre_largeur = 400; // Largeur de la fenêtre
  int fenetre_hauteur = 300; // Hauteur de la fenêtre
  set_size_request(fenetre_largeur, fenetre_hauteur);
  
  // Utiliser get_size_request pour obtenir la taille de la fenêtre
  int largeur, hauteur;
  get_size_request(largeur, hauteur);
  
  // Calculer la taille des cases
  double case_width = static_cast<double>(largeur) / nb_cases_x;
  double case_height = static_cast<double>(hauteur) / nb_cases_y;
  
  int clicked_row = static_cast<int>(button_event->y / case_height);
  int clicked_col = static_cast<int>(button_event->x / case_width);
  
  // Pour changer l'état de la case sur laquelle on clique, conformément à la définition de la piece et de la tole (-1 pour les cases vides de la tole, 1 pour les cases de la pièce)
  // On remet à 0 si l'on clique une deuxième fois dessus
  grille[clicked_row][clicked_col] = (grille[clicked_row][clicked_col] == 0) ? (isPiece ? 1 : -1) : 0;
  
  // Redessiner la grille
  queue_draw();
  
  return true;
}


