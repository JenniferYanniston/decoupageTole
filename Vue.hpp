#pragma once

#include <gtkmm.h>
class Controleur;

class Grille : public Gtk::DrawingArea {
public:
  Grille(int nb_cases_x, int nb_cases_y, bool isPiece);
  std::vector<std::vector<int>> get_data() const;
  void set_data(const std::vector<std::vector<int>>& data);
  int get_case_value(int row, int col) const;
  int get_nb_cases_x() const;
  int get_nb_cases_y() const;
  bool isValidPiece(const std::vector<std::vector<int>>& pieceData);


protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  bool on_button_press_event(GdkEventButton* button_event) override;
        

private:
    int nb_cases_x;
    int nb_cases_y;
    bool isPiece;
    std::vector<std::vector<int>> grille;
};



class Resultat : public Gtk::Window {
private:
  Gtk::Box box;
  Grille grille;
  Gtk::Button boutonQuit;
protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  

public:
  Resultat(const std::vector<std::vector<int>>& data);
  void on_bouton_quit_clicked();
};


class WindowTolePiece : public Gtk::Window {
private:
    Gtk::Box box;
    Gtk::Button bouton, boutonQuit;
    Gtk::Label labelTole, labelPiece;
    Grille tole;
    Grille piece;

public:
  WindowTolePiece(int nb_cases_x_tole, int nb_cases_y_tole, int nb_cases_x_piece, int nb_cases_y_piece);

  void on_bouton_clicked();
  void on_bouton_quit_clicked();
  void addGenerateListener(Controleur *c);
};

class Vue : public Gtk::Window {
private:
    Gtk::Box box, box2, box3;
    Gtk::Button bouton, boutonQuit;
    Gtk::Label labelTole, labelPiece;
    Gtk::Label labelLongueurTole, labelLargeurTole;
    Gtk::Label labelLongueurPiece, labelLargeurPiece;
    Gtk::Entry champSaisieXtole;
    Gtk::Entry champSaisieYtole;
    Gtk::Entry champSaisieXpiece;
    Gtk::Entry champSaisieYpiece;

public:
  Vue();

  void on_bouton_clicked();
  void on_bouton_quit_clicked();
  
};
