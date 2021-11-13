/**
 * @file spyropengl.cpp
 * @brief Gère le démarrage de l'application
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 2.1
 * @date 13/11/2021
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
#include <jpeglib.h>
#include <jerror.h>

#include "Montage.h"
#include "IntermittentDuSpectacle.h"

const int widthSkybox=1280;
const int heightSkybox=720;
//unsigned char image[widthImage*heightImage*4];
unsigned char textureSkybox[widthSkybox*heightSkybox*3];
const int tailleSkybox = 14;
const int nombreFacesSkybox = 30;
const bool showSkybox = true;  //DEBUG : Désactiver permet une plus grande liberté de mouvement
char presse;
int anglex;
int angley;
int x;
int y;
int xold;
int yold;
int angleRotation = 0; // Angle de rotation de la lumière 1

// Variables globales pour les annimations /!\ A DEPLACER QUAND POSSIBLE DANS INTERMITTENTDUSPECTACLE
float angleRotationAiles = 0.0;
bool sensMontantAiles = true;

float angleRotationBouche = 0.0;
bool sensMontantBouche = false;  //false = vers le haut, true = vers le bas
bool SPACE_PRESSED = false;

// Threads pour jouer de la musique ou des sons
std::thread bgMusic;
std::thread voice;

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
void loadJpegImage(char *fichier, unsigned char* texture);  //Un tableau est un pointeur
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

    /* Chargement de la texture */
    loadJpegImage("Ressources/Texture/skybox.jpg", textureSkybox);

    /* initialisation de glut et creation
     de la fenetre */
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    const int initWindowWidth = 1600;
    const int initWindowHeight = 900;
    glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH)/2 - initWindowWidth/2, glutGet(GLUT_SCREEN_HEIGHT)/2 - initWindowHeight/2);  //La fonction gère automatiquement les valeurs négatives en utilisant 0
    glutInitWindowSize(initWindowWidth,initWindowHeight);
    glutCreateWindow("SPYROpenGL");

    /* Initialisation d'OpenGL */
    glClearColor(0.0,0.0,0.0,0.0);
    glColor4f(1.0,1.0,1.0,1.0);
    glPointSize(2.0);
    glEnable(GL_DEPTH_TEST);

    /* Parametrage du placage de textures */
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    //glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,widthImage,heightImage,0,GL_RGBA,GL_UNSIGNED_BYTE,image);

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
    bgMusic = std::thread(IntermittentDuSpectacle::JoueDeLaMusique);

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


    float Wsize = (float) glutGet(GLUT_WINDOW_WIDTH)/ (float) glutGet(GLUT_WINDOW_HEIGHT);
    glLoadIdentity();
    glOrtho(-champDeVision*Wsize, champDeVision*Wsize, -champDeVision, champDeVision, -3-(997*!showSkybox), 1000);  //Gère le zoom/dézoom
    glRotatef(angley,1.0,0.0,0.0);
    glRotatef(anglex,0.0,1.0,0.0);

    srand(713705);  //Seed utilisé pour les couleurs aléatoires

    /********************************************/
    /*****     Utilisation des lumières     *****/
    /********************************************/
    IntermittentDuSpectacle::PlaceLaLumiereStatique(angleRotation);
    angleRotation++;


    /********************************************/
    /*****        Dessin de la SkyBox       *****/
    /********************************************/

    glColor4f(1,1,1,1);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,widthSkybox,heightSkybox,0,GL_RGB,GL_UNSIGNED_BYTE,textureSkybox);
    glEnable(GL_TEXTURE_2D);

    if (showSkybox)
    {
        float x[nombreFacesSkybox*nombreFacesSkybox];
        float y[nombreFacesSkybox*nombreFacesSkybox];
        float z[nombreFacesSkybox*nombreFacesSkybox];

        float fSphere[nombreFacesSkybox][nombreFacesSkybox][4];

        for(int j = 0; j < nombreFacesSkybox; j++)
        {
            for(int i = 0; i < nombreFacesSkybox; i++)
            {
                x[i+j*nombreFacesSkybox] = tailleSkybox*cos(2*i*M_PI/nombreFacesSkybox)*cos(-M_PI/2+j*M_PI/(nombreFacesSkybox-1));
                y[i+j*nombreFacesSkybox] = tailleSkybox*sin(2*i*M_PI/nombreFacesSkybox)*cos(-M_PI/2+j*M_PI/(nombreFacesSkybox-1));
                z[i+j*nombreFacesSkybox] = tailleSkybox*sin(-M_PI/2+j*M_PI/(nombreFacesSkybox-1));
            }
        }
        for(int j = 0; j < nombreFacesSkybox - 1; j++)
        {
            for(int i = 0; i < nombreFacesSkybox; i++)
            {
                fSphere[j][i][0] = ((i+1)%nombreFacesSkybox) + j*nombreFacesSkybox;
                fSphere[j][i][1] = ((i+1)%nombreFacesSkybox) + (j+1)*nombreFacesSkybox;
                fSphere[j][i][2] = i+(j+1)*nombreFacesSkybox;
                fSphere[j][i][3] = i+j*nombreFacesSkybox;

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


    glTranslatef(translationX, translationY, translationZ);  //Décalage de tout sur chaque axe



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
    angleRotationAiles = RotationneAileSpyro(angleRotationAiles);
    Montage::MontageSpyro(angleRotationAiles, angleRotationBouche);


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

    // Pour actualiser
    glutPostRedisplay();
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
        case 'z':
            //Zoom
            champDeVision -= 0.05;
            if (champDeVision < 0.05){
                //Zoom maximum
                champDeVision = 0.05;
            }
            glutPostRedisplay();
            break;
        case 'Z':
            //Dézoom
            champDeVision += 0.05;
            if (champDeVision > 6){
                //Dézoom maximum
                champDeVision = 6;
            }
            glutPostRedisplay();
            break;
        case 'i':
            translationY += 0.05;
            if (showSkybox && translationY > 0.2){
                //Translation maximum
                translationY = 0.2;
            }
            glutPostRedisplay();
            break;
        case 'k':
            translationY -= 0.05;
            if (showSkybox && translationY < -0.2){
                //Translation maximum
                translationY = -0.2;
            }
            glutPostRedisplay();
            break;
        case 'j':
            translationX -= 0.05;
            if (showSkybox && translationX < -0.2){
                //Translation maximum
                translationX = -0.2;
            }
            glutPostRedisplay();
            break;
        case 'J':
            translationZ -= 0.05;
            if (showSkybox && translationZ < -0.2){
                //Translation maximum
                translationZ = -0.2;
            }
            glutPostRedisplay();
            break;
        case 'l':
            translationX += 0.05;
            if (showSkybox && translationX > 0.2){
                //Translation maximum
                translationX = 0.2;
            }
            glutPostRedisplay();
            break;
        case 'L':
            translationZ += 0.05;
            if (showSkybox && translationZ > 0.2){
                //Translation maximum
                translationZ = 0.2;
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
                    if(voice.joinable()){
                        voice.join();
                        voice.~thread();
                    }
                    bool* PTR_SPACE_PRESSED = &SPACE_PRESSED;
                    voice = std::thread(IntermittentDuSpectacle::CrieSurLaVoiePublique, PTR_SPACE_PRESSED);
                }
            }
            break;
        case 'q' : /*la touche 'q' permet de quitter le programme */
            exit(0);
            break;
    }
}

