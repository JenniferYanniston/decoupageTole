#include <gtkmm.h>
#include <iostream>
#include "Vue.hpp"
#include "Controleur.hpp"

Vue::Vue() {
        set_default_size(200, 100);

        box.set_orientation(Gtk::ORIENTATION_VERTICAL);
        add(box);

        labelTole.set_text("Veuillez entrer les dimensions de la tôle : ");
        box.pack_start(labelTole);
        box2.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
        labelLongueurTole.set_text("Longueur : ");
        box2.pack_start(labelLongueurTole);
        box2.pack_start(champSaisieXtole);
        labelLargeurTole.set_text("Largeur : ");
        box2.pack_start(labelLargeurTole);
        box2.pack_start(champSaisieYtole);
        box.pack_start(box2);

        labelPiece.set_text("Veuillez entrer les dimensions de la pièce : ");
        box.pack_start(labelPiece);
        box3.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
        labelLongueurPiece.set_text("Longueur : ");
        box3.pack_start(labelLongueurPiece);
        box3.pack_start(champSaisieXpiece);
        labelLargeurPiece.set_text("Largeur : ");
        box3.pack_start(labelLargeurPiece);
        box3.pack_start(champSaisieYpiece);
        box.pack_start(box3);

        bouton.set_label("Générer les éléments");
        box.pack_start(bouton);

        bouton.signal_clicked().connect(sigc::mem_fun(*this, &Vue::on_bouton_clicked));

        boutonQuit.set_label("Quitter");
        boutonQuit.signal_clicked().connect(sigc::mem_fun(*this, &Vue::on_bouton_quit_clicked));
        box.pack_start(boutonQuit);

        show_all_children();
    }

void Vue::on_bouton_clicked() {
    try {
        int nb_cases_x_tole = std::stoi(champSaisieXtole.get_text());
        int nb_cases_y_tole = std::stoi(champSaisieYtole.get_text());
        int nb_cases_x_piece = std::stoi(champSaisieXpiece.get_text());
        int nb_cases_y_piece = std::stoi(champSaisieYpiece.get_text());
        
        // Vérification des valeurs entrées (doivent être des entiers naturels non nuls)
        if (nb_cases_x_tole <= 0 || nb_cases_y_tole <= 0 || nb_cases_x_piece <= 0 || nb_cases_y_piece <= 0) {
            // Affichage de l'erreur sur l'interface graphique, on peut le faire avec Gtk::MessageDialog qui au lieu de l'afficher sur la sortie standard va afficher une fenêtre d'erreur
            Gtk::MessageDialog dialog(*this, "Erreur", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
            dialog.set_secondary_text("Les dimensions doivent être des entiers naturels non nuls.");
            dialog.run();
            return;
        }

        // Si les valeurs entrées sont valides, créer et afficher la fenêtre
        WindowTolePiece* f = new WindowTolePiece(nb_cases_x_tole, nb_cases_y_tole, nb_cases_x_piece, nb_cases_y_piece);
        f->show();
    } catch (const std::invalid_argument& e) {
        // Affichage de l'erreur sur l'interface graphique
        Gtk::MessageDialog dialog(*this, "Erreur", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
        dialog.set_secondary_text("Entrée invalide. Assurez-vous que toutes les entrées sont des entiers.");
        dialog.run();
    } catch (const std::out_of_range& e) {
        // Affichage de l'erreur sur l'interface graphique
        Gtk::MessageDialog dialog(*this, "Erreur", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
        dialog.set_secondary_text("La valeur entrée est trop grande.");
        dialog.run();
    }
}



void Vue::on_bouton_quit_clicked() {
  hide(); //Permet de quiiter le programme
}


