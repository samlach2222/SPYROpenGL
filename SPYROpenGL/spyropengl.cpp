/**
 * @file spyropengl.cpp
 * @brief Gère le démarrage de l'application
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 2.4
 * @date 16/06/2024
 */

/********************************************************/
/*                     spyropengl.cpp                   */
/********************************************************/
/*       Affiche une version réduite de Spyro en 3D     */
/********************************************************/

/* inclusion des fichiers d'en-tête freeglut */
#ifdef __APPLE__
/* Pour Mac OS X */
#include <GLUT/glut.h>
#include <GLUT/freeglut_ext.h>
#else
/* Pour les autres systèmes */
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif

#include "Montage.h"
#include "IntermittentDuSpectacle.h"
#include "Textures.h"
using namespace std;
#include <vector>

#include <math.h>
#include <thread>

/* Déclaration des variables extern des textures */
unsigned char textureOeil[Textures::widthOeil*Textures::heightOeil*3];
unsigned char textureSkybox[Textures::widthSkybox*Textures::heightSkybox*3];
unsigned char textureCriniere[Textures::widthCriniere*Textures::heightCriniere*3];

const int tailleSkybox = 14;
const int nombreFacesSkybox = 30;
const bool showSkybox = true;  //DEBUG : Désactiver permet une plus grande liberté de mouvement
char presse;
GLfloat anglex;
GLfloat angley;
int x;
int y;
int xold;
int yold;
int angleRotation = 0; // Angle de rotation de la lumière 1

// Variables globales pour les animations /!\ A DEPLACER QUAND POSSIBLE DANS INTERMITTENTDUSPECTACLE
float angleRotationAiles = 0.0;
bool sensMontantAiles = true;

float angleRotationBouche = 0.0;
bool sensMontantBouche = false;  //false = vers le haut, true = vers le bas
bool SPACE_PRESSED = false;

// Threads pour jouer de la musique ou des sons
thread bgMusic;
thread voice;

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
float RotationneAileSpyro(float);
float RotationneBoucheSpyro(float);

int main(int argc,char **argv)
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    champDeVision = 3;  //Valeur de dézoom initiale
    translationX = 0;  //Valeur par défaut de la translation sur l'axe X pour tout
    translationY = 0;  //Valeur par défaut de la translation sur l'axe Y pour tout
    translationZ = 0;  //Valeur par défaut de la translation sur l'axe Z pour tout

    /* initialisation de glut et création de la fenêtre */
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    const int initWindowWidth = 1600;
    const int initWindowHeight = 900;
    glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH)/2 - initWindowWidth/2, glutGet(GLUT_SCREEN_HEIGHT)/2 - initWindowHeight/2);  //La fonction gère automatiquement les valeurs négatives en utilisant 0
    glutInitWindowSize(initWindowWidth,initWindowHeight);
    glutCreateWindow("SPYROpenGL");
    // Par défaut l'application quitte immédiatement à la fermeture de la fenêtre, avec cette commande elle sort de glutMainLoop
    // Cela permet de quitter proprement sans crash
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    /* Initialisation d'OpenGL */
    glClearColor(0.0,0.0,0.0,0.0);
    glColor4f(1.0,1.0,1.0,1.0);
    glPointSize(2.0);
    glEnable(GL_DEPTH_TEST);

    /* Paramétrage du placage de textures */
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);  //Filtre
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);  //Filtre
    glAlphaFunc(GL_GREATER, 0.5);  //Rend transparent les pixels avec plus de 0,5 d'alpha
    glEnable(GL_ALPHA_TEST);  //Active la transparence

    /* Chargement des textures */
    #ifdef _WIN32
    char* t1 = _strdup("Ressources/Texture/skybox.jpg");
    char* t2 = _strdup("Ressources/Texture/oeil.jpg");
    char* t3 = _strdup("Ressources/Texture/criniere.jpg");
    #elif __GNUC__
    char* t1 = "Ressources/Texture/skybox.jpg";
    char* t2 = "Ressources/Texture/oeil.jpg";
    char* t3 = "Ressources/Texture/criniere.jpg";
    #endif
    Textures::LoadJpegImage(t1, textureSkybox);
    Textures::LoadJpegImage(t2, textureOeil);
    Textures::LoadJpegImage(t3, textureCriniere);

    /* enregistrement des fonctions de rappel */
    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemotion);
    glutSpecialFunc(specialInput);  //similaire à glutKeyboardFunc mais pour les touches non-ascii

    /***************************************************************/
    /***** L'intermittent du spectacle joue la musique de fond *****/
    /***************************************************************/
    bgMusic = thread(IntermittentDuSpectacle::JoueDeLaMusique);

    /* Entrée dans la boucle principale glut */
    glutMainLoop();
    // Si Spyro est en train de crier sur la voie publique à la fermeture de SPYROpenGL un crash se produit, idem avec la musique
    // Une alternative plus propre mais verbeuse serait d'englober les deux threads dans des classes avec leur propre destructeur
    IntermittentDuSpectacle::ArreteCrieSurLaVoiePublique(voice);
    IntermittentDuSpectacle::ArreteJoueDeLaMusique(bgMusic);
    return 0;
}

