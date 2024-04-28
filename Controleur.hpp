#pragma once

#include "modele.hpp"
#include "Vue.hpp"



class Controleur {
    private:
        Modele *m;
        WindowTolePiece *v;
    public:
        Controleur(Modele *mm, WindowTolePiece *vv) : m(mm), v(vv) {
            this->on_button_generate();
            //this->on_button_exit();
        }
        
        void on_button_generate() {
            v->addGenerateListener(this);
        }
/*
        void on_button_exit() {
            v->addExitListener();
        }*/
                //std::vector<int>>& toleData, const std::vector<std::vector<int>>& pieceData
        void toGen() const {
            //this->m->Decoupage(this->m->getToleData(), pieceData);
            this->v->on_bouton_clicked();
        }
};