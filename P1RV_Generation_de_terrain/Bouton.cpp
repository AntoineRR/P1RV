#include "Bouton.h"


//=============== BOUTON =======================

Bouton::Bouton() {
	posX = 0;
	posY = 0;
	width = 20;
	height = 20;

	clicked = false;
}

Bouton::Bouton(int x, int y, int w, int h) {
	posX = x;
	posY = y;
	width = w;
	height = h;

	clicked = false;
}

bool Bouton::onClick(int _x, int _y) {
	// Détection du clic sur le bouton
	if(_x >= posX && _x <= posX + width && _y >= posY && _y <= posY + height) {
		clicked = true;
	}
	else {
		clicked = false;
	}
	glutPostRedisplay();

	return clicked;
}

void Bouton::onRelease(Brush &brush) {
	// Relachement du bouton
	if(clicked) {
		effect(brush);     // On applique l'effet au relachement
	}
	clicked = false;
}


//============= BOUTON CHARGER ====================

BoutonCharger::BoutonCharger(int x, int y, int w, int h) : Bouton(x, y, w, h) { }

void BoutonCharger::effect(Brush &brush) {
	char* fileName = openFileExplorer();     // On ouvre une fenêtre d'explorateur windows
	if(fileName != "error") {
		loadHeightMap(fileName);     // Chargement de la heightmap
		Brush::loadBrush(&brush);     // Chargement du brush
	}

	glutPostRedisplay();
}

void BoutonCharger::onDraw() {
	glBegin(GL_QUADS);
		// Changement de la couleur en fonction de l'appui
		if(getClicked())
			glColor3f(1.0, 0.0, 0.0);
		else
			glColor3f(0.8, 0.0, 0.0);
		// Dessin du bouton
		glVertex2f(getX(), getY());
		glVertex2f(getX()+getWidth(), getY());
		glVertex2f(getX()+getWidth(), getY()+getHeight());
		glVertex2f(getX(), getY()+getHeight());
	glEnd();

	// Affichage du texte sur le bouton
	string strBouton = "Open";
	afficherString(strBouton, getX()+getWidth()/2, getY()+getHeight()/2);
}


//============== BOUTON SAUVEGARDER ===============

BoutonSauvegarder::BoutonSauvegarder(int x, int y, int w, int h) : Bouton(x, y, w, h) { }

void BoutonSauvegarder::effect(Brush &brush) {
	char* fileName = openFileExplorer();     // On ouvre une fenêtre d'explorateur windows
	if(fileName != "error") {
		saveHeightMap(fileName);     // On sauvegarde l'éditeur en cours
	}

	glutPostRedisplay();
}

void BoutonSauvegarder::onDraw() {
	glBegin(GL_QUADS);
		// Changement de la couleur en fonction de l'appui
		if(getClicked())
			glColor3f(0.0, 1.0, 1.0);
		else
			glColor3f(0.0, 0.8, 0.8);
		// Dessin du bouton
		glVertex2f(getX(), getY());
		glVertex2f(getX()+getWidth(), getY());
		glVertex2f(getX()+getWidth(), getY()+getHeight());
		glVertex2f(getX(), getY()+getHeight());
	glEnd();

	// Affichage du texte sur le bouton
	string strBouton = "Save as";
	afficherString(strBouton, getX()+getWidth()/2, getY()+getHeight()/2);
}

//================ BOUTON CHOIX DU BRUSH =================

BoutonChoixBrush::BoutonChoixBrush(int x, int y, int w, int h) : Bouton(x, y, w, h) { 
}

void BoutonChoixBrush::effect(Brush &brush) {
	char* fileName = openFileExplorer();     // On ouvre une fenêtre d'explorateur windows
	if(fileName != "error") {
		brush.setId(fileName);     // On change l'id du brush (ce qui le rechage)
	}

	glutPostRedisplay();
}

void BoutonChoixBrush::onDraw() {
	glBegin(GL_QUADS);
		// Changement de la couleur en fonction de l'appui
		if(getClicked())
			glColor3f(0.0, 1.0, 0.0);
		else
			glColor3f(0.0, 0.8, 0.0);
		// Dessin du bouton
		glVertex2f(getX(), getY());
		glVertex2f(getX()+getWidth(), getY());
		glVertex2f(getX()+getWidth(), getY()+getHeight());
		glVertex2f(getX(), getY()+getHeight());
	glEnd();

	// Affichage du texte sur le bouton
	string strBouton = "Choose Brush";
	afficherString(strBouton, getX()+getWidth()/2, getY()+getHeight()/2);
}

//================ BOUTON TAILLE ===================

BoutonTailleBrush::BoutonTailleBrush(int x, int y, int w, int h, Brush *brush) : Bouton(x, y, w, h) { 
	ptrBrush = brush;     // Brush dont on doit changer la taille
}

void BoutonTailleBrush::effect(Brush &brush) {
	brush.setTaille();     // Changement de la taille du brush

	glutPostRedisplay();
}

void BoutonTailleBrush::onDraw() {
	glBegin(GL_QUADS);
		// Changement de la couleur en fonction de l'appui
		if(getClicked())
			glColor3f(1.0, 0.0, 1.0);
		else
			glColor3f(0.8, 0.0, 0.8);
		// Dessin du bouton
		glVertex2f(getX(), getY());
		glVertex2f(getX()+getWidth(), getY());
		glVertex2f(getX()+getWidth(), getY()+getHeight());
		glVertex2f(getX(), getY()+getHeight());
	glEnd();

	// Affichage du texte sur le bouton
	string strBouton = "Size : "+std::to_string(6-ptrBrush->getTaille());
	afficherString(strBouton, getX()+getWidth()/2, getY()+getHeight()/2);
}


//================ BOUTON CLEAR ===================

BoutonClear::BoutonClear(int x, int y, int w, int h) : Bouton(x, y, w, h) {}

void BoutonClear::effect(Brush &brush) {
	// Réinitialisation de grayLevel
	grayLevel = vector<int>();
	for(int i = 0; i< x*y ; i++)
		grayLevel.push_back(0);
	
	// Réinitialisation de la hauteur maximale de la heightmap
	maxHeight = 0;

	glutPostRedisplay();
}

void BoutonClear::onDraw() {
	glBegin(GL_QUADS);
		// Changement de la couleur en fonction de l'appui
		if(getClicked())
			glColor3f(1.0, 1.0, 1.0);
		else
			glColor3f(0.8, 0.8, 0.8);
		// Dessin du bouton
		glVertex2f(getX(), getY());
		glVertex2f(getX()+getWidth(), getY());
		glVertex2f(getX()+getWidth(), getY()+getHeight());
		glVertex2f(getX(), getY()+getHeight());
	glEnd();

	// Affichage du texte sur le bouton
	string strBouton = "Clear";
	afficherString(strBouton, getX()+getWidth()/2, getY()+getHeight()/2);
}

//=============== FONCTIONS UTILES =================

void afficherString(string str, int _x, int _y) {
	glColor3f(0.0, 0.0, 0.0);     // On écrit en noir

	glRasterPos2f(_x-glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)str.c_str())/2, _y-10);     // On fixe la position en fonction de la taille du string à afficher
	for(std::string::iterator c = str.begin(); c < str.end(); c++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);     // Affichage du string caractère par caractère
}