void affichage()
{
    /* effacement de l'image avec la couleur de fond */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);


    float Wsize = (float) glutGet(GLUT_WINDOW_WIDTH) / (float) glutGet(GLUT_WINDOW_HEIGHT);
    glLoadIdentity();
    glOrtho(-champDeVision*Wsize, champDeVision*Wsize, -champDeVision, champDeVision, -3-(997*!showSkybox), 1000);  //Gère le zoom/dézoom
    glRotatef(angley,1.0,0.0,0.0);
    glRotatef(anglex,0.0,1.0,0.0);

    //srand(713705);  //Seed utilisé pour les couleurs aléatoires

    /********************************************/
    /*****     Utilisation des lumières     *****/
    /********************************************/
    IntermittentDuSpectacle::PlaceLaLumiereStatique();
    IntermittentDuSpectacle::PlaceLaLumiereQuiBouge(angleRotation);
    angleRotation++;


    /********************************************/
    /*****        Dessin de la Skybox       *****/
    /********************************************/
    glColor4f(1,1,1,1);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,Textures::widthSkybox,Textures::heightSkybox,0,GL_RGB,GL_UNSIGNED_BYTE,textureSkybox);
    glEnable(GL_TEXTURE_2D);

    if (showSkybox)
    {
        vector<float> x(nombreFacesSkybox*nombreFacesSkybox);
        vector<float> y(nombreFacesSkybox*nombreFacesSkybox);
        vector<float> z(nombreFacesSkybox*nombreFacesSkybox);

        vector<vector<vector<double>>> fSphere(nombreFacesSkybox, vector<vector<double>>(nombreFacesSkybox, vector<double>(4)));

        for(int j = 0; j < nombreFacesSkybox; j++)
        {
            for(int i = 0; i < nombreFacesSkybox; i++)
            {
                // convert double to float
                x[i+j*nombreFacesSkybox] = (float) (tailleSkybox*cos(2*i*M_PI/nombreFacesSkybox)*cos(-M_PI/2+j*M_PI/(nombreFacesSkybox-1)));
                y[i+j*nombreFacesSkybox] = (float) (tailleSkybox*sin(2*i*M_PI/nombreFacesSkybox)*cos(-M_PI/2+j*M_PI/(nombreFacesSkybox-1)));
                z[i+j*nombreFacesSkybox] = (float) (tailleSkybox*sin(-M_PI/2+j*M_PI/(nombreFacesSkybox-1)));
            }
        }
        for(int j = 0; j < nombreFacesSkybox - 1; j++)
        {
            for(int i = 0; i < nombreFacesSkybox; i++)
            {
                fSphere[j][i][0] = (float) (((i+1)%nombreFacesSkybox) + j*nombreFacesSkybox);
                fSphere[j][i][1] = (float) (((i+1)%nombreFacesSkybox) + (j+1)*nombreFacesSkybox);
                fSphere[j][i][2] = (float) (i+(j+1)*nombreFacesSkybox);
                fSphere[j][i][3] = (float) (i+j*nombreFacesSkybox);

                glPushMatrix();
                glRotatef(90,-1,0,0);
                glRotatef(90,0,0,-1);
                glBegin(GL_POLYGON);
                //glTexCoord2f(x, y); avec x et y de 0 à 1 et le point d'origine dans le coin haut gauche
                glTexCoord2f(1 - (float) (i+1)/nombreFacesSkybox, 1 - (float) j/nombreFacesSkybox);
                glVertex3f(x[((i+1)%nombreFacesSkybox) + j*nombreFacesSkybox], y[((i+1)%nombreFacesSkybox) + j*nombreFacesSkybox], z[((i+1)%nombreFacesSkybox) + j*nombreFacesSkybox]);

                glTexCoord2f(1 - (float) (i+1)/nombreFacesSkybox, 1 - (float) (j+1)/nombreFacesSkybox);
                glVertex3f(x[((i+1)%nombreFacesSkybox) + (j+1)*nombreFacesSkybox], y[((i+1)%nombreFacesSkybox) + (j+1)*nombreFacesSkybox], z[((i+1)%nombreFacesSkybox) + (j+1)*nombreFacesSkybox]);

                glTexCoord2f(1 - (float) i/nombreFacesSkybox, 1 - (float) (j+1)/nombreFacesSkybox);
                glVertex3f(x[i+(j+1)*nombreFacesSkybox], y[i+(j+1)*nombreFacesSkybox], z[i+(j+1)*nombreFacesSkybox]);

                glTexCoord2f(1 - (float) i/nombreFacesSkybox, 1 - (float) j/nombreFacesSkybox);
                glVertex3f(x[i+j*nombreFacesSkybox], y[i+j*nombreFacesSkybox], z[i+j*nombreFacesSkybox]);
                glEnd();
                glPopMatrix();
            }
        }
    }

    glDisable(GL_TEXTURE_2D);

    /********************************************/
    /*****   Check Mouvement bouche Spyro   *****/
    /********************************************/
    if(SPACE_PRESSED){
        if (!sensMontantBouche){
            angleRotationBouche++;
            if (angleRotationBouche > 14)  //Angle maximum
            {
                sensMontantBouche = true;
            }
        }
        else{
            angleRotationBouche--;
            if (angleRotationBouche < 6)  //Angle minimum
            {
                sensMontantBouche = false;
            }
        }
    }
    else  //Fermeture de la bouche
    {
        if (angleRotationBouche > 0)
        {
            angleRotationBouche--;
        }
        if (sensMontantBouche)
        {
            sensMontantBouche = false;
        }
    }


    /********************************************/
    /***** Affichage du personnage de SPYRO *****/
    /********************************************/
    glTranslatef(translationX, translationY, translationZ);  //Décalage de Spyro

    angleRotationAiles = RotationneAileSpyro(angleRotationAiles);
    Montage::MontageSpyro(angleRotationAiles, angleRotationBouche);


    /*//Repère
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
    glEnd();*/

    glFlush();

    //On échange les buffers
    glutSwapBuffers();

    // Pour actualiser
    glutPostRedisplay();
}

