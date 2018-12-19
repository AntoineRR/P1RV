#pragma once

#include <iostream>
#include <vector>

using namespace std;

extern vector<vector<int> > couleurs;

class Couleur {

private:
	int finTransitionDebut;     // Indique la fin de l'interpolation avec la couleur pr�c�dente
	int debutTransitionFin;     // Indique le d�but de l'interpolation avec la couleur suivante
	vector<int> color;     // Contient le r,g et b de la couleur

public:
	static vector<Couleur> c;     // Contient chacune des couleurs affichables
	
	// Constructeur
	Couleur(int ftd, int dtf, int r, int v, int b);

	// Fonction initialisant les couleurs
	static void initCouleur();

	// Fonction permettant de calculer le vecteur couleurs utilis� par CallbackMap.cpp
	static void calculCouleur();

};

