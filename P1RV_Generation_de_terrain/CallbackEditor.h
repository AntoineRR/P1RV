#pragma once

/*
	CallbackEditor.h : Fichier d'en tête de CallbackEditor.cpp
	Description : Fichier permettant la gestion de l'éditeur de heightmap
	Auteurs : FERRAND Edouard / ROMERO-ROMERO Antoine
	Date : 12/12/2018
*/

//========== INCLUDE ==========

#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <tchar.h>
#include <vector>

// OpenGL lib
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glext.h>

// JPEG lib
#include "Jpeg.h"

// Boutons
#include "Bouton.h"

// Brush
#include "Brush.h"

// Map
#include "CallbackMap.h"

using namespace std;

// =========== RECUPERATION DES VARIABLES GLOBALES =========

// Taille de la fenêtre
extern int windowWEditor;
extern int windowHEditor;

// Variable de chargement du jpg
extern unsigned long x;
extern unsigned long y;

// Vecteur contenant les hauteurs de tous les points à afficher
extern vector<int> grayLevel;

// Infos de caméra
extern float focale;
extern float _near;
extern float _far;

// Hauteur maximale stockée dans grayLevel
extern int maxHeight;

//========== DEFINITION DES FONCTIONS DE CALLBACK ==========

// Fonction de redimensionnement de la fenêtre
GLvoid redimensionnerEditor(int w, int h);

// Fonction d'affichage de la map
GLvoid affichageEditor();

// Fonctions de gestion de la souris
GLvoid sourisEditor(int bouton, int etat, int _x, int _y);
GLvoid deplacementSourisEditor(int _x, int _y);

//========= DEFINITION DES AUTRES FONCTIONS ==========

/*
	Initialisation des boutons affichés sur l'éditeur
*/
void initBoutons();

/*
	Fonction permettant de générer un brush de cercle, inaccessible dans l'application finale
	_x et _y représentent la position de la souris au moment du clic
*/
void cercle(int _x, int _y);

/*
	Fonction permettant d'afficher la forme correspondant au brush sélectionné sur l'éditeur
	xEcran et yEcran représentent la position de la souris au moment du clic
*/
void appliquerBrush(int xEcran, int yEcran);

