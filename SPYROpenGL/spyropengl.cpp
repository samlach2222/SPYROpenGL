/**
 * @file spyropengl.cpp
 * @brief Gère le démarrage de l'application
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 1.0
 * @date 16/10/2021
 */

/********************************************************/
/*                     spyropengl.cpp                   */
/********************************************************/
/*       Affiche une version rédute de Spyro en 3D     */
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
#include <thread>

#include "Montage.h"
#include "IntermittentDuSpectacle.h"

char presse;
int anglex;
int angley;
int x;
int y;
int xold;
int yold;

/**
 * @brief Valeur du champ de vision
 */
float champDeVision;  // /!\ Correspond à une valeur de dézoom
/**
 * @brief Valeur de la translation sur l'axe X pour tout
 */
float translationX;
/**
 * @brief Valeur de la translation sur l'axe Y pour tout
 */
float translationY;
/**
 * @brief Valeur de la translation sur l'axe Z pour tout
 */
float translationZ;

/* Prototype des fonctions */;
void affichage();
void clavier(unsigned char touche,int x,int y);
void reshape(int x,int y);
void idle();
void mouse(int bouton,int etat,int x,int y);
void mousemotion(int x,int y);
void specialInput(int key, int x, int y);  //similaire au clavier mais avec des touches non-ascii

int main(int argc,char **argv)
{
    champDeVision = 3;  //Valeur de dézoom initiale
    translationX = 0;  //Valeur par défaut de la translation sur l'axe X pour tout
    translationY = 0;  //Valeur par défaut de la translation sur l'axe Y pour tout
    translationZ = 0;  //Valeur par défaut de la translation sur l'axe Z pour tout

    /* initialisation de glut et creation
     de la fenetre */
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(1600,900);
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
    glutSpecialFunc(specialInput);  //similaire à glutKeyboardFunc mais pour les touches non-ascii

    /* Entree dans la boucle principale glut */

    /***************************************************************/
    /***** L'intermittent du spectacle joue la musique de fond *****/
    /***************************************************************/
    std::thread t(IntermittentDuSpectacle::play_music);

    glutMainLoop();
    return 0;
}

void affichage()
{
    int i,j;
    /* effacement de l'image avec la couleur de fond */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);


    float Wsize = (float) glutGet(GLUT_WINDOW_WIDTH)/ (float) glutGet(GLUT_WINDOW_HEIGHT);
    glLoadIdentity();
    glOrtho(-champDeVision*Wsize, champDeVision*Wsize, -champDeVision, champDeVision, -1000, 1000);  //Gère le zoom/dézoom
    glRotatef(angley,1.0,0.0,0.0);
    glRotatef(anglex,0.0,1.0,0.0);
    glTranslatef(translationX, translationY, translationZ);  //Décalage sur Y de tout

    srand(713705);


    /*******************************************/
    /***** Dessin des pieds + corps + queue*****/
    /*******************************************/
    Montage::MontageSpyro();

    /*glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glBegin( GL_QUADS ); // apriori pour mettre un BG il faut texturer cette chose, mais spyro passe à travers

    glTexCoord2f(0,0);
    glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1,0);
    glVertex2f(1.0f, -1.0f);
    glTexCoord2f(1,1);
    glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0,1);
    glVertex2f(-1.0f, 1.0f);

    glEnd();

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);*/

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
        case '+':
            //Zoom
            champDeVision -= 0.05;
            if (champDeVision < 0.05){
                //Zoom maximum
                champDeVision = 0.05;
            }
            glutPostRedisplay();
            break;
        case '-':
            //Dézoom
            champDeVision += 0.05;
            if (champDeVision > 6){
                //Dézoom maximum
                champDeVision = 6;
            }
            glutPostRedisplay();
            break;
        case 'q' : /*la touche 'q' permet de quitter le programme */
            exit(0);
    }
}

void specialInput(int key, int x, int y){

    //Si touche ctrl ou shift ou les deux maintenues
    bool ctrlOrShift = false;
    switch(glutGetModifiers())
    {
        case GLUT_ACTIVE_CTRL:
        case GLUT_ACTIVE_SHIFT:
        case GLUT_ACTIVE_CTRL+GLUT_ACTIVE_SHIFT:
            ctrlOrShift = true;
            break;
    }

    //Si ctrlOrShift est vrai les flèches gauche/droite déplace sur l'axe Z, sinon sur l'axe X
    switch(key)
    {
        case GLUT_KEY_UP:
        translationY += 0.05;
            break;
        case GLUT_KEY_DOWN:
        translationY -= 0.05;
            break;
        case GLUT_KEY_LEFT:
        if (ctrlOrShift){
            translationZ -= 0.05;
        } else {
            translationX -= 0.05;
        }
            break;
        case GLUT_KEY_RIGHT:
        if (ctrlOrShift){
            translationZ += 0.05;
        } else {
            translationX += 0.05;
        }
            break;
    }
    glutPostRedisplay();
}

void reshape(int x,int y)
{
    glViewport(0,0,x,y);
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
