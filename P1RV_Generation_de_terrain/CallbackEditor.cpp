#include "CallbackEditor.h"

//Taille de la zone d'édition de heightmap
int editorHeight = EDITOR_HEIGHT;
int editorWidth = EDITOR_WIDTH;

// Rapport de la taille de l'éditeur en pixels à l'écran sur la taille en pixel de la heightmap éditable
float rapportPixel = (float)editorWidth/(float)x;

// Brush utilisé
Brush brush = Brush("brush/brush_cercle_degrade.jpg");

// Tableau contenant tous les boutons affichés
vector<Bouton*> boutons;

// Booléens de gestion du click souris
bool clickG = false;
bool clickD = false;
bool clickBouton = false;

//=========== FONCTIONS DE CALLBACK =============

GLvoid affichageEditor() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	// Tracé de la zone de dessin
	// On trace des carrés correspondant à un pixel sur l'écran
	for(float i = 0; i < y; i++) {
		for(float j = 0; j < x; j++) {
			glBegin(GL_QUADS);
				// Modification de la couleur des carrés en fonction de la variable grayLevel
				glColor3f((float)grayLevel[(int)(i*x+j)]/(float)maxHeight, (float)grayLevel[(int)(i*x+j)]/(float)maxHeight, (float)grayLevel[(int)(i*x+j)]/(float)maxHeight);
				// Changement de la couleur des zones de l'éditeur qui n'ont pas encore été modifiées (pour une meilleure lisibilité)
				if(grayLevel[(int)(i*x+j)] == 0)
					glColor3f(0.4f, 0.4f, 0.6f);
				// Tracé des carrés
				glVertex2f(-(float)editorWidth/2.0+j*rapportPixel, -(float)editorHeight/2.0+i*rapportPixel);
				glVertex2f(-(float)editorWidth/2.0+(j+1.0)*rapportPixel, -(float)editorHeight/2.0+i*rapportPixel);
				glVertex2f(-(float)editorWidth/2.0+(j+1.0)*rapportPixel, -(float)editorHeight/2.0+(i+1.0)*rapportPixel);
				glVertex2f(-(float)editorWidth/2.0+j*rapportPixel, -(float)editorHeight/2.0+(i+1.0)*rapportPixel);
			glEnd();
		}
	}

	// Affichage des boutons
	for(int i = 0; i < boutons.size(); i++) {
		boutons[i]->onDraw();
	}

	glFlush();
	glutSwapBuffers();
}

GLvoid redimensionnerEditor(int w, int h) {
	glutReshapeWindow(windowWEditor, windowHEditor);

	glViewport(0,0,windowWEditor, windowHEditor);
	glMatrixMode(GL_PROJECTION); // Choisit la matrice de projection
	glLoadIdentity();
	
	gluOrtho2D(-windowWEditor/2,windowWEditor/2,-windowHEditor/2,windowHEditor/2);
	
	// Retourne a la pile modelview
	glMatrixMode(GL_MODELVIEW);
}

GLvoid sourisEditor(int bouton, int etat, int _x, int _y){
   // Test pour voir si le bouton gauche de la souris est enfoncé
    if(bouton == GLUT_LEFT_BUTTON && etat == GLUT_DOWN) {
		 clickG = true;

		// on verifie le click des boutons
		for(int i = 0; i < boutons.size(); i++) {
			if(boutons[i]->onClick(_x - windowWEditor/2, -(_y - windowHEditor/2)))
				clickBouton = true;
		}

		// Si on n'a pas clické sur un bouton, on applique le brush
		if(!clickBouton)
			appliquerBrush(_x, _y);
	}

    // si on relache le bouton gauche
    if(bouton == GLUT_LEFT_BUTTON && etat == GLUT_UP) {
		clickG = false;
		clickBouton = false;

		// on release les boutons
		 for(int i = 0; i < boutons.size(); i++) {
			boutons[i]->onRelease(brush);
		}

    }

	if(bouton == GLUT_RIGHT_BUTTON && etat == GLUT_DOWN) {
		clickD = true;
		brush.setGomme(true);

		if(!clickBouton)
			appliquerBrush(_x, _y);
	}

	if(bouton == GLUT_RIGHT_BUTTON && etat == GLUT_UP) {
		clickD = false;
		brush.setGomme(false);

		// Si on a gommé, le maximum e trouve ailleurs que dans la zone que l'on vient d'éditer.
		// Il faut donc faire une recherche de maximum sur tout grayLevel, ce qui ralenti un peut l'affichage de la heightmap
		// C'est pourquoi cette fonction n'est appelée que lorsqu'on relache le bouton après avoir gommé

		maxHeight = 0;
		for(int i = 0; i < grayLevel.size(); i++) {
			checkMax(grayLevel[i], maxHeight);
		}
		
		glutPostRedisplay();
	}
}

