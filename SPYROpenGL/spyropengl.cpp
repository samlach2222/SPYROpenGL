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
#include <time.h>

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

// Prototype des fonctions de dessin
void DessinSphere(float taille, int NP, int N);
void DessinCone(float hauteur, float rayon, int NM);
void DessinCriniere(float rayonSphere);
void DessinPrisme(float longueurX, float longueurZ, float hauteur, float coeffX = 1, float coeffZ = 1, float decalageSX = 0, float decalageSZ = 0);
void DessinCube(float taille);
void DessinJambes(float longueurX, float longueurZ, float hauteur, bool sens);
void DessinTetraedre(float longueurX, float longueurZ, float hauteur, float decalageBX = 0, float decalageBZ = 0, float decalageSX = 0, float decalageSZ = 0);

// Prototype des fonctions de création
void CreationJambesPlusPieds(float taille, float hauteurJambes);
void CreationPieds(float taille);
void CreationJambes(float taille, float hauteur, bool sens);
void CreationComposantsTete(float taille, float hauteurCorne, float largeurCorne);
void CreationQueue(float taille = 1);

// Prototype des autres fonctions
void RandomColor3f();

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

    //Dessin de la tête
	//CreationComposantsTete(0.5, 1, 0.15);

    //Dessin de la queue
    //CreationQueue(1);

	//Dessin des pieds
	//float taille = 0.5;
	//float hauteurJambes = 3;
	//CreationJambesPlusPieds(taille, hauteurJambes);

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


  //changement de la caméra
  /*glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-3, 3, -3, 3, -3, 3);
  glMatrixMode(GL_MODELVIEW);*/
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

    float fSphere[NP][NM][4];

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

            glPushMatrix();
            glRotatef(90,-1,0,0);
            glRotatef(90,0,0,-1);
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
            glPopMatrix();
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

void DessinCriniere(float rayonSphere)
{
    /*
        ma base est au centre de la sphère
        Voici son orientation :

            _____
            \    |
             \   |
              \  |
               \ |
                \|

        L'arête gauche fait 2r avec r rayon de la sphère.
        L'arête du dessus fait 2r avec r rayon de la sphère.re.
        Ainsi l'hypothénuse sqrt(4r²) --> Pythagore.

        Les angles sont respectivement 90°, 45° et 45°.
        L'hypothénuse passe en son milieu sur le centre de la sphère.
        Elle est en 2D située sur l'axe Z, Y. En effet X est nul.

        Je construit mon triangle avec le point du bas en 0,0,0 afin d'avoir des coordonnées faciles.
    */
    float x;
    float y;
    float z;

    glPushMatrix();
    /*
        J'effectue une translation afin de positionner mon triangle :
        Je recule sur le derrière de la tête le triangle d'une longueur du rayon de la sphère.
        Je descend sur le dessous de la tête le triangle des 3/4 du rayon de la sphère afin de garder une partie débordante de la crinière
        _____
        \    |
         \   |  ⋀
          \  |  | =  -3/4*rayonSphere   <--- = -rayonSphere
           \ |  |
            \|
    */
    glTranslatef(0,-rayonSphere*3/4, -rayonSphere);
    glBegin(GL_POLYGON);

    glColor3f(0.2, 0.4, 0.6);
    glVertex3f(0, 0, 0); // Point du bas (à l'origine)

    glColor3f(0.6, 0.4, 0.6);
    glVertex3f(0, 2*rayonSphere, 0); // Point haut droit

    glColor3f(0.2, 0.2, 0.6);
    glVertex3f(0, 2*rayonSphere, 2*rayonSphere); // Point haut gauche

    glEnd();
    glPopMatrix();
}

void DessinPrisme(float longueurX, float longueurZ, float hauteur, float coeffX, float coeffZ, float decalageSX, float decalageSZ){

    float coordPoints[6][3] = {
        {0, 0, 0},
        {longueurX, 0, 0},
        {0, 0, longueurZ},
        {decalageSX, hauteur, decalageSZ},
        {longueurX*coeffX, hauteur, 0},
        {0, hauteur, longueurZ*coeffZ}
    };

    //base bas
    glBegin(GL_POLYGON);
    RandomColor3f();
    glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
    glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
    glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();

    //base haut
    glBegin(GL_POLYGON);
    RandomColor3f();
    glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
    glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
    glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
    glEnd();

    //côté hypothénuse
    glBegin(GL_POLYGON);
    RandomColor3f();
    glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
    glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
    glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
    glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
    glEnd();

    //côté axe x
    glBegin(GL_POLYGON);
    RandomColor3f();
    glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
    glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
    glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
    glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();

    //côté axe z
    glBegin(GL_POLYGON);
    RandomColor3f();
    glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
    glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
    glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
    glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();
}

