/*
	Main.cpp : définit le point d'entrée pour l'application console.
	Description : Fichier contenant les variables globales, la fonction principale, et la fonction d'initialisation de grayLevel
	Auteurs : FERRAND Edouard / ROMERO-ROMERO Antoine
	Date : 12/12/2018
*/

//========== INCLUDE ==========

#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <vector>

// OpenGL lib
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glext.h>

// JPEG lib
#include "jpeglib.h"
#include "jerror.h"

// Gestions des 2 fenêtres
#include "CallbackMap.h"
#include "CallbackEditor.h"

// Gestion des couleurs
#include "Couleur.h"

using namespace std;

//========== VARIABLES GLOBALES ===========

// Taille des fenêtres
int windowWEditor = 800;
int windowHEditor = 600;
int windowWMap = 640;
int windowHMap = 480;

// Variable de chargement du jpg
unsigned long x = 400;     // x de l'image chargée
unsigned long y = 300;     // y de l'image chargée

// Vecteur contenant les hauteurs de tous les points à afficher
vector<int> grayLevel;

// Infos de caméra
float focale = 65.0f;
float _near = 0.1f;
float _far = 100.0f;

// Ancienne position de la souris
GLint oldX;
GLint oldY;

// Hauteur maximale stockée dans grayLevel
int maxHeight = 0;

// Vecteur contenant toutes les couleurs utilisées pour le rendu 3D
vector<vector<int> > couleurs;

/**
	Fonction permettant l'initialisation et la réinitialisation de la variable grayLevel
	Cette variable contient des valeurs positives indiquant la hauteur de chaque pixel
**/
void initGrayLevel() {
	for(int i = 0; i< x*y ; i++)
		grayLevel.push_back(0);
	
	maxHeight = 0;
}

/**
	Fonction principale de l'application
**/
int main(int argc, char* argv[])
{

	// Initialisation de GLUT
	glutInit(&argc, argv);

	// Initialisation de la variable grayLevel
	initGrayLevel();
	
	//============ FENETRE DE LA MAP 3D ==========

		// Choix du mode d'affichage (ici RVB)
		glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

		// Position initiale de la fenetre GLUT
		glutInitWindowPosition(220+windowWEditor, 200);

		// Taille initiale de la fenetre GLUT
		glutInitWindowSize(windowWMap, windowHMap);

		// Initialisation des couleurs
		Couleur::initCouleur();

		// Creation de la fenetre GLUT
		glutCreateWindow("Map3D");

		// Définition de la couleur d'effacement du framebuffer
		glClearColor(0.2f, 0.0f, 0.0f, 0.0f);

		// Initialement on active le Z-buffer
		glEnable(GL_DEPTH_TEST);

		// Correction de la perspective
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		// Blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
		// Définition de la fonction d'affichage
		glutDisplayFunc(affichageMap);

		// Définition de la fonction de redimensionnement
		glutReshapeFunc(redimensionnerMap);

		// Définition des fonctions de gestion de la souris
		glutMouseFunc(sourisMap);
		glutMotionFunc(deplacementSourisMap);
	
	// ==============  FENETRE DE L'EDITEUR =============

		// Initialisation des boutons de l'application
		initBoutons();

		// Choix du mode d'affichage (ici RVB)
		glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

		// Position initiale de la fenetre GLUT
		glutInitWindowPosition(200, 200);

		// Taille initiale de la fenetre GLUT
		glutInitWindowSize(windowWEditor, windowHEditor);

		glutCreateWindow("HeightMap Editor");

		// Définition de la couleur d'effacement du framebuffer
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		// Blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Définition de la fonction d'affichage
		glutDisplayFunc(affichageEditor);

		// Définition de la fonction de redimensionnement
		glutReshapeFunc(redimensionnerEditor);

		// Définition des fonctions de gestion de la souris
		glutMouseFunc(sourisEditor);
		glutMotionFunc(deplacementSourisEditor);

	// Lancement de la boucle infinie GLUT
	glutMainLoop();

	return 0;
}

