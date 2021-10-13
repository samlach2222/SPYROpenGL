/********************************************************/
/*                     cube.cpp                         */
/********************************************************/
/*                Affiche a l'ecran un cube en 3D       */
/********************************************************/

/* inclusion des fichiers d'en-tete freeglut */

#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systemes */
#endif
#include <cstdlib>
#include <math.h>

#include "Point.h"

char presse;
int anglex;
int angley;
int x;
int y;
int xold;
int yold;

/* Prototype des fonctions */;
void affichage();
void clavier(unsigned char touche,int x,int y);
void reshape(int x,int y);
void idle();
void mouse(int bouton,int etat,int x,int y);
void mousemotion(int x,int y);
void DessinSphere(float taille, int NP, int N);
void DessinCone(float hauteur, float rayon, int NM);
void DessinTetraedreStandard(float, float);

int main(int argc,char **argv)
{
  /* initialisation de glut et creation
     de la fenetre */
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(200,200);
  glutInitWindowSize(500,500);
  glutCreateWindow("cube");

  /* Initialisation d'OpenGL */
  glClearColor(0.0,0.0,0.0,0.0);
  glColor3f(1.0,1.0,1.0);
  glPointSize(2.0);
  glEnable(GL_DEPTH_TEST);

  /* enregistrement des fonctions de rappel */
  glutDisplayFunc(affichage);
  glutKeyboardFunc(clavier);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(mousemotion);

  /* Entree dans la boucle principale glut */
  glutMainLoop();
  return 0;
}

void affichage()
{
    int i,j;
    /* effacement de l'image avec la couleur de fond */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);

    glLoadIdentity();
    glRotatef(angley,1.0,0.0,0.0);
    glRotatef(anglex,0.0,1.0,0.0);

    //Dessin de la tête de SPYRO
    //DessinSphere(1, 5, 5);

    //Dessin des cornes de SPYRO
    //DessinCone(1, 0.25, 100);

	//Test du Tetraedre
    DessinTetraedreStandard(0.5, 0.8);

    //Repère
    //axe x en rouge
    glBegin(GL_LINES);
        glColor3f(1.0,0.0,0.0);
    	glVertex3f(0, 0,0.0);
    	glVertex3f(1, 0,0.0);
    glEnd();
    //axe des y en vert
    glBegin(GL_LINES);
    	glColor3f(0.0,1.0,0.0);
    	glVertex3f(0, 0,0.0);
    	glVertex3f(0, 1,0.0);
    glEnd();
    //axe des z en bleu
    glBegin(GL_LINES);
    	glColor3f(0.0,0.0,1.0);
    	glVertex3f(0, 0,0.0);
    	glVertex3f(0, 0,1.0);
    glEnd();

  glFlush();

  //On echange les buffers
  glutSwapBuffers();
}

void clavier(unsigned char touche,int x,int y)
{
  switch (touche)
    {
    case 'p': /* affichage du carre plein */
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glutPostRedisplay();
      break;
    case 'f': /* affichage en mode fil de fer */
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      glutPostRedisplay();
      break;
    case 's' : /* Affichage en mode sommets seuls */
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
      glutPostRedisplay();
      break;
    case 'd':
      glEnable(GL_DEPTH_TEST);
      glutPostRedisplay();
      break;
    case 'D':
      glDisable(GL_DEPTH_TEST);
      glutPostRedisplay();
      break;
    case 'q' : /*la touche 'q' permet de quitter le programme */
      exit(0);
    }
}

void reshape(int x,int y)
{
  if (x<y)
    glViewport(0,(y-x)/2,x,x);
  else
    glViewport((x-y)/2,0,y,y);
}

void mouse(int button, int state,int x,int y)
{
  /* si on appuie sur le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    presse = 1; /* le booleen presse passe a 1 (vrai) */
    xold = x; /* on sauvegarde la position de la souris */
    yold=y;
  }
  /* si on relache le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    presse=0; /* le booleen presse passe a 0 (faux) */
}

void mousemotion(int x,int y)
  {
    if (presse) /* si le bouton gauche est presse */
    {
      /* on modifie les angles de rotation de l'objet
	 en fonction de la position actuelle de la souris et de la derniere
	 position sauvegardee */
      anglex=anglex+(x-xold);
      angley=angley+(y-yold);
      glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
    }

    xold=x; /* sauvegarde des valeurs courante de le position de la souris */
    yold=y;
  }


