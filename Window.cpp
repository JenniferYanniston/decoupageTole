#include <gtkmm.h>
#include <iostream>
#include "solver.hpp"
#include "factory.hpp"
#include "Vue.hpp"
#include "modele.hpp"
#include "Controleur.hpp"


WindowTolePiece::WindowTolePiece(int nb_cases_x_tole, int nb_cases_y_tole, int nb_cases_x_piece, int nb_cases_y_piece) 
  : tole(nb_cases_x_tole, nb_cases_y_tole, false), piece(nb_cases_x_piece, nb_cases_y_piece, true) {
  set_default_size(800, 600);
  
  box.set_orientation(Gtk::ORIENTATION_VERTICAL);
  add(box);
  
  labelTole.set_text("Veuillez saisir les cases de la tôle à enlever : ");
  box.pack_start(labelTole);
  box.pack_start(tole);
  
  Gtk::Label *espace = Gtk::manage(new Gtk::Label(" "));
  box.pack_start(*espace);
  
  labelPiece.set_text("Dessinez la forme de pièce que vous souhaitez en cochant les cases : ");
  box.pack_start(labelPiece);
  box.pack_start(piece);
  
  bouton.set_label("Générer la solution");  
  bouton.signal_clicked().connect(sigc::mem_fun(*this, &WindowTolePiece::on_bouton_clicked));
  box.pack_start(bouton);

  boutonQuit.set_label("Quitter");
  boutonQuit.signal_clicked().connect(sigc::mem_fun(*this, &WindowTolePiece::on_bouton_quit_clicked));
  box.pack_start(boutonQuit);
  
  show_all_children();
}

void WindowTolePiece::on_bouton_clicked() {
    // Récupérer les données de la tôle et de la pièce à partir des grilles
    std::vector<std::vector<int>> toleData = tole.get_data();
    std::vector<std::vector<int>> pieceData = piece.get_data();

    // Si la pièce est une matrice de zéros, alors on affiche un message d'erreur (l'utilisateur n'a cliqué sur aucune case et la pièce n'est pas initialisée)
    if (!piece.isValidPiece(pieceData)) {
        Gtk::MessageDialog dialog(*this, "Erreur", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
        dialog.set_secondary_text("La pièce est invalide. Il faut qu'elle contiennent AU MOINS une case. De plus, il doit s'agir d'une pièce correcte (les cases doivent être reliées entre elles). Vous pouvez cliquer sur les cases pour les ajouter à la pièce.");
        dialog.run();
        return;
    }

    Modele modele(toleData, pieceData);

    switch(modele.Decoupage(toleData, pieceData)) {
    case 3:
        {
            Gtk::MessageDialog dialog(*this, "Information", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);
            dialog.set_secondary_text("Pas de solutions possibles (Le nombre de cases dans la pièce ne permet pas de remplir entièrement la tôle)");
            dialog.run();
            return;
        }
    case 2:
        {
            Gtk::MessageDialog dialog(*this, "Information", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);
            dialog.set_secondary_text("Pas de solutions possibles (Il existe au moins une case que la pièce ne peut jamais atteindre)");
            dialog.run();
            return;
        }
    case 1:
        {
            Gtk::MessageDialog dialog(*this, "Information", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);
            dialog.set_secondary_text("Aucune solution trouvée.");
            dialog.run();
            break;
        }
    case 0:
        {
            Gtk::MessageDialog dialog(*this, "Information", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);
            dialog.set_secondary_text("Solution trouvée.");
            dialog.run();

	    // Récupérer les nouvelles données de la grille tole depuis le modèle
	    std::vector<std::vector<int>> newToleData = modele.getToleData();
	    
	    // Mettre à jour la grille tole avec les nouvelles données
	    tole.set_data(newToleData);
	    

            // Créer une nouvelle fenêtre pour afficher le résultat
            Resultat* resultat = new Resultat(tole.get_data());
            resultat->show();
	    // On rend la forme initiale de la tôle après l'affichage du résultat
	    tole.set_data(toleData);
            break;
        }
    default:
        {
            // Gestion d'une erreur non prévue
            Gtk::MessageDialog dialog(*this, "Erreur", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
            dialog.set_secondary_text("Erreur inattendue.");
            dialog.run();
            break;
        }
    }
}


void WindowTolePiece::on_bouton_quit_clicked() {    
  hide(); // Permet de quitter le programme
}

void WindowTolePiece::addGenerateListener(Controleur *c){
    this->bouton.signal_clicked().connect(sigc::mem_fun(*c, &Controleur::toGen));
}

