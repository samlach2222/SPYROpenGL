#include "Dessin.h"

#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systemes */
#endif
#include "math.h"

const void Dessin::Cylindre(int NM, float rayon, float hauteur){

    float x[NM*2]; // NM --> taille du nombre de subdivison d'une base * 2 (base du bas + base du haut)
    float y[NM*2];
    float z[NM*2];

    // Remplissage des coordonnées des points dans x et y et z;
    for(int i = 0; i < NM*2; i++)
    {
        x[i] = rayon*cos(2*i*M_PI/NM);
        z[i] = rayon*sin(2*i*M_PI/NM);

        if (i < NM){  //Base du bas
            y[i] = 0;
        }
        else{  //Base du haut
            y[i] = hauteur;
        }
    }

    //Dessin de la base bas
    glBegin(GL_POLYGON);
    for(int i = 0; i < NM; i++)
    {
        RandomColor3f();
        glVertex3f(x[i], y[i], z[i]);
    }
    glEnd();

    //Dessin de la base haut
    glBegin(GL_POLYGON);
    for(int i = NM; i < NM*2; i++)
    {
        RandomColor3f();
        glVertex3f(x[i], y[i], z[i]);
    }
    glEnd();

    //Dessin des faces sur les côtés
    for (int i = 0; i < NM; i++){
        glBegin(GL_POLYGON);
			Dessin::RandomColor3f();
			glVertex3f(x[i], y[i], z[i]);
			glVertex3f(x[(i+1)%NM], y[(i+1)%NM], z[(i+1)%NM]);
			glVertex3f(x[((i+1)%NM)+NM], y[((i+1)%NM)+NM], z[((i+1)%NM)+NM]);
			glVertex3f(x[i+NM], y[i+NM], z[i+NM]);
        glEnd();
    }
}

const void Dessin::RandomColor3f(){
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);  //Donne une valeur entre 0.0 et 1.0 inclus
    float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    glColor3f(r,g,b);
}

const void Dessin::Sphere(float taille, int NP, int NM)
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

const void Dessin::Cone(float hauteur, float rayon, int NM)
{
    float x[NM]; // NM --> taille du nombre de subdivison de la base
    float z[NM];

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

const void Dessin::Criniere(float rayonSphere)
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
    glPushMatrix();
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

const void Dessin::Prisme(float longueurX, float longueurZ, float hauteur, float coeffX, float coeffZ, float decalageSX, float decalageSZ)
{
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
        Dessin::RandomColor3f();
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();

    //base haut
    glBegin(GL_POLYGON);
        Dessin::RandomColor3f();
        glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
    glEnd();

    //côté hypothénuse
    glBegin(GL_POLYGON);
        Dessin::RandomColor3f();
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
        glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
    glEnd();

    //côté axe x
    glBegin(GL_POLYGON);
        Dessin::RandomColor3f();
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();

    //côté axe z
    glBegin(GL_POLYGON);
        Dessin::RandomColor3f();
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();
}

const void Dessin::Jambes(float longueurX, float longueurZ, float hauteur, bool sens)
{
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

const void Dessin::Cube(float taille)
{
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

const void Dessin::Tetraedre(float longueurX, float longueurZ, float hauteur, float decalageBX, float decalageBZ, float decalageSX, float decalageSZ)
{
    float coordPoints[4][3] = {
        {decalageBX, 0, decalageBZ},
        {longueurX, 0, 0},
        {0, 0, longueurZ},
        {longueurX/2 + decalageSX, hauteur, longueurZ/2 + decalageSZ},
    };

    //base bas
    glBegin(GL_POLYGON);
        Dessin::RandomColor3f();
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();

    //côté hypothénuse
    glBegin(GL_POLYGON);
        Dessin::RandomColor3f();
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
    glEnd();

    //côté axe x
    glBegin(GL_POLYGON);
        Dessin::RandomColor3f();
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();

    //côté axe z
    glBegin(GL_POLYGON);
        Dessin::RandomColor3f();
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();
}

const void Dessin::PyramideTronquee(float hauteur, float largeur, float longueur, float ecart)
{
    /*
        l = largeur
        L = longueur
        h = hauteur

        liste des différents points:
        0 (0,0,0)       4 (0,h,0)
        1 (0,0,l)       5 (0,h,l)
        2 (L,0,l)       6 (L,h,l)
        3 (L,0,0)       7 (L,h,0)
    */

    // base bas (0,1,2,3)
    glBegin(GL_POLYGON);
        glColor3f(0.4, 0.6, 0.2);
        glVertex3f(0, 0, 0);
        glVertex3f(0-ecart, 0, largeur);
        glVertex3f(longueur+ecart, 0, largeur);
        glVertex3f(longueur, 0, 0);
    glEnd();

    // base haut (4,5,6,7)
    glBegin(GL_POLYGON);
        glColor3f(0.2, 0.2, 0.2);
        glVertex3f(0, hauteur, 0);
        glVertex3f(0-ecart, hauteur, largeur);
        glVertex3f(longueur+ecart, hauteur, largeur);
        glVertex3f(longueur, hauteur, 0);
    glEnd();

    // face devant (1,2,6,5)
    glBegin(GL_POLYGON);
        glColor3f(0.6, 0.6, 0.2);
        glVertex3f(0-ecart, 0, largeur);
        glVertex3f(longueur+ecart, 0, largeur);
        glVertex3f(longueur+ecart, hauteur, largeur);
        glVertex3f(0-ecart, hauteur, largeur);
    glEnd();

    // face droite (2,3,7,6)
    glBegin(GL_POLYGON);
        glColor3f(0.4, 0.4, 0.2);
        glVertex3f(longueur+ecart, 0, largeur);
        glVertex3f(longueur, 0, 0);
        glVertex3f(longueur, hauteur, 0);
        glVertex3f(longueur+ecart, hauteur, largeur);
    glEnd();

    // face derrière (3,0,4,7)
    glBegin(GL_POLYGON);
        glColor3f(0.6, 0.6, 0.6);
        glVertex3f(longueur, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, hauteur, 0);
        glVertex3f(longueur, hauteur, 0);
    glEnd();

    // face gauche (0,1,5,4)
    glBegin(GL_POLYGON);
        glColor3f(0.2, 0.6, 0.2);
        glVertex3f(0, 0, 0);
        glVertex3f(0-ecart, 0, largeur);
        glVertex3f(0-ecart, hauteur, largeur);
        glVertex3f(0, hauteur, 0);
    glEnd();
}