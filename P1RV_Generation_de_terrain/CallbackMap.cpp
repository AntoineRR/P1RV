#include "CallbackMap.h"

// Variables de gestion du zoom
float zoom = 2.0, coeffZoom = 0.1;

// Variables de gestion des clicks souris
bool rightClick = false;
bool clickM = false;
bool wheelClick = false;

// Rotations autour de X et Y
GLfloat angleX;
GLfloat angleY;

//========== FONCTION DE CALLBACK ==========
GLvoid affichageMap() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	// Application des rotations à l'image
	glLoadIdentity();
	glRotatef(-angleY,1.0f,0.0f,0.0f);
	glRotatef(-angleX,0.0f,1.0f,0.0f);

	float r = (float)x/(float)y;

	// Tracé du modèle 3D tiré de la variable greyLevel à partir d'une série de triangles
	// Les lignes fournies à GL_TRIANGLE_STRIP pour le tracé des triangles sont celles formée par un pixel et sont plus proche voisin de dessous
	for(int j = 0; j < x-1; j++) {
		glBegin(GL_TRIANGLE_STRIP);
			for(int i = 0; i < y; i++) {
				glColor3f((float)couleurs[(int)((float)grayLevel[i*x+j]*255./((float)maxHeight+1))][0]/255., (float)couleurs[(int)((float)grayLevel[i*x+j]*255./((float)maxHeight+1))][1]/255.0, (float)couleurs[(int)((float)grayLevel[i*x+j]*255./((float)maxHeight+1))][2]/255.);

				glVertex3f(-r+(float)j*r*2.0f/(float)x, -1.0f+(float)i*2.0f/(float)y, 0.1f*(float)grayLevel[i*x+j]/256.0f);     // Choix du premier point de la ligne

				glColor3f((float)couleurs[(int)((float)grayLevel[i*x+j+1]*255./((float)maxHeight+1))][0]/255., (float)couleurs[(int)((float)grayLevel[i*x+j+1]*255./((float)maxHeight+1))][1]/255., (float)couleurs[(int)((float)grayLevel[i*x+j+1]*255./((float)maxHeight+1))][2]/255.);

				glVertex3f(-r+(float)(j+1)*r*2.0f/(float)x, -1.0f+(float)i*2.0f/(float)y, 0.1f*(float)grayLevel[i*x+j+1]/256.0f);     // Choix du deuxième point de la ligne
			}
		glEnd();
	}

	/*// Tracé du rectangle représentant l'eau
	glBegin(GL_QUADS);
			glColor3f(0 ,1.0, 1.0);     // Correspond à une couleur cyan
			glVertex3f(-r, -1.0, 0.01);
			glVertex3f(-r, 1.0, 0.01);
			glVertex3f(r, 1.0, 0.01);
			glVertex3f(r, -1.0, 0.01);
	glEnd();*/

	glFlush();
	glutSwapBuffers();
}

//========== FONCTION DE REDIMENSIONNEMENT DE FENETRE ==========
GLvoid redimensionnerMap(int w, int h) {
	// Garde les valeurs
	windowWMap = w;
	windowHMap = h;
	// eviter une division par 0
	if(windowHMap==0)
		windowHMap = 1;

	float ratio = (float)windowWMap / (float)windowHMap;

	// Projection
	glMatrixMode(GL_PROJECTION);

	// Resetting matrix
	glLoadIdentity();

	// Viewport
	glViewport(0, 0, windowWMap, windowHMap);

	// Mise en place de la perspective
	gluPerspective(focale, ratio, _near, _far);

	// Placement de la caméra
	gluLookAt(0, 0, zoom, 0, 0, 0, 0, 1, 0);
	
	// Retourne a la pile modelview
	glMatrixMode(GL_MODELVIEW);
}

//========== FONCTIONS DE RAPPEL DE LA SOURIS ==========

GLvoid sourisMap(int bouton, int etat, int _x, int _y){
   // Test pour voir si le bouton gauche de la souris est appuyé
   if(bouton == GLUT_LEFT_BUTTON && etat == GLUT_DOWN) {
      clickM = true;
      oldX = _x;
      oldY = _y;
   }
   // Test pour voir si le bouton droit de la souris est appuyé
   else if(bouton == GLUT_RIGHT_BUTTON && etat == GLUT_DOWN) {
      rightClick = true;
      oldX = _x;
      oldY = _y;
   }
   // Test pour voir si le bouton de la souris est appuyé
   else if(bouton == GLUT_MIDDLE_BUTTON && etat == GLUT_DOWN) {
	   wheelClick = true;
	   oldX = _x;
	   oldY = _y;
   }
   
   // si on relache le bouton gauche
   if(bouton == GLUT_LEFT_BUTTON && etat == GLUT_UP) {
      clickM = false;
   }
   // si on relache le bouton droit
   if(bouton == GLUT_RIGHT_BUTTON && etat == GLUT_UP) {
      rightClick = false;
   }
   // si on relache le clic molette
   if(bouton == GLUT_MIDDLE_BUTTON && etat == GLUT_UP) {
	   wheelClick = false;
   }

}

GLvoid deplacementSourisMap(int _x, int _y) {
   // si le bouton gauche est appuye et qu'on se deplace
   // alors on doit modifier les angles de rotations du cube
   // en fonction de la derniere position de la souris 
   // et de sa position actuelle
   if(clickM) {
      angleX += (_x-oldX);
      angleY += (_y-oldY);
      // Appeler le re-affichage de la scene OpenGL
      glutPostRedisplay();
   }

   // Si le bouton droit de la souris est enfoncé, on applique un zoom
   if(rightClick) {
	   zoom += coeffZoom*(_y-oldY);

	   redimensionnerMap(windowWMap, windowHMap);

	   glutPostRedisplay();
   }
   
   // Si le clic molette est enfoncé, on modifie la hauteur maximale du modèle 3D
   if(wheelClick) {
	   scaleGrayLevel(_x-oldX);
   }

   // Mise a jour des anciennes positions de la souris en X et Y
   oldX = _x;
   oldY = _y;
}

// ============ AUTRES FONCTIONS ============

void scaleGrayLevel(int deltaHeight) {
	float rapport = (float)(maxHeight-(-deltaHeight*4))/(float)maxHeight;     // deltaHeight est multiplié par 4 pour accentuer l'effet
	maxHeight = 0;
	for(int i=0; i<x; i++) {
		for(int j=0; j<y; j++) {
			// Changement de la hauteur du modèle et mise à jour du max
			grayLevel[j*x+i] = (int)((float)grayLevel[j*x+i]*rapport);
			checkMax(grayLevel[j*x+i], maxHeight);
		}
	}

	glutPostRedisplay();
}