void DessinJambes(float longueurX, float longueurZ, float hauteur, bool sens){

    float h = sqrt(longueurX*longueurX + longueurZ*longueurZ); // hypothénuse du triangle du dessus
    if(sens)
    {
        float coordPoints[6][3] = {
            {0, 0, 0},
            {longueurX, 0, 0},
            {0, 0, longueurZ},
            {0, hauteur+((h/2)/(tan(M_PI/4))), 0}, // On translate les points de leurs distance avec l'angle de tanslation avec une relation Tan = Opp / Adj
            {longueurX, hauteur+(h/(tan(M_PI/4))), 0}, // On translate les points de leurs distance avec l'angle de tanslation avec une relation Tan = Opp / Adj
            {0, hauteur, longueurZ}
        };

        //base bas
        glBegin(GL_POLYGON);
        glColor3f(0.8, 0.1, 0.1);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
        glEnd();

        //base haut
        glBegin(GL_POLYGON);
        glColor3f(0.1, 0.8, 0.1);
        glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
        glEnd();

        //côté hypothénuse
        glBegin(GL_POLYGON);
        glColor3f(0.8, 0.1, 0.8);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
        glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glEnd();

        //côté axe x
        glBegin(GL_POLYGON);
        glColor3f(0.8, 0.8, 0.1);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
        glEnd();

        //côté axe z
        glBegin(GL_POLYGON);
        glColor3f(0.1, 0.1, 0.8);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
        glEnd();
    }
    else
    {
        float coordPoints[6][3] = {
            {0, 0, 0},
            {longueurX, 0, 0},
            {0, 0, longueurZ},
            {0, hauteur+((h/2)/(tan(M_PI/4))), 0}, // On translate les points de leurs distance avec l'angle de tanslation avec une relation Tan = Opp / Adj
            {longueurX, hauteur, 0},
            {0, hauteur+(h/(tan(M_PI/4))), longueurZ} // On translate les points de leurs distance avec l'angle de tanslation avec une relation Tan = Opp / Adj
        };

        //base bas
        glBegin(GL_POLYGON);
        glColor3f(0.8, 0.1, 0.1);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
        glEnd();

        //base haut
        glBegin(GL_POLYGON);
        glColor3f(0.1, 0.8, 0.1);
        glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
        glEnd();

        //côté hypothénuse
        glBegin(GL_POLYGON);
        glColor3f(0.8, 0.1, 0.8);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
        glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glEnd();

        //côté axe x
        glBegin(GL_POLYGON);
        glColor3f(0.8, 0.8, 0.1);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
        glEnd();

        //côté axe z
        glBegin(GL_POLYGON);
        glColor3f(0.1, 0.1, 0.8);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
        glEnd();
    }
}

void DessinCube(float taille){
    // base bas
    glBegin(GL_POLYGON);
    glColor3f(0.4, 0.6, 0.2);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, taille);
    glVertex3f(taille, 0, taille);
    glVertex3f(taille, 0, 0);
    glEnd();

    // base haut
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(0, taille, 0);
    glVertex3f(0, taille, taille);
    glVertex3f(taille, taille, taille);
    glVertex3f(taille, taille, 0);
    glEnd();

    // face devant
    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.6, 0.2);
    glVertex3f(0, 0, taille);
    glVertex3f(taille, 0, taille);
    glVertex3f(taille, taille, taille);
    glVertex3f(0, taille, taille);
    glEnd();

    // face droite
    glBegin(GL_POLYGON);
    glColor3f(0.4, 0.4, 0.2);
    glVertex3f(taille, 0, taille);
    glVertex3f(taille, 0, 0);
    glVertex3f(taille, taille, 0);
    glVertex3f(taille, taille, taille);
    glEnd();

    // face derrière
    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(taille, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, taille, 0);
    glVertex3f(taille, taille, 0);
    glEnd();

    // face gauche
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.6, 0.2);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, taille);
    glVertex3f(0, taille, taille);
    glVertex3f(0, taille, 0);
    glEnd();
}

