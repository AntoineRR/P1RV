#pragma once

/*
	Brush.h�: Fichier d'en t�te de Brush.cpp
	Description : Fichier permettant la gestion du syst�me de brush
	Autheurs : FERRAND Edouard / ROMERO-ROMERO Antoine
	Date : 12/12/2018
*/

//============ INCLUDE =============

#include <vector>
#include <string>

// Jpeg lib
#include "Jpeg.h"

using namespace std;

//============= VARIABLES GLOBALES =============

// Taille du fichier JPG ouvert
extern unsigned long x, y;

class Brush {
	private:
		// Taille du brush initial en pixels
		unsigned long brushX;
		unsigned long brushY;
		
		// Nom du fichier � charger comme brush
		string id;

		// Hauteur maximale de dessin avec le brush
		int maxHeight;

		// Taille du brush (entre 1 et 5, 1 �tant le plus grand et 5 le plus petit)
		int tailleBrush;

		// Donn�e contenant le brush
		vector<int> *grayLevel;

		// Bool�en indiquant si on efface ou pas
		bool gomme;

	public:
		// Constructeurs
		Brush();
		Brush(string _id);

		// Getters
		unsigned long getX() const { return brushX; };
		unsigned long getY() const { return brushY; };
		string getId() const { return id; };
		int getMaxHeight() const { return maxHeight; };
		int getTaille() const { return tailleBrush; };
		vector<int>* getGrayLevel() const { return grayLevel; };
		bool getGomme() const { return gomme; };

		// Setters
		void setTaille();
		void setGomme(bool _gomme) { gomme = _gomme; };
		void setId(string _id);

		// Fonction permettant de charger un brush � partir d'un JPG carr�
		static void loadBrush(Brush *brush);
};