void specialInput(int key, int x, int y)
{
    /*Pour la souris, des rotations de 1 minimum et uniquement d'entiers sont appliqués
      Autant faire la même chose avec les touches fléchées*/
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

void loadJpegImage(char *fichier, unsigned char* texture)
{
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *file;
    unsigned char *ligne;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    #ifdef __WIN32
    if (fopen_s(&file,fichier,"rb") != 0)
    {
        fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
        exit(1);
    }
    #elif __GNUC__
    if ((file = fopen(fichier,"rb")) == 0)
    {
        fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
        exit(1);
    }
    #endif
    jpeg_stdio_src(&cinfo, file);
    jpeg_read_header(&cinfo, TRUE);

    /*
    if ((cinfo.image_width!=256)||(cinfo.image_height!=256)) {
    fprintf(stdout,"Erreur : l'image doit etre de taille 256x256\n");
    exit(1);
    }
    */
    if (cinfo.jpeg_color_space==JCS_GRAYSCALE) {
        fprintf(stdout,"Erreur : l'image doit etre de type RGB\n");
        exit(1);
    }

    jpeg_start_decompress(&cinfo);
    ligne=texture;
    while (cinfo.output_scanline<cinfo.output_height)
    {
        ligne=texture+3*cinfo.output_width*cinfo.output_scanline;
        jpeg_read_scanlines(&cinfo,&ligne,1);
    }
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
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
        res += 0.5;
    }
    if(sensMontantAiles == false)
    {
        res -= 0.5;
    }
    return res;
}

float RotationneBoucheSpyro(float angle)
{
    float res = angle;
    if(res == 0.0)
    {
        sensMontantBouche = false;
    }
    else if(res == -6.0)
    {
        sensMontantBouche = true;
    }

    if(sensMontantBouche == true)
    {
        res += 0.5;
    }
    if(sensMontantBouche == false)
    {
        res -= 0.5;
    }
    return res;
}
