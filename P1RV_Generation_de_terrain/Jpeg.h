/*
	Jpeg.h : Fichier d'en tête de Jpeg.cpp
	Description : Fonctions d'écriture et de lecture de Jpeg
	Auteurs : FERRAND Edouard / ROMERO-ROMERO Antoine
	Date : 12/12/2018
*/

#pragma once

//========== INCLUDE ==========

#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <tchar.h>

#include <vector>

// JPEG Lib
#include "jpeglib.h"
#include "jerror.h"

// OpenGL lib
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glext.h>

// pour la fonction loadHeightMap
#define EDITOR_WIDTH 640
#define EDITOR_HEIGHT 480

using namespace std;

// Variable de chargement du jpg
extern unsigned long x;
extern unsigned long y;

// Variables concernant l'image
extern vector<int> grayLevel;
extern int maxHeight;

//Taille de la zone d'édition de heightmap
extern int editorHeight;
extern int editorWidth;

// Rapport de la taille de l'éditeur en pixels à l'écran sur la taille en pixel de la heightmap éditable
extern float rapportPixel;

/*
	Fonction chargeant un fichier jpg en nuance de gris. Utilisée pour une heightmap ou un brush
	Renvoi les données de l'image dans dataImage et le max de hauteur de l'image dans maxGray
*/
bool loadJPEG(char* fileName, unsigned long &_x, unsigned long &_y, vector<int> &dataImage, int &maxGray);

/*
	Fonction enregistrant l'image dessinée sur l'éditeur dans un fichier jpg
*/
void saveJPEG(char* filename, unsigned long &_x, unsigned long &_y, vector<int> &dataImage, int maxGray);

/*
	Fonction permettant de modifier la valeur du max de hauteur de la heightmap si level>maxHeight
*/
void checkMax(int level, int &maxHeight);

/*
	Fonction permettant de charger une heightMap à partir du nom d'un fichier
	Renvoi un booléen indiquant si l'ouverture s'est bien déroulée
*/
bool loadHeightMap(char* FileName);

/*
	Fonction permettant de sauvegarder la heightmap. Elle est appelée uniquement avec fileName, ce qui permet de l'appeler depuis le fichier Bouton
*/
void saveHeightMap(char* FileName);

/*
	Fonction permettant d'ouvrir une fenêtre de l'explorateur windows, et de récupérer le nom du fichier sélectionné par l'utilisateur
*/
char* openFileExplorer();