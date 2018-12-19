#include "Brush.h"

Brush::Brush() {
	grayLevel = new vector<int>();
	id = "0.jpg";
	tailleBrush = 3;
	loadBrush(this);

	gomme = false;
}

Brush::Brush(string _id) {
	grayLevel = new vector<int>();
	id = _id;
	tailleBrush = 3;
	loadBrush(this);

	gomme = false;
}

void Brush::loadBrush(Brush *brush) {
	string fileName = brush->id;
	// On utilise la fonction loadJPEG définie dans Jpeg.cpp
	loadJPEG((char*)fileName.c_str(), brush->brushX, brush->brushY, *brush->grayLevel, brush->maxHeight);
	
	// Initialisation du tableau qui contiendra le brush
	vector<int>* newGrayLevel = new vector<int>();
	
	int coteBrush = (int)((float)y/(3.0*(float)brush->tailleBrush));
	// calcul du ratio entre la taille de l'image chargées et de l'image que l'on souhaite avoir.
	float ratio = (float)brush->brushX/((float)coteBrush);

	for(int i=0; i<coteBrush; i++) {
		for(int j=0; j<coteBrush; j++) {
			newGrayLevel->push_back(0);
		}
	}

	// On rempli le brush avec les valeurs voulues
	for(int i=0; i<brush->brushY; i++) {
		for(int j=0; j<brush->brushX; j++) {
			int iBrush = (int)((float)i/ratio);
			int jBrush = (int)((float)j/ratio);
			(*newGrayLevel)[iBrush*coteBrush+jBrush] = (*brush->grayLevel)[i*brush->brushX+j];
		}
	}

	brush->grayLevel = newGrayLevel;
	brush->brushX = coteBrush;
	brush->brushY = coteBrush;
}

void Brush::setTaille() {
	tailleBrush++;
	// La taille évolue entre 1 et 5
	if(tailleBrush > 5) {
		tailleBrush = 1;
	}
	// On recharge le brush avec la nouvelle taille
	loadBrush(this);
}

void Brush::setId(string _id) {
	id = _id;      // Nom du fichier à charger
	// On recharge le nouveau brush
	loadBrush(this);
}