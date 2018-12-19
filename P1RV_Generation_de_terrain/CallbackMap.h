
/*
	CallbackMap.h�: Fichier d'en t�te de CallbackMap.cpp
	Description : Fichier permettant la gestion du rendu 3D de la map
	Auteurs : FERRAND Edouard / ROMERO-ROMERO Antoine
	Date : 12/12/2018
*/

#pragma once

//========== INCLUDE ==========

#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <vector>

// OpenGL lib
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glext.h>

// Utilis� pour avoir la fonction checkMax
#include "Jpeg.h"

using namespace std;

// =========== VARIABLES GLOBALES =========
// Taille de la fen�tre
extern int windowWMap;
extern int windowHMap;

// Variable de chargement du jpg
extern unsigned long x;
extern unsigned long y;

extern vector<int> grayLevel;

// Infos de cam�ra
extern float focale;
extern float _near;
extern float _far;

// Hauteur max de la map
extern int maxHeight;

// Couleurs
extern vector<vector<int> > couleurs;

// Ancienne position de la souris
extern GLint oldX;
extern GLint oldY;

// ========== DEFINITION DES FONCTIONS DE CALLBACK ==========

// Fonction de redimensionnement de la fen�tre
GLvoid redimensionnerMap(int w, int h);

// Fonction d'affichage de la map
GLvoid affichageMap();

// Fonctions de gestion de la souris
GLvoid sourisMap(int bouton, int etat, int _x, int _y);
GLvoid deplacementSourisMap(int _x, int _y);

// ========== DEFINITION DES AUTRES FONCTIONS ============

/*
	Fonction de r�ajustement de la hauteur maximale du mod�le 3D, appel�e au clic molette
	deltaHeight : diff�rence entre la hauteur actuelle et la nouvelle hauteur
*/
void scaleGrayLevel(int deltaHeight);
