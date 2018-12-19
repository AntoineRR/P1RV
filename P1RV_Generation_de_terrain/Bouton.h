/*
 * Classe permettant d'instancier des boutons
*/

#pragma once

#include <string>
#include "Brush.h"
#include "Jpeg.h"

/*
	Classe mère de tous les boutons
	Une classe héritant de celle ci a été créée pour chaque bouton
	Cette classe gère les input de la souris
*/
class Bouton {
	private:
		int posX, posY;     // Position du bouton
		int width, height;      // Dimension du bouton
		bool clicked;      // Booléen indiquant si on appui sur le bouton

	public:
		// Constructeur
		Bouton();
		Bouton(int x, int y, int w, int h);

		// Getters
		int getX() const { return posX; };
		int getY() const { return posY; };
		int getWidth() const { return width; };
		int getHeight() const { return height; };
		bool getClicked() const { return clicked; };

		// Fonction de gestion du clic et du relachement du bouton
		bool onClick(int _x, int _y);
		void onRelease(Brush &brush);

		// Fonction de gestion de l'affichage du bouton
		virtual void onDraw() = 0;

		// Fonction indiquant l'effet du bouton
		virtual void effect(Brush &brush) = 0;
};

/*
	Bouton permettant de charger une image
*/
class BoutonCharger : public Bouton {
	public:
		// Constructeur
		BoutonCharger(int x, int y, int w, int h);

		// Redéfinition des fonctions virtuelles
		void onDraw();
		void effect(Brush &brush);
};

/*
	Bouton permettant de sauvegarder une image éditée
*/
class BoutonSauvegarder : public Bouton {
	public:
		// Constructeur
		BoutonSauvegarder(int x, int y, int w, int h);

		// Redéfinition des fonctions virtuelles
		void onDraw();
		void effect(Brush &brush);
};

/*
	Bouton permettant de charger un nouveau brush
*/
class BoutonChoixBrush : public Bouton {
	public:
		// Constructeur
		BoutonChoixBrush(int x, int y, int w, int h);

		// Redéfinition des fonctions virtuelles
		void onDraw();
		void effect(Brush &brush);
};

/*
	Bouton permettant de gérer la taille du brush
*/
class BoutonTailleBrush : public Bouton {
	private:
		// Pointeur vers le brush dont on doit changer la taille
		Brush* ptrBrush;

	public:
		// Constructeur
		BoutonTailleBrush(int x, int y, int w, int h, Brush *brush);

		// Redéfinition des fonctions virtuelles
		void onDraw();
		void effect(Brush &brush);
};

/*
	Bouton permettant d'effacer l'éditeur
*/
class BoutonClear : public Bouton {
	public:
		// Constructeur
		BoutonClear(int x, int y, int w, int h);

		// Redéfinition des fonctions virtuelles
		void onDraw();
		void effect(Brush &brush);
};

/*
	Fonction utilisée pour afficher du texte sur les boutons
	str : texte à afficher
	_x, _y : position du texte
*/
void afficherString(string str, int _x, int _y);