void DessinTetraedre(float longueurX, float longueurZ, float hauteur, float decalageBX, float decalageBZ, float decalageSX, float decalageSZ){

    float coordPoints[4][3] = {
        {decalageBX, 0, decalageBZ},
        {longueurX, 0, 0},
        {0, 0, longueurZ},
        {longueurX/2 + decalageSX, hauteur, longueurZ/2 + decalageSZ},
    };

    //base bas
    glBegin(GL_POLYGON);
    RandomColor3f();
    glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
    glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
    glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();

    //côté hypothénuse
    glBegin(GL_POLYGON);
    RandomColor3f();
    glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
    glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
    glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
    glEnd();

    //côté axe x
    glBegin(GL_POLYGON);
    RandomColor3f();
    glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
    glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
    glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();

    //côté axe z
    glBegin(GL_POLYGON);
    RandomColor3f();
    glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
    glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
    glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();
}

void CreationJambes(float taille, float hauteur, bool sens)
{
    glPushMatrix();
        glRotatef(45,0,-1,0);
        glTranslatef(-sqrt((taille*taille)/2),taille,0);
        DessinJambes(sqrt((taille*taille)/2), sqrt((taille*taille)/2), hauteur, sens);
    glPopMatrix();
}

void CreationPieds(float taille)
{
    glPushMatrix();
        glRotatef(90,0,0,1);
        glTranslatef(0,0,taille);
        DessinPrisme(taille, 1, taille);
    glPopMatrix();

	glPushMatrix();
        glTranslatef(-taille,0,0);
        DessinCube(taille);
	glPopMatrix();

	glPushMatrix();
        glRotatef(45,0,-1,0);
        glTranslatef(-sqrt((taille*taille)/2),0,0);
        DessinPrisme(sqrt((taille*taille)/2), sqrt((taille*taille)/2), taille);
    glPopMatrix();
}

void CreationJambesPlusPieds(float taille, float hauteurJambes)
{
    // ******** DESSIN DES PIEDS + JAMBES ********
    CreationPieds(taille); // PIED 1
    CreationJambes(taille, hauteurJambes, false); // JAMBE 1
    glTranslatef(2*taille,0,0); // TRANSLATION 2EME PARTIE
    CreationPieds(taille); // PIED 2
    CreationJambes(taille, hauteurJambes, true); // JAMBE 2
    glTranslatef(-2*taille,0,0); // RETOUR ORIGINE
    // ******** FIN DESSIN PIED + JAMBES ********
}

void CreationComposantsTete(float taille, float hauteurCorne, float largeurCorne)
{
    //Dessin de la tête de SPYRO
    DessinSphere(taille, 5, 5);

    //Dessin de la crinière de SPYRO
    DessinCriniere(taille);

    //Dessin des cornes de SPYRO
    glPushMatrix();
        glRotatef(15,1,0,-1);
        glTranslatef(taille/10,0,taille/7);
        DessinCone(hauteurCorne, largeurCorne, 100);
    glPopMatrix();

    glPushMatrix();
        glRotatef(15,1,0,1);
        glTranslatef(-taille/10,0,taille/7);
        DessinCone(hauteurCorne, largeurCorne, 100);
    glPopMatrix();
}

void CreationQueue(float taille)
{
    //Dessin de la première partie de la queue de SPYRO
    srand(32);
    const float longueurPremierePartieQueue = 2.0;
    DessinPrisme(0.8*taille,0.8*taille,longueurPremierePartieQueue*taille,0.25,0.25);

    //Dessin de la deuxième partie de la queue
    srand(64);
    const float longueurDeuxiemePartieQueue = 0.2;
    glPushMatrix();
    glTranslatef(0,longueurPremierePartieQueue*taille,0);
    DessinPrisme(0.2*taille,0.2*taille,longueurDeuxiemePartieQueue*taille,2,2,-0.1*taille,-0.1*taille);
    glPopMatrix();

    //Dessin de la troisième partie de la queue
    srand(128);
    const float longueurTroisiemePartieQueue = 0.4;
    glPushMatrix();
    glTranslatef(0, longueurPremierePartieQueue*taille + longueurDeuxiemePartieQueue*taille, 0);
    DessinTetraedre(0.4*taille, 0.4*taille, longueurTroisiemePartieQueue*taille, -0.1*taille, -0.1*taille);
    glPopMatrix();
}

void RandomColor3f(){
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);  //Donne une valeur entre 0.0 et 1.0 inclus
    float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    glColor3f(r,g,b);
}