void DessinSphere(float taille, int NP, int NM)
{
    float x[NM*NP];
    float y[NM*NP];
    float z[NM*NP];

    float fSphere[NM][NP][4];

    for(int j = 0; j < NP; j++)
    {
        for(int i = 0; i < NM; i++)
        {
            x[i+j*NM] = taille*cos(2*i*M_PI/NM)*cos(-M_PI/2+j*M_PI/(NP-1));
            y[i+j*NM] = taille*sin(2*i*M_PI/NM)*cos(-M_PI/2+j*M_PI/(NP-1));
            z[i+j*NM] = taille*sin(-M_PI/2+j*M_PI/(NP-1));
        }
    }
    for(int j = 0; j < NP -1; j++)
    {

        for(int i = 0; i < NM; i++)
        {
            fSphere[j][i][0] = ((i+1)%NM) + j*NM;
            fSphere[j][i][1] = ((i+1)%NM) + (j+1)*NM;
            fSphere[j][i][2] = i+(j+1)*NM;
            fSphere[j][i][3] = i+j*NM;

            glBegin(GL_POLYGON);

            //glTexCoord2f(0,0); //texture
            glColor3f(0.2, 0.4, 0.6);
            glVertex3f(x[((i+1)%NM) + j*NM], y[((i+1)%NM) + j*NM], z[((i+1)%NM) + j*NM]);

            //glTexCoord2f(0,1); //texture
            glColor3f(0.4, 0.4, 0.6);
            glVertex3f(x[((i+1)%NM) + (j+1)*NM], y[((i+1)%NM) + (j+1)*NM], z[((i+1)%NM) + (j+1)*NM]);

            //glTexCoord2f(1,1); //texture
            glColor3f(0.2, 0.6, 0.6);
            glVertex3f(x[i+(j+1)*NM], y[i+(j+1)*NM], z[i+(j+1)*NM]);

            //glTexCoord2f(1,0); //texture
            glColor3f(0.2, 0.4, 0.2);
            glVertex3f(x[i+j*NM], y[i+j*NM], z[i+j*NM]);

            glEnd();
        }
    }
}
void DessinCone(float hauteur, float rayon, int NM)
{
    float x[NM]; // NM --> taille du nombre de subdivison de la base
    float z[NM];

    float fCone[NM][3]; // NM faces sur la même circonférence de 3 points

    // dessin de la base
    for(int i = 0; i < NM; i++)
    {
        x[i] = rayon*cos(2*i*M_PI/NM);
        z[i] = rayon*sin(2*i*M_PI/NM);
    }

    glBegin(GL_POLYGON);
    for(int i = 0; i < NM; i++)
    {
        glColor3f(0.2*i, 0.2*i, 0.2*i);
        glVertex3f(x[i], 0, z[i]);  // y toujours égal à 0 car le pentagone est en 2D
    }
    glEnd();

    // dessin du volume
    for(int i = 0; i < NM; i++)
    {
        glBegin(GL_POLYGON);

        glColor3f(0.4, 0.4, 0.6);
        glVertex3f(x[i], 0, z[i]); // Premier point du triangle

        glColor3f(0.6, 0.4, 0.6);
        glVertex3f(x[(i+1)%NM], 0, z[(i+1)%NM]); // Deuxième point du triangle

        glColor3f(0.4, 0.4, 0.2);
        glVertex3f(0, hauteur, 0);  // Sommet du triangle

        glEnd();
    }
}

void DessinTetraedreStandard(float longeur, float hauteur){

    //base bas
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.1, 0.1);
    glVertex3f(longeur, 0, 0);
    glVertex3f(0, 0, longeur);
    glVertex3f(0, 0, 0);
    glEnd();

    //base haut
    glBegin(GL_POLYGON);
    glColor3f(0.1, 0.8, 0.1);
    glVertex3f(0, hauteur, longeur);
    glVertex3f(0, hauteur, 0);
    glVertex3f(longeur, hauteur, 0);
    glEnd();

    //côté hypothénuse
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.1, 0.8);
    glVertex3f(0, 0, longeur);
    glVertex3f(0, hauteur, longeur);
    glVertex3f(longeur, hauteur, 0);
    glVertex3f(longeur, 0, 0);
    glEnd();

    //côté axe x
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.8, 0.1);
    glVertex3f(longeur, 0, 0);
    glVertex3f(longeur, hauteur, 0);
    glVertex3f(0, hauteur, 0);
    glVertex3f(0, 0, 0);
    glEnd();

    //côté axe z
    glBegin(GL_POLYGON);
    glColor3f(0.1, 0.1, 0.8);
    glVertex3f(0, 0, longeur);
    glVertex3f(0, hauteur, longeur);
    glVertex3f(0, hauteur, 0);
    glVertex3f(0, 0, 0);
    glEnd();
}
