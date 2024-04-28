#include <gtkmm.h>
#include "Vue.hpp"


Resultat::Resultat(const std::vector<std::vector<int>>& data)
  : grille(data[0].size(), data.size(), false) {
  set_default_size(400, 300);
  
  grille.set_data(data);
  box.set_orientation(Gtk::ORIENTATION_VERTICAL);
  box.pack_start(grille);
  
  
  boutonQuit.set_label("Quitter");

  boutonQuit.signal_clicked().connect(sigc::mem_fun(*this, &Resultat::on_bouton_quit_clicked));
  
  box.pack_start(boutonQuit);
  
  add(box);
  
  show_all_children();
}

bool Resultat::on_draw(const Cairo::RefPtr<Cairo::Context>& cr){
  // Définir la taille de la fenêtre
  int fenetre_largeur = 400; // Largeur de la fenêtre
  int fenetre_hauteur = 300; // Hauteur de la fenêtre
  set_size_request(fenetre_largeur, fenetre_hauteur);
  
  // Utiliser get_size_request pour obtenir la taille de la fenêtre
  int largeur, hauteur;
  get_size_request(largeur, hauteur);
  
  // Calculer la taille des cases
  double case_width = static_cast<double>(largeur) / grille.get_nb_cases_x();
  double case_height = static_cast<double>(hauteur) / grille.get_nb_cases_y();
  
  for (int i = 0; i < grille.get_nb_cases_x(); ++i) {
    for (int j = 0; j < grille.get_nb_cases_y(); ++j) {
      double x = i * case_width;
      double y = j * case_height;
      
      // Changer la couleur en fonction du numéro de la pièce
      if (grille.get_case_value(j, i) == -1) {
	cr->set_source_rgb(0, 0, 0);  // Noir pour les trous dans la tôle
      } else {
	// Utiliser une couleur différente pour chaque numéro de pièce, on multiplie par des constantes arbitraires afin de varier les tonalités
	cr->set_source_rgb((grille.get_case_value(j, i) * 23) % 256 / 255.0, (grille.get_case_value(j, i) * 42) % 256 / 255.0, (grille.get_case_value(j, i) * 73) % 256 / 255.0);
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

void Resultat::on_bouton_quit_clicked() {
        hide(); // Masquer la fenêtre lorsque le bouton "Quitter" est cliqué
    }