void clavier(unsigned char touche,int x,int y)
{
    switch (touche)
    {
        case 'p': /* Affichage du carré plein */
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            glutPostRedisplay();
            break;
        case 'f': /* Affichage en mode fil de fer */
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
        case 'z':
            //Zoom
            champDeVision -= 0.05f;
            if (champDeVision < 0.05){
                //Zoom maximum
                champDeVision = 0.05f;
            }
            glutPostRedisplay();
            break;
        case 'Z':
            //Dézoom
            champDeVision += 0.05f;
            if (champDeVision > 6){
                //Dézoom maximum
                champDeVision = 6;
            }
            glutPostRedisplay();
            break;
        case 'i':
            translationY += 0.05f;
            if (showSkybox && translationY > 0.2){
                //Translation maximum
                translationY = 0.2f;
            }
            glutPostRedisplay();
            break;
        case 'k':
            translationY -= 0.05f;
            if (showSkybox && translationY < -0.2){
                //Translation maximum
                translationY = -0.2f;
            }
            glutPostRedisplay();
            break;
        case 'j':
            translationX -= 0.05f;
            if (showSkybox && translationX < -0.2){
                //Translation maximum
                translationX = -0.2f;
            }
            glutPostRedisplay();
            break;
        case 'J':
            translationZ -= 0.05f;
            if (showSkybox && translationZ < -0.2){
                //Translation maximum
                translationZ = -0.2f;
            }
            glutPostRedisplay();
            break;
        case 'l':
            translationX += 0.05f;
            if (showSkybox && translationX > 0.2){
                //Translation maximum
                translationX = 0.2f;
            }
            glutPostRedisplay();
            break;
        case 'L':
            translationZ += 0.05f;
            if (showSkybox && translationZ > 0.2){
                //Translation maximum
                translationZ = 0.2f;
            }
            glutPostRedisplay();
            break;
        case ' ':
        {
            if (!SPACE_PRESSED)
            {
                SPACE_PRESSED = true;
                /******************************************************************************************/
                /***** L'intermittent du spectacle crie sur la place publique : Bonjour je suis Spyro *****/
                /******************************************************************************************/
                IntermittentDuSpectacle::ArreteCrieSurLaVoiePublique(voice);
                bool* PTR_SPACE_PRESSED = &SPACE_PRESSED;
                voice = thread(IntermittentDuSpectacle::CrieSurLaVoiePublique, PTR_SPACE_PRESSED);
            }
        }
            break;
        case 'q' : /* La touche 'q' permet de quitter le programme */
            glutLeaveMainLoop();
            break;
    }
}