GLvoid deplacementSourisEditor(int _x, int _y) {
   // si le bouton gauche est appuye et qu'on se deplace
   // alors on doit modifier les angles de rotations du cube
   // en fonction de la derniere position de la souris 
   // et de sa position actuelle

    if(clickG) {
		// on verifie le click des boutons
		 for(int i = 0; i < boutons.size(); i++) {
			boutons[i]->onClick(_x - windowWEditor/2, -(_y - windowHEditor/2));
		}

		// Si on n'a pas clické sur un bouton, on applique le brush
		if(!clickBouton)
			appliquerBrush(_x, _y);
    }

	if(clickD) {
		brush.setGomme(true);

		if(!clickBouton)
			appliquerBrush(_x, _y);
	}

}

//=============== AUTRES FONCTIONS ==============

void initBoutons() {
	boutons = vector<Bouton*>();
	boutons.push_back(new BoutonCharger(-windowWEditor/2, windowHEditor/2-50, 100, 50));
	boutons.push_back(new BoutonSauvegarder(-windowWEditor/2+100, windowHEditor/2-50, 100, 50));
	boutons.push_back(new BoutonTailleBrush(windowWEditor/2-150, -windowHEditor/2, 150, 50, &brush));
	boutons.push_back(new BoutonChoixBrush(windowWEditor/2-300, -windowHEditor/2, 150, 50));
	boutons.push_back(new BoutonClear(-windowWEditor/2, -windowHEditor/2, 70, 50));
}

void cercle(int xEcran, int yEcran) {
	int r=300;     // Le rayon du cercle
	float max = 100, _x, _y;     // Augmentation maximale de la hauteur en 1 clic

	_y = windowHEditor - yEcran;

	_x = xEcran - (windowWEditor-editorWidth)/2;
	_y -= (windowHEditor-editorHeight)/2;

	_x /= rapportPixel;
	_y /= rapportPixel;

	// Pour tracer le cercle, on considère un carré de côté 2*r, et on teste si chacun de ses pixels se trouve dans le cercle ou pas.
	// On applique ensuite une hauteur au pixel en fonction de sa distance au centre du cercle, de manière à ce que cela forme une parabole pour la hauteur
	for(int j=_x-r; j<_x+r; j++) { 
		for(int i=_y-r; i<_y+r; i++) {
			if(i*x+j >= 0 && i*x+j < x*y && i >= 0 && i < y && j >= 0 && j < x) {
				float distance2 = (_x-j)*(_x-j) + (_y-i)*(_y-i);     // On laisse la distance au carré pour avoir une hauteur en parabole
				if(distance2<r*r) {
					grayLevel[i*x+j] += (r*r-distance2)*max/(float)(r*r);
					// Mise à jour de la hauteur maximale de la map
					checkMax(grayLevel[i*x+j], maxHeight);
				}
			}
		}
	}
	// Appeler le re-affichage de la scene OpenGL
	glutPostRedisplay();
}

void appliquerBrush(int xEcran, int yEcran) {
	
	float _x, _y;

	_y = windowHEditor - yEcran;

	_x = xEcran - (windowWEditor-editorWidth)/2;
	_y -= (windowHEditor-editorHeight)/2;

	_x /= rapportPixel;
	_y /= rapportPixel;

	// Ces casts sont INDISPENSABLES sinon on peut avoir de grosses différences entre l'endroit où l'on clique et celui où le brush s'affiche
	_x = (int)_x;
	_y = (int)_y;

	// Pour tracer le cercle, on considère un carré de côté 2*r, et on teste si chacun de ses pixels se trouve dans le cercle ou pas.
	// On applique ensuite une hauteur au pixel en fonction de sa distance au centre du cercle, de manière à ce que cela forme une parabole pour la hauteur
	for(int j=0; j<brush.getX(); j++) { 
		for(int i=0; i<brush.getY(); i++) {
			int indiceTableau = (i-(int)((float)brush.getY()/2.0)+_y)*x+j+_x-(int)((float)brush.getX()/2.0);

			if(indiceTableau >= 0 && indiceTableau < x*y && i-(int)(brush.getY()/2)+_y >= 0 && i-(int)(brush.getY()/2)+_y < y && j+_x-(int)(brush.getX()/2) >= 0 && j+_x-(int)(brush.getX()/2) < x) {
				int hauteur = (*brush.getGrayLevel())[i*brush.getX()+j];     // On récupère la valeur de la hauteur dans le brush

				if(!brush.getGomme()) {
					grayLevel[indiceTableau] += hauteur/2;
					// Mise à jour de la hauteur maximale de la map
					checkMax(grayLevel[indiceTableau], maxHeight);
				} 
				else {
					// Si on veut gommer, on gomme avec la forme du brush également
					grayLevel[indiceTableau] -= hauteur;
					if(grayLevel[indiceTableau] < 0)
						grayLevel[indiceTableau] = 0;
				}
			}
		}
	}

	// Appeler le re-affichage de la scene OpenGL
	glutPostRedisplay();

}