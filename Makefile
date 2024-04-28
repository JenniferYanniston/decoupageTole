GTKMM_CF = `pkg-config gtkmm-3.0 --cflags`
GTKMM_LD = `pkg-config gtkmm-3.0 --libs`

CFLAGS = $(GTKMM_CF) -Wall # les options du compilateur
LDFLAGS = $(GTKMM_LD)      # les options pour l'éditeur de liens

CC = g++             # le compilateur à utiliser

SRC = Vue.cpp piece.cpp tole.cpp solver.cpp factory.cpp Grille.cpp Resultat.cpp Window.cpp mainn.cpp   # les fichiers sources
PROG = a.out          # nom de l'exécutable
OBJS =  $(SRC:.cpp=.o) # les .o qui en découlent
.SUFFIXES: .cpp .o     # lien entre les suffixes

all: $(PROG)

# étapes de compilation et d'édition de liens
# $@ la cible  $^ toutes les dépendances	
$(PROG): $(OBJS)
	$(CC)  -o $@ $^ $(LDFLAGS)

mainn.cpp : factory.cpp factory.hpp tole.cpp tole.hpp solver.cpp solver.hpp piece.hpp piece.cpp Vue.hpp Vue.cpp Window.cpp Grille.cpp Resultat.cpp modele.hpp Controleur.hpp

# le lien entre .o et .c
# $< dernière dépendance	
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

# pour faire propre
.PHONY: clean
clean:
	rm -f *.o *~ *.gch core $(PROG)