void specialInput(int key, int x, int y)
{
    /* Pour la souris, des rotations de 1 minimum et uniquement d'entiers sont appliqués.
       Autant faire la même chose avec les touches fléchées */
    switch(key)
    {
        case GLUT_KEY_UP:
            angley -= 1;
            break;
        case GLUT_KEY_DOWN:
            angley += 1;
            break;
        case GLUT_KEY_LEFT:
            anglex -= 1;
            break;
        case GLUT_KEY_RIGHT:
            anglex += 1;
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
        presse = 1; /* le booléen presse passe à 1 (vrai) */
        xold = x; /* on sauvegarde la position de la souris */
        yold=y;
    }
    /* si on relâche le bouton gauche */
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        presse=0; /* le booléen presse passe à 0 (faux) */
}

void mousemotion(int x,int y)
{
    if (presse) /* si le bouton gauche est presse */
    {
        /* on modifie les angles de rotation de l'objet
        en fonction de la position actuelle de la souris et de la dernière
        position sauvegardée */
        anglex=anglex+(x-xold);
        angley=angley+(y-yold);
        glutPostRedisplay(); /* on demande un rafraîchissement de l'affichage */
    }

    xold=x; /* sauvegarde des valeurs courantes de la position de la souris */
    yold=y;
}

float RotationneAileSpyro(float angle)
{
    float res = angle;
    if(res == 50.0)
    {
        sensMontantAiles = false;
    }
    else if(res == -50.0)
    {
        sensMontantAiles = true;
    }

    if(sensMontantAiles == true)
    {
        res += 1.0;
    }
    if(sensMontantAiles == false)
    {
        res -= 1.0;
    }
    return res;
}
