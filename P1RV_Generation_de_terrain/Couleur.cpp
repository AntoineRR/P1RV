#include "Couleur.h"

vector<Couleur> Couleur::c = vector<Couleur>();     // Initialisation de c, variable statique

Couleur::Couleur(int ftd, int dtf, int r, int v, int b) {
	finTransitionDebut = ftd;
	debutTransitionFin = dtf;
	color.push_back(r);
	color.push_back(v);
	color.push_back(b);
}

void Couleur::initCouleur() {

	// Eaux profondes
	c.push_back(Couleur(0, 10, 0, 38, 255));
	// Eaux peu profondes
	c.push_back(Couleur(25, 35, 38, 175, 255));
	// Sable
	c.push_back(Couleur(45, 55, 255, 235, 109));
	// Colline
	c.push_back(Couleur(65, 100, 38, 163, 45));
	// Foret
	c.push_back(Couleur(115, 135, 38, 89, 45));
	// Montagne
	c.push_back(Couleur(150, 175, 100, 100, 100));
	// Neige
	c.push_back(Couleur(195, 255, 244, 255, 244));

	calculCouleur();

}

void Couleur::calculCouleur() {

	cout << "Calcul des couleurs" << endl;
	int compteur;

	// Il y a 255 couleurs possibles dans couleurs
	for(int j=0; j<255; j++) {
		int r=0, v=0, b=0;
		compteur = 0;

		for(int i = 0; i<c.size(); i++) {
			// interpolation linéaire entre les couleurs
			if(i != 0 && j >= c[i-1].debutTransitionFin && j < c[i].finTransitionDebut) {
				couleurs.push_back(vector<int>());
				float a, b;
				for(int k = 0; k < 3; k++) {
					// Calcul des indices nécessaires à l'interpolaiton
					a = (float)(c[i].color[k]-c[i-1].color[k])/(float)(c[i].finTransitionDebut-c[i-1].debutTransitionFin);
					b = (float)c[i].color[k]-a*(float)c[i].finTransitionDebut;

					couleurs[couleurs.size()-1].push_back((int)(a*(float)j+b));
				}
			}
			// Si on est pas dans la zone d'interpolation des couleurs, on rempli couleurs avec la couleur en cours
			else if(j >= c[i].finTransitionDebut && j < c[i].debutTransitionFin) {
				couleurs.push_back(vector<int>());
				for(int k = 0; k < 3; k++) {
					couleurs[couleurs.size()-1].push_back(c[i].color[k]);
				}
			}
		}
	}

}

