#include <gtkmm.h>
#include "Vue.hpp"
#include "modele.hpp"
#include "Controleur.hpp"
#include "tole.hpp"
#include "piece.hpp"

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv);

    // Définir les données pour Tole et Piece
    std::vector<std::vector<int>> toleData; // Remplacez par les données appropriées
    std::vector<std::vector<int>> pieceData; // Remplacez par les données appropriées

    // Créer une nouvelle instance de Tole et Piece avec les données définies
    Tole t(toleData);
    Piece p(pieceData);

    // Créer une nouvelle instance de Modele avec les objets Tole et Piece
    Modele *m = new Modele(t, p);

    // Définir les valeurs pour WindowTolePiece
    int nb_cases_x_tole = 0; // Remplacez par la valeur appropriée
    int nb_cases_y_tole = 0; // Remplacez par la valeur appropriée
    int nb_cases_x_piece = 0; // Remplacez par la valeur appropriée
    int nb_cases_y_piece = 0; // Remplacez par la valeur appropriée

    // Créer une nouvelle instance de WindowTolePiece avec les valeurs définies
    Vue *v  = new Vue();
    WindowTolePiece *vg = new WindowTolePiece(nb_cases_x_tole, nb_cases_y_tole, nb_cases_x_piece, nb_cases_y_piece);

    // Créer une nouvelle instance de Controleur avec Modele et WindowTolePiece
    new Controleur(m, vg);

    // Exécuter l'application
    return app->run(*v);
}
