/**
 * @file src/Dessin.cpp
 * @brief Implémentation des méthodes de création des formes géométrique et sous-parties de Spyro
 * @author Loïs PAZOLA
 * @author Samuel LACHAUD
 * @version 3.2
 * @date 12/11/2021
 */

#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systèmes */
#endif

#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif

#include "Dessin.h"
#include "Textures.h"

#include <tuple>
#include <math.h>
#include <vector>
using namespace std;

/**
 * @brief Méthode de création d'un cylindre
 * @param NM       Nombre de côtés de chaque base
 * @param rayon       Longueur du rayon
 * @param hauteur       Hauteur du cylindre
 * @param rotation       Rotation supplémentaire de "rotation*pi / NM" (optionnelle, défaut: 0)
 * @return un tuple de deux points correspondant à un coté du cylindre
 */
const tuple<Point, Point> Dessin::Cylindre(int NM, float rayon, float hauteur, float rotation){

    vector<float> x(NM * 2); // NM --> taille du nombre de subdivision d'une base * 2 (base du bas + base du haut)
    vector<float> y(NM * 2);
    vector<float> z(NM * 2);

    // Remplissage des coordonnées des points dans x et y et z;
    for(int i = 0; i < NM*2; i++)
    {
        x[i] = (float) (rayon*cos(2*i*M_PI/NM + rotation*M_PI/NM));  //Si rotation est différent de 0, "décale" les points sur le cercle implicitement utilisé pour avoir les points des deux bases
        z[i] = (float) (rayon*sin(2*i*M_PI/NM + rotation*M_PI/NM));

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
        glColor3f(0.40784f, 0.19607f, 0.50980f);
        glVertex3f(x[i], y[i], z[i]);
    }
    glEnd();

    //Dessin de la base haut
    glBegin(GL_POLYGON);
    for(int i = NM; i < NM*2; i++)
    {
        glColor3f(0.40784f, 0.19607f, 0.50980f);
        glVertex3f(x[i], y[i], z[i]);
    }
    glEnd();

    //Dessin des faces sur les côtés
    for (int i = 0; i < NM; i++){
        glBegin(GL_POLYGON);
            if(i == 1 || i == 2)
            {
                glColor3f(0.99607f+0.05f, 0.70196f+0.05f, 0.31372f+0.05f);
            }
            else
            {
               glColor3f(0.40784f, 0.19607f, 0.50980f);
            }
            glVertex3f(x[i], y[i], z[i]);
            glVertex3f(x[(i+1)%NM], y[(i+1)%NM], z[(i+1)%NM]);
            glVertex3f(x[((i+1)%NM)+NM], y[((i+1)%NM)+NM], z[((i+1)%NM)+NM]);
            glVertex3f(x[i+NM], y[i+NM], z[i+NM]);
        glEnd();
    }

    Point p1 = Point(x[NM*2-1], y[NM*2-1], z[NM*2-1]);
    Point p2 = Point(x[NM], y[NM], z[NM]);
    tuple<Point, Point> tuplePointsBaseCorps(p1, p2);

    return tuplePointsBaseCorps;
}

/**
 * @brief Méthode de création de la liaison du corps au cou
 * @param NM    Nombre de côtés de chaque base
 * @param rayon     Longueur du rayon
 * @param hauteur     Hauteur de la liaison corps <--> cou
 * @param rotation       Rotation supplémentaire de "rotation*pi / NM" (optionnelle, défaut: 0)
 * @param coeff     Coefficient d'agrandissement de la base qui sera liée au cou par rapport à la base liée au corps
 */
const void Dessin::LiaisonCorpsCou(int NM, float rayon, float hauteur, float rotation, float coeff){

    vector<float> x(NM * 2); // NM --> taille du nombre de subdivision d'une surface * 2 (surface du bas + surface du haut)
    vector<float> y(NM * 2);
    vector<float> z(NM * 2);

    // Remplissage des coordonnées des points dans x et y et z;
    for(int i = 0; i < NM*2; i++)
    {
        if (i < NM){  //Base du bas
            x[i] = (float)(rayon*cos(2*i*M_PI/NM + rotation*M_PI/NM));  //Si rotation est différent de 0, "décale" les points sur le cercle implicitement utilisé pour avoir les points des deux bases
            y[i] = 0;
            z[i] = (float)(rayon*sin(2*i*M_PI/NM + rotation*M_PI/NM));
        }
        else{  //Base du haut
            x[i] = (float)(rayon*coeff*cos(2*i*M_PI/NM + rotation*M_PI/NM));
            y[i] = (float)(hauteur+rayon*coeff*sin(2*i*M_PI/NM + rotation*M_PI/NM));
            z[i] = -hauteur;
        }
    }

    //Dessin de la base bas
    glBegin(GL_POLYGON);
    for(int i = 0; i < NM; i++)
    {
        glColor3f(0.40784f, 0.19607f, 0.50980f);
        glVertex3f(x[i], y[i], z[i]);
    }
    glEnd();

    //Dessin de la base haut
    glBegin(GL_POLYGON);
    for(int i = NM; i < NM*2; i++)
    {
        glColor3f(0.40784f, 0.19607f, 0.50980f);
        glVertex3f(x[i], y[i], z[i]);
    }
    glEnd();

    //Dessin des faces sur les côtés
    for (int i = 0; i < NM; i++){
        glBegin(GL_POLYGON);
            if(i == 1 || i == 2)
            {
                glColor3f(0.99607f+0.05f, 0.70196f+0.05f, 0.31372f+0.05f);
            }
            else
            {
               glColor3f(0.40784f, 0.19607f, 0.50980f);
            }
            glVertex3f(x[i], y[i], z[i]);
            glVertex3f(x[(i+1)%NM], y[(i+1)%NM], z[(i+1)%NM]);
            glVertex3f(x[((i+1)%NM)+NM], y[((i+1)%NM)+NM], z[((i+1)%NM)+NM]);
            glVertex3f(x[i+NM], y[i+NM], z[i+NM]);
        glEnd();
    }
}

/**
 * @brief Méthode de création d'une sphère
 * @param taille    Taille de la sphère
 * @param NP    Nombre de côtés à la verticale
 * @param NM    Nombre de côtés à l'horizontale
 * @param yeux    Applique une texture d'œil sur 2 faces symétriques
 */
const void Dessin::Sphere(float taille, int NP, int NM, bool yeux)
{
    if (yeux){
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,Textures::widthOeil,Textures::heightOeil,0,GL_RGB,GL_UNSIGNED_BYTE,textureOeil);
    }

    vector<float> x(NM*NP);
    vector<float> y(NM * NP);
    vector<float> z(NM * NP);

    vector<vector<vector<float>>> fSphere(NP, vector<vector<float>>(NM, vector<float>(4)));

    for(int j = 0; j < NP; j++)
    {
        for(int i = 0; i < NM; i++)
        {
            x[i+j*NM] = (float)(taille*cos(2*i*M_PI/NM)*cos(-M_PI/2+j*M_PI/(NP-1)));
            y[i+j*NM] = (float)(taille*sin(2*i*M_PI/NM)*cos(-M_PI/2+j*M_PI/(NP-1)));
            z[i+j*NM] = (float)(taille*sin(-M_PI/2+j*M_PI/(NP-1)));
        }
    }
    for(int j = 0; j < NP -1; j++)
    {
        for(int i = 0; i < NM; i++)
        {
            fSphere[j][i][0] = (float)(((i+1)%NM) + j*NM);
            fSphere[j][i][1] = (float)(((i+1)%NM) + (j+1)*NM);
            fSphere[j][i][2] = (float)(i+(j+1)*NM);
            fSphere[j][i][3] = (float)(i+j*NM);

            glPushMatrix();
                glRotatef(90,-1,0,0);
                glRotatef(90,0,0,-1);

                if (yeux && j==2 && (i == 0 || i == 4))
                {
                    glColor4f(1,1,1,1);
                    glEnable(GL_TEXTURE_2D);

                    glBegin(GL_POLYGON);
                        if (i==0)  //oeil gauche
                        {
                            glTexCoord2f(1,1);
                            glVertex3f(x[((i+1)%NM) + j*NM], y[((i+1)%NM) + j*NM], z[((i+1)%NM) + j*NM]);

                            glTexCoord2f(1,0);
                            glVertex3f(x[((i+1)%NM) + (j+1)*NM], y[((i+1)%NM) + (j+1)*NM], z[((i+1)%NM) + (j+1)*NM]);

                            glTexCoord2f(0,0);
                            glVertex3f(x[i+(j+1)*NM], y[i+(j+1)*NM], z[i+(j+1)*NM]);

                            glTexCoord2f(0,1);
                            glVertex3f(x[i+j*NM], y[i+j*NM], z[i+j*NM]);
                        }
                        if (i==4)  //oeil droite
                        {
                            glTexCoord2f(1,1);
                            glVertex3f(x[((i+1)%NM) + j*NM], y[((i+1)%NM) + j*NM], z[((i+1)%NM) + j*NM]);

                            glTexCoord2f(1,0);
                            glVertex3f(x[((i+1)%NM) + (j+1)*NM], y[((i+1)%NM) + (j+1)*NM], z[((i+1)%NM) + (j+1)*NM]);

                            glTexCoord2f(0,0);
                            glVertex3f(x[i+(j+1)*NM], y[i+(j+1)*NM], z[i+(j+1)*NM]);

                            glTexCoord2f(0,1);
                            glVertex3f(x[i+j*NM], y[i+j*NM], z[i+j*NM]);
                        }
                    glEnd();

                    glDisable(GL_TEXTURE_2D);
                }
                else
                {
                    glBegin(GL_POLYGON);
                        glColor3f(0.40784f+0.05f, 0.19607f+0.05f, 0.50980f+0.05f);
                        glVertex3f(x[((i+1)%NM) + j*NM], y[((i+1)%NM) + j*NM], z[((i+1)%NM) + j*NM]);

                        glVertex3f(x[((i+1)%NM) + (j+1)*NM], y[((i+1)%NM) + (j+1)*NM], z[((i+1)%NM) + (j+1)*NM]);

                        glVertex3f(x[i+(j+1)*NM], y[i+(j+1)*NM], z[i+(j+1)*NM]);

                        glVertex3f(x[i+j*NM], y[i+j*NM], z[i+j*NM]);
                    glEnd();
                }
            glPopMatrix();
        }
    }
}

/**
 * @brief Méthode de création d'un cône
 * @param hauteur    Hauteur du cône
 * @param rayon     Longueur du rayon
 * @param NM    Nombre de côtés (à l'horizontale)
 */
const void Dessin::Cone(float hauteur, float rayon, int NM)
{
    vector<float> x(NM); // NM --> taille du nombre de subdivison de la base
    vector<float> z(NM);

    // dessin de la base
    for(int i = 0; i < NM; i++)
    {
        x[i] = (float)(rayon*cos(2*i*M_PI/NM));
        z[i] = (float)(rayon*sin(2*i*M_PI/NM));
    }

    glBegin(GL_POLYGON);
    for(int i = 0; i < NM; i++)
    {
        glColor3f(0.99607f, 0.70196f, 0.31372f);
        glVertex3f(x[i], 0, z[i]);  // y toujours égal à 0 car le pentagone est en 2D
    }
    glEnd();

    // dessin du volume
    for(int i = 0; i < NM; i++)
    {
        glBegin(GL_POLYGON);
            glColor3f(0.99607f, 0.70196f, 0.31372f);
            glVertex3f(x[i], 0, z[i]); // Premier point du triangle

            glColor3f(0.99607f, 0.70196f, 0.31372f);
            glVertex3f(x[(i+1)%NM], 0, z[(i+1)%NM]); // Deuxième point du triangle

            glColor3f(0.99607f, 0.70196f, 0.31372f);
            glVertex3f(0, hauteur, 0);  // Sommet du triangle
        glEnd();
    }
}

/**
 * @brief Méthode de création d'une crinière
 * @param rayonSphere    Longueur du rayon de la sphère utilisé pour créer la crinière
 */
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
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

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

    //On ne peut pas utiliser un vector pour textureCriniereTransparente car
    //la fonction glTexImage2D (quelques lignes plus bas) ne le supporte pas
    unsigned char *textureCriniereTransparente = (unsigned char*) malloc(Textures::widthCriniere * Textures::heightCriniere * 4);
    if (!textureCriniereTransparente) {
        //malloc retourne null quand l'allocation de mémoire n'a pas pu avoir lieu (par exemple mémoire insuffisante)
        throw bad_alloc();
    }
    for (unsigned int i = 0; i < Textures::widthCriniere*Textures::heightCriniere; i++){
        unsigned char bleuCourant = textureCriniere[i*3 + 2];

        if (bleuCourant > 150) {
            //Pixel transparent
            textureCriniereTransparente[i*4 + 3] = 0;  //Alpha
        }
        else
        {
            //Pixel normal
            textureCriniereTransparente[i*4] = textureCriniere[i*3];  //Rouge
            textureCriniereTransparente[i*4 + 1] = textureCriniere[i*3 + 1];  //Vert
            textureCriniereTransparente[i*4 + 2] = bleuCourant;  //Bleu
            textureCriniereTransparente[i*4 + 3] = 255;  //Alpha
        }
    }
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,Textures::widthCriniere,Textures::heightCriniere,0,GL_RGBA,GL_UNSIGNED_BYTE,textureCriniereTransparente);
    free(textureCriniereTransparente);

    glColor4f(1,1,1,1);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
        glTranslatef(0,-rayonSphere*2.0f/4, -rayonSphere);
        glBegin(GL_POLYGON);
            glTexCoord2f(1,1);
            glVertex3f(0, 0, 0); // Point bas droit (à l'origine)

            glTexCoord2f(1,0);
            glVertex3f(0, 1.7f*rayonSphere, 0); // Point haut droit

            glTexCoord2f(0,0);
            glVertex3f(0, 1.7f*rayonSphere, 1.8f*rayonSphere); // Point haut gauche

            glTexCoord2f(0,1);
            glVertex3f(0, 0, 1.8f*rayonSphere); // Point bas gauche
        glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glColor4f(1,1,1,1);
}

/**
 * @brief Méthode de création d'un prisme (isocèle, rectangle)
 * @param longueurX     Longueur du prisme sur l'axe X
 * @param longueurZ     Longueur du prisme sur l'axe Z
 * @param hauteur       Hauteur du prisme
 * @param coeffX        Coefficient d'agrandissement de la surface haute du prisme par rapport à la surface basse sur l'axe X (optionnelle, défaut: 1)
 * @param coeffZ        Coefficient d'agrandissement de la surface haute du prisme par rapport à la surface basse sur l'axe Z (optionnelle, défaut: 1)
 * @param decalageSX    Décalage sur l'axe X du point de la surface haute se trouvant à l'angle droit (optionnelle, défaut: 0)
 * @param decalageSZ    Décalage sur l'axe Z du point de la surface haute se trouvant à l'angle droit (optionnelle, défaut: 0)
 */
const void Dessin::Prisme(float longueurX, float longueurZ, float hauteur, float coeffX, float coeffZ, float decalageSX, float decalageSZ)
{
    vector<vector<float>> coordPoints{
        {0, 0, 0},
        {longueurX, 0, 0},
        {0, 0, longueurZ},
        {decalageSX, hauteur, decalageSZ},
        {longueurX*coeffX, hauteur, 0},
        {0, hauteur, longueurZ*coeffZ}
    };

    //base bas
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*1, 0.19607f+0.05f*1, 0.50980f+0.05f*1);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();

    //base haut
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*0, 0.19607f+0.05f*0, 0.50980f+0.05f*0);
        glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
    glEnd();

    //côté hypothénuse
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*2, 0.19607f+0.05f*2, 0.50980f+0.05f*2);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
        glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
    glEnd();

    //côté axe x
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*3, 0.19607f+0.05f*3, 0.50980f+0.05f*3);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();

    //côté axe z
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*4, 0.19607f+0.05f*4, 0.50980f+0.05f*4);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();
}

/**
 * @brief Méthode de création de la bouche
 * @param rayonCou     Rayon du cou
 * @param hauteur     Hauteur entre le cou et la bouche
 * @param coeffX        Coefficient d'agrandissement de la surface haute (correspondant à la bouche) par rapport à la surface basse (accrochée au cou) sur l'axe X (optionnelle, défaut: 1)
 * @param coeffZ        Coefficient d'agrandissement de la surface haute (correspondant à la bouche) par rapport à la surface basse (accrochée au cou) sur l'axe Z (optionnelle, défaut: 1)
 * @param decalageSZ    Décalage sur l'axe Z du point isocèle de la surface haute (correspondant à la bouche) (optionnelle, défaut: 0)
 * @param decalageSY    Décalage sur l'axe Y du point isocèle de la surface haute (correspondant à la bouche) (optionnelle, défaut: 0)
 */
const void Dessin::Bouche(float rayonCou, float hauteur, float coeffX, float coeffZ, float decalageSZ, float decalageSY){

    const float rotationP1 = 4.5;
    const float rotationP2 = 0.5;

    vector<vector<float>> coordPoints{
        {0, 0, rayonCou},
        {static_cast<float>(rayonCou*cos(rotationP1*M_PI/5)), 0, static_cast<float>(rayonCou*sin(rotationP1*M_PI/5))},
        {static_cast<float>(rayonCou*cos(rotationP2*M_PI/5)), 0, static_cast<float>(rayonCou*sin(rotationP2*M_PI/5))},
        {0, hauteur+decalageSY, rayonCou*coeffZ + decalageSZ},
        {static_cast<float>(rayonCou*cos(rotationP1*M_PI/5)*coeffX), hauteur, static_cast<float>(rayonCou*sin(rotationP1*M_PI/5) + decalageSZ)},
        {static_cast<float>(rayonCou*cos(rotationP2*M_PI/5)*coeffX), hauteur, static_cast<float>(rayonCou*sin(rotationP2*M_PI/5) + decalageSZ)},
    };

    //base bas
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*0, 0.19607f+0.05f*0, 0.50980f+0.05f*0);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();

    //base haut
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*1, 0.19607f+0.05f*1, 0.50980f+0.05f*1);
        glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
    glEnd();

    //côté hypothénuse
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*2, 0.19607f+0.05f*2, 0.50980f+0.05f*2);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
        glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
    glEnd();

    //côté axe x
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*3, 0.19607f+0.05f*3, 0.50980f+0.05f*3);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();

    //côté axe z
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*4, 0.19607f+0.05f*4, 0.50980f+0.05f*4);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();
}

/**
 * @brief Méthode de création du nez
 * @param rayonVersBouche     Rayon pour aller aux deux points sur les côtés de la bouche
 * @param hauteur     Hauteur du nez
 * @param boucheCoeffX        Le coefficient d'agrandissement sur l'axe X qui A ETAIT utilisé pour la surface haute de la bouche
 * @param coeffBoucheZ        Le coefficient d'agrandissement sur l'axe Z qui A ETAIT utilisé pour la surface haute de la bouche
 * @param coeffIY       Coefficient d'agrandissement des deux points sur les côtés sur l'axe Y (optionnelle, défaut: 1)
 * @param decalageZ    Décalage sur l'axe Z des deux points isocèle (le point isocèle de chaque surface) (optionnelle, défaut: 0)
 */
const void Dessin::Nez(float rayonVersBouche, float hauteur, float boucheCoeffX, float coeffBoucheZ, float coeffIY, float decalageZ){
    const float rotationP1 = 4.5;
    const float rotationP2 = 0.5;

    //Le code créé un prisme, le cinquième et sixième point sont au même endroit pour faire un tétraèdre
    vector<vector<float>> coordPoints{
        {0, 0, rayonVersBouche*coeffBoucheZ + decalageZ},
        {static_cast<float>(rayonVersBouche*cos(rotationP1*M_PI/5)*boucheCoeffX), 0, static_cast<float>(rayonVersBouche*sin(rotationP1*M_PI/5))},
        {static_cast<float>(rayonVersBouche*cos(rotationP2*M_PI/5)*boucheCoeffX), 0, static_cast<float>(rayonVersBouche*sin(rotationP2*M_PI/5))},
        //{0, hauteur*coeffIY, rayonVersBouche*coeffBoucheZ + decalageZ},  //Quatrième coordPoints à la même hauteur que le cinquième et sixième
        {0, 0, rayonVersBouche*coeffBoucheZ + decalageZ},  //Quatrième coordPoints identique au premier
        {0, hauteur*coeffIY, static_cast<float>(rayonVersBouche*sin(rotationP1*M_PI/5))},
        {0, hauteur*coeffIY, static_cast<float>(rayonVersBouche*sin(rotationP2*M_PI/5))},
    };

    //base bas
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*0, 0.19607f+0.05f*0, 0.50980f+0.05f*0);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();

    //base haut
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*1, 0.19607f+0.05f*1, 0.50980f+0.05f*1);
        glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
    glEnd();

    //côté hypothénuse
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*2, 0.19607f+0.05f*2, 0.50980f+0.05f*2);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
        glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
    glEnd();

    //côté axe x
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*3, 0.19607f+0.05f*3, 0.50980f+0.05f*3);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();

    //côté axe z
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*4, 0.19607f+0.05f*4, 0.50980f+0.05f*4);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();
}

/**
 * @brief Méthode de création de la première partie de la queue
 * @param longueurRayonCorps      Longueur du rayon du corps
 * @param deuxPointsBaseCorps     Tuple de deux points correspondant à un coté du corps
 * @param hauteur       Hauteur de la première partie de la queue
 * @param coeff        Coefficient d'agrandissement de la surface haute de la première partie de la queue par rapport à la surface basse sur les axes X et Z (optionnelle, défaut: 1)
 */
const void Dessin::PremierePartieQueue(float longueurRayonCorps, tuple<Point, Point> deuxPointsBaseCorps, float hauteur, float coeff){

    /*  longueurRayonCorps² = moitieLongueurCoteCorps² + longueur²
    --> longueur² = longueurRayonCorps² - moitieLongueurCoteCorps²
    --> longueur = sqrt(longueurRayonCorps² - moitieLongueurCoteCorps²)*/
    //float longueur = sqrt(longueurRayonCorps*longueurRayonCorps - longueurCoteCorps/2*longueurCoteCorps/2);

    Point p1 = get<0>(deuxPointsBaseCorps);
    Point p2 = get<1>(deuxPointsBaseCorps);

    vector<vector<float>> coordPoints{
        {0, 0, 0},
        {static_cast<float>(p1.x), 0, static_cast<float>(p1.z)},
        {static_cast<float>(p2.x), 0, static_cast<float>(p2.z)},
        {0, hauteur, 0},
        {static_cast<float>(p1.x*coeff), hauteur, static_cast<float>(p1.z*coeff)},
        {static_cast<float>(p2.x*coeff), hauteur, static_cast<float>(p2.z*coeff)}
    };

    //base bas
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*0, 0.19607f+0.05f*0, 0.50980f+0.05f*0);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();

    //base haut
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*1, 0.19607f+0.05f*1, 0.50980f+0.05f*1);
        glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
    glEnd();

    //côté hypothénuse
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*2, 0.19607f+0.05f*2, 0.50980f+0.05f*2);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
        glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
    glEnd();

    //côté axe x
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*3, 0.19607f+0.05f*3, 0.50980f+0.05f*3);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();

    //côté axe z
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*4, 0.19607f+0.05f*4, 0.50980f+0.05f*4);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();
}

/**
 * @brief Méthode de création de la deuxième partie de la queue
 * @param longueurX     Longueur de la deuxième partie de la queue sur l'axe X
 * @param longueurZ     Longueur de la deuxième partie de la queue sur l'axe Z
 * @param hauteur       Hauteur de la deuxième partie de la queue
 * @param deuxPointsBaseCorps     Tuple de deux points correspondant à un coté du corps
 * @param coeffX        Coefficient d'agrandissement de la surface haute de la deuxième partie de la queue par rapport à la surface basse sur l'axe X (optionnelle, défaut: 1)
 * @param coeffZ        Coefficient d'agrandissement de la surface haute de la deuxième partie de la queue par rapport à la surface basse sur l'axe Z (optionnelle, défaut: 1)
 * @param decalageSX    Décalage sur l'axe X du point du sommet (optionnelle, défaut: 0)
 * @param decalageSZ    Décalage sur l'axe Z du point du sommet (optionnelle, défaut: 0)
 */
const void Dessin::DeuxiemePartieQueue(float longueurX, float longueurZ, float hauteur, tuple<Point, Point> deuxPointsBaseCorps, float coeffX, float coeffZ, float decalageSX, float decalageSZ){

    Point p1 = get<0>(deuxPointsBaseCorps);
    Point p2 = get<1>(deuxPointsBaseCorps);

    vector<vector<float>> coordPoints{
        {0, 0, 0},
        {static_cast<float>(p1.x), 0, static_cast<float>(p1.z)},
        {static_cast<float>(p2.x), 0, static_cast<float>(p2.z)},
        {decalageSX, hauteur, decalageSZ},
        {static_cast<float>(p1.x*coeffX), hauteur, static_cast<float>(p1.z*coeffZ)},
        {static_cast<float>(p2.x*coeffX), hauteur, static_cast<float>(p2.z*coeffZ)}
    };

    //base bas
    glBegin(GL_POLYGON);
        glColor3f(0.99607f+0.05f*0, 0.70196f+0.05f*0, 0.31372f+0.05f*0);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();

    //base haut
    glBegin(GL_POLYGON);
        glColor3f(0.99607f+0.05f*1, 0.70196f+0.05f*1, 0.31372f+0.05f*1);
        glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
    glEnd();

    //côté hypothénuse
    glBegin(GL_POLYGON);
        glColor3f(0.99607f+0.05f*2, 0.70196f+0.05f*2, 0.31372f+0.05f*2);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
        glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
    glEnd();

    //côté axe x
    glBegin(GL_POLYGON);
        glColor3f(0.99607f+0.05f*3, 0.70196f+0.05f*3, 0.31372f+0.05f*3);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();

    //côté axe z
    glBegin(GL_POLYGON);
        glColor3f(0.99607f+0.05f*4, 0.70196f+0.05f*4, 0.31372f+0.05f*4);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();
}

/**
 * @brief Méthode de création de la troisième partie de la queue
 * @param longueurX     Longueur du tétraèdre sur l'axe X
 * @param longueurZ     Longueur du tétraèdre sur l'axe Z
 * @param hauteur       Hauteur du tétraèdre
 * @param deuxPointsBaseCorps     Tuple de deux points correspondant à un coté du corps
 * @param decalageBX    Décalage sur l'axe X du point de la surface basse se trouvant à l'angle droit (optionnelle, défaut: 0)
 * @param decalageBZ    Décalage sur l'axe Z du point de la surface basse se trouvant à l'angle droit (optionnelle, défaut: 0)
 * @param decalageSX    Décalage sur l'axe X du point du sommet (optionnelle, défaut: 0)
 * @param decalageSZ    Décalage sur l'axe Z du point du sommet (optionnelle, défaut: 0)
 */
const void Dessin::TroisiemePartieQueue(float longueurX, float longueurZ, float hauteur, tuple<Point, Point> deuxPointsBaseCorps, float decalageBX, float decalageBZ, float decalageSX, float decalageSZ){

    Point p1 = get<0>(deuxPointsBaseCorps);
    Point p2 = get<1>(deuxPointsBaseCorps);

    vector<vector<float>> coordPoints{
        {decalageBX, 0, decalageBZ},
        {static_cast<float>(p1.x), 0, static_cast<float>(p1.z)},
        {static_cast<float>(p2.x), 0, static_cast<float>(p2.z)},
        {longueurX/2 + decalageSX, hauteur, longueurZ/2 + decalageSZ},
    };

    //base bas
    glBegin(GL_POLYGON);
        glColor3f(0.99607f+0.05f*3, 0.70196f+0.05f*3, 0.31372f+0.05f*3);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();

    //côté hypothénuse
    glBegin(GL_POLYGON);
        glColor3f(0.99607f+0.05f*2, 0.70196f+0.05f*2, 0.31372f+0.05f*2);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
    glEnd();

    //côté axe x
    glBegin(GL_POLYGON);
        glColor3f(0.99607f+0.05f*1, 0.70196f+0.05f*1, 0.31372f+0.05f*1);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();

    //côté axe z
    glBegin(GL_POLYGON);
        glColor3f(0.99607f+0.05f*0, 0.70196f+0.05f*0, 0.31372f+0.05f*0);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();
}

/**
 * @brief Méthode de création des jambes
 * @param longueurX     Longueur des jambes sur l'axe X
 * @param longueurZ     Longueur des jambes sur l'axe Z
 * @param hauteur   Hauteur des jambes
 * @param sens      Sens des jambes
 * @param agrandissement    Agrandissement de la surface du haut
 * @param largeurDUnCoteDuCorps donne la largeur d'un coté du cylindre formant le corps
 */
const void Dessin::Jambes(float longueurX, float longueurZ, float hauteur, bool sens, float agrandissement, float largeurDUnCoteDuCorps)
{
    float h = sqrtf(longueurX*longueurX + longueurZ*longueurZ); // hypoténuse du triangle du dessus
    float t = agrandissement;
    float tx = sqrtf(t*t/2);

    // longueurs du triangle de base et de l'agrandit
    float hypotenuseDeBase = sqrtf(2*(longueurX * longueurX));
    float hypotenuseAgrandie = largeurDUnCoteDuCorps;
    float coteDeBase = longueurX;
    float coteAgrandie = sqrtf(pow(hypotenuseAgrandie,2)/2);

    // coefficients d'agrandissement
    float coefficientAgrandissement = hypotenuseAgrandie/hypotenuseDeBase;
    float agrandissementHypotenuseParThales = hypotenuseDeBase*(coteAgrandie/coteDeBase); // Thalès
    float diagonaleAgrandissement = (coteDeBase*(hypotenuseAgrandie/hypotenuseDeBase))-coteDeBase;

    // calculs vecteurs de translation :
    float translation = sqrtf(pow(diagonaleAgrandissement,2) + pow((agrandissementHypotenuseParThales-hypotenuseDeBase)/2,2)) /1.75;

    // calculs de rotation de la face du dessus
    float rotationAxeVertical = sqrtf(pow(largeurDUnCoteDuCorps,2) - 0.2*0.2);
    float rotationAxeVerticalMoitie = rotationAxeVertical/2;
    float rotationAxeHorizontal = hypotenuseAgrandie - 0.2f;
    float rotationAxeHorizontalMoitie = rotationAxeHorizontal/2;

    if(sens)
    {
        vector<vector<float>> coordPoints{
            {0, 0, 0},
            {longueurX, 0, 0},
            {0, 0, longueurZ},
            {0-translation-rotationAxeHorizontalMoitie, hauteur+rotationAxeVerticalMoitie, 0-translation+rotationAxeHorizontalMoitie}, // POINT A
            {static_cast<float>((longueurZ+translation)*0.958), static_cast<float>(hauteur+rotationAxeVertical*1.10), 0}, //POINT C
            {0, hauteur, longueurZ+translation} // POINT B
        };

        //base bas
        glBegin(GL_POLYGON);
            glColor3f(0.40784f+0.05f*0, 0.19607f+0.05f*0, 0.50980f+0.05f*0);
            glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
            glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
            glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
        glEnd();

        //base haut
        glBegin(GL_POLYGON);
            glColor3f(0.40784f+0.05f*1, 0.19607f+0.05f*1, 0.50980f+0.05f*1);
            glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
            glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
            glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
        glEnd();

        //côté hypothénuse
        glBegin(GL_POLYGON);
            glColor3f(0.40784f+0.05f*2, 0.19607f+0.05f*2, 0.50980f+0.05f*2);
            glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
            glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
            glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
            glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glEnd();

        //côté axe x
        glBegin(GL_POLYGON);
            glColor3f(0.40784f+0.05f*3, 0.19607f+0.05f*3, 0.50980f+0.05f*3);
            glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
            glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
            glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
            glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
        glEnd();

        //côté axe z
        glBegin(GL_POLYGON);
            glColor3f(0.40784f+0.05f*4, 0.19607f+0.05f*4, 0.50980f+0.05f*4);
            glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
            glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
            glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
            glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
        glEnd();
    }
    else
    {
        vector<vector<float>> coordPoints{
            {0, 0, 0},
            {longueurX, 0, 0},
            {0, 0, longueurZ},
            {0-translation+rotationAxeHorizontalMoitie, hauteur+rotationAxeVerticalMoitie, 0-translation-rotationAxeHorizontalMoitie}, // POINT A
            {longueurZ+translation, hauteur, 0}, //POINT C
            {0, static_cast<float>(hauteur+rotationAxeVertical*1.10), static_cast<float>((longueurZ+translation)*0.958)} // POINT B
        };

        /*
            Depuis la queue :

            C---B
             \ /
              A
        */

        //base bas
        glBegin(GL_POLYGON);
            glColor3f(0.40784f+0.05f*0, 0.19607f+0.05f*0, 0.50980f+0.05f*0);
            glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
            glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
            glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
        glEnd();

        //base haut
        glBegin(GL_POLYGON);
            glColor3f(0.40784f+0.05f*1, 0.19607f+0.05f*1, 0.50980f+0.05f*1);
            glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
            glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
            glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
        glEnd();

        //côté hypothénuse
        glBegin(GL_POLYGON);
            glColor3f(0.40784f+0.05f*2, 0.19607f+0.05f*2, 0.50980f+0.05f*2);
            glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
            glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
            glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
            glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glEnd();

        //côté axe x
        glBegin(GL_POLYGON);
            glColor3f(0.40784f+0.05f*3, 0.19607f+0.05f*3, 0.50980f+0.05f*3);
            glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
            glVertex3f(coordPoints[4][0], coordPoints[4][1], coordPoints[4][2]);
            glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
            glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
        glEnd();

        //côté axe z
        glBegin(GL_POLYGON);
            glColor3f(0.40784f+0.05f*4, 0.19607f+0.05f*4, 0.50980f+0.05f*4);
            glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
            glVertex3f(coordPoints[5][0], coordPoints[5][1], coordPoints[5][2]);
            glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
            glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
        glEnd();
    }
}

/**
 * @brief Méthode de création d'un cube
 * @param taille    Taille du cube
 */
const void Dessin::Cube(float taille)
{
    // base bas
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*0, 0.19607f+0.05f*0, 0.50980f+0.05f*0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, taille);
        glVertex3f(taille, 0, taille);
        glVertex3f(taille, 0, 0);
    glEnd();

    // base haut
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*1, 0.19607f+0.05f*1, 0.50980f+0.05f*1);
        glVertex3f(0, taille, 0);
        glVertex3f(0, taille, taille);
        glVertex3f(taille, taille, taille);
        glVertex3f(taille, taille, 0);
    glEnd();

    // face devant
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*2, 0.19607f+0.05f*2, 0.50980f+0.05f*2);
        glVertex3f(0, 0, taille);
        glVertex3f(taille, 0, taille);
        glVertex3f(taille, taille, taille);
        glVertex3f(0, taille, taille);
    glEnd();

    // face droite
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*3, 0.19607f+0.05f*3, 0.50980f+0.05f*3);
        glVertex3f(taille, 0, taille);
        glVertex3f(taille, 0, 0);
        glVertex3f(taille, taille, 0);
        glVertex3f(taille, taille, taille);
    glEnd();

    // face derrière
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*4, 0.19607f+0.05f*4, 0.50980f+0.05f*4);
        glVertex3f(taille, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, taille, 0);
        glVertex3f(taille, taille, 0);
    glEnd();

    // face gauche
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*5, 0.19607f+0.05f*5, 0.50980f+0.05f*5);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, taille);
        glVertex3f(0, taille, taille);
        glVertex3f(0, taille, 0);
    glEnd();
}

/**
 * @brief Méthode de création d'un tétraèdre (le sommet se trouve par défaut au milieu de l'hypoténuse)
 * @param longueurX     Longueur du tétraèdre sur l'axe X
 * @param longueurZ     Longueur du tétraèdre sur l'axe Z
 * @param hauteur       Hauteur du tétraèdre
 * @param decalageBX    Décalage sur l'axe X du point de la surface basse se trouvant à l'angle droit (optionnelle, défaut: 0)
 * @param decalageBZ    Décalage sur l'axe Z du point de la surface basse se trouvant à l'angle droit (optionnelle, défaut: 0)
 * @param decalageSX    Décalage sur l'axe X du point du sommet (optionnelle, défaut: 0)
 * @param decalageSZ    Décalage sur l'axe Z du point du sommet (optionnelle, défaut: 0)
 */
const void Dessin::Tetraedre(float longueurX, float longueurZ, float hauteur, float decalageBX, float decalageBZ, float decalageSX, float decalageSZ)
{
    vector<vector<float>> coordPoints{
        {decalageBX, 0, decalageBZ},
        {longueurX, 0, 0},
        {0, 0, longueurZ},
        {longueurX/2 + decalageSX, hauteur, longueurZ/2 + decalageSZ},
    };

    //base bas
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*0, 0.19607f+0.05f*0, 0.50980f+0.05f*0);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();

    //côté hypothénuse
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*1, 0.19607f+0.05f*1, 0.50980f+0.05f*1);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
    glEnd();

    //côté axe x
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*2, 0.19607f+0.05f*2, 0.50980f+0.05f*2);
        glVertex3f(coordPoints[1][0], coordPoints[1][1], coordPoints[1][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();

    //côté axe z
    glBegin(GL_POLYGON);
        glColor3f(0.40784f+0.05f*3, 0.19607f+0.05f*3, 0.50980f+0.05f*3);
        glVertex3f(coordPoints[2][0], coordPoints[2][1], coordPoints[2][2]);
        glVertex3f(coordPoints[3][0], coordPoints[3][1], coordPoints[3][2]);
        glVertex3f(coordPoints[0][0], coordPoints[0][1], coordPoints[0][2]);
    glEnd();
}

/**
 * @brief Méthode de création d'une pyramide tronquée
 * @param hauteur     Hauteur du prisme tronquée
 * @param largeur     Largeur du prisme tronquée
 * @param longueur    Longueur du prisme tronquée
 * @param ecart     Longueur du décalage de deux points dans une direction opposée
 */
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
        glColor3f(0.99607f+0.05f*0, 0.70196f+0.05f*0, 0.31372f+0.05f*0);
        glVertex3f(0, 0, 0);
        glVertex3f(0-ecart, 0, largeur);
        glVertex3f(longueur+ecart, 0, largeur);
        glVertex3f(longueur, 0, 0);
    glEnd();

    // base haut (4,5,6,7)
    glBegin(GL_POLYGON);
        glColor3f(0.99607f+0.05f*1, 0.70196f+0.05f*1, 0.31372f+0.05f*1);
        glVertex3f(0, hauteur, 0);
        glVertex3f(0-ecart, hauteur, largeur);
        glVertex3f(longueur+ecart, hauteur, largeur);
        glVertex3f(longueur, hauteur, 0);
    glEnd();

    // face devant (1,2,6,5)
    glBegin(GL_POLYGON);
        glColor3f(0.99607f+0.05f*2, 0.70196f+0.05f*2, 0.31372f+0.05f*2);
        glVertex3f(0-ecart, 0, largeur);
        glVertex3f(longueur+ecart, 0, largeur);
        glVertex3f(longueur+ecart, hauteur, largeur);
        glVertex3f(0-ecart, hauteur, largeur);
    glEnd();

    // face droite (2,3,7,6)
    glBegin(GL_POLYGON);
        glColor3f(0.99607f+0.05f*3, 0.70196f+0.05f*3, 0.31372f+0.05f*3);
        glVertex3f(longueur+ecart, 0, largeur);
        glVertex3f(longueur, 0, 0);
        glVertex3f(longueur, hauteur, 0);
        glVertex3f(longueur+ecart, hauteur, largeur);
    glEnd();

    // face derrière (3,0,4,7)
    glBegin(GL_POLYGON);
        glColor3f(0.99607f+0.05f*4, 0.70196f+0.05f*4, 0.31372f+0.05f*4);
        glVertex3f(longueur, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, hauteur, 0);
        glVertex3f(longueur, hauteur, 0);
    glEnd();

    // face gauche (0,1,5,4)
    glBegin(GL_POLYGON);
        glColor3f(0.99607f+0.05f*5, 0.70196f+0.05f*5, 0.31372f+0.05f*5);
        glVertex3f(0, 0, 0);
        glVertex3f(0-ecart, 0, largeur);
        glVertex3f(0-ecart, hauteur, largeur);
        glVertex3f(0, hauteur, 0);
    glEnd();
}

/**
 * @brief Méthode de création d'une pyramide
 * @param largeur     Largeur de la pyramide
 * @param longueur     Longueur de la pyramide
 * @param hauteur     Hauteur de la pyramide
 * @param translationX    Longueur de la translation du point du sommet sur l'axe X
 * @param translationZ    Longueur de la translation du point du sommet sur l'axe Z
 */
const void Dessin::Pyramide(float largeur, float longueur, float hauteur, float translationX, float translationZ)
{
    /*
        l = largeur
        L = longueur
        h = hauteur

        liste des différents points:
        0 (0,0,0)
        1 (0,0,l)
        2 (L,0,l)
        3 (L,0,0)
        4 (translationX,h,translationZ)
    */

    // base bas (0,1,2,3)
    glBegin(GL_POLYGON);
        glColor3f(0.99607f+0.05f*4, 0.70196f+0.05f*4, 0.31372f+0.05f*4);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, largeur);
        glVertex3f(longueur, 0, largeur);
        glVertex3f(longueur, 0, 0);
    glEnd();

    // base gauche (1,4,0)
    glBegin(GL_POLYGON);
        glColor3f(0.99607f+0.05f*3, 0.70196f+0.05f*3, 0.31372f+0.05f*3);
        glVertex3f(0, 0, largeur);
        glVertex3f(translationX, hauteur, translationZ);
        glVertex3f(0, 0, 0);
    glEnd();

    // face devant (2,4,1)
    glBegin(GL_POLYGON);
        glColor3f(0.99607f+0.05f*2, 0.70196f+0.05f*2, 0.31372f+0.05f*2);
        glVertex3f(longueur, 0, largeur);
        glVertex3f(translationX, hauteur, translationZ);
        glVertex3f(0, 0, largeur);
    glEnd();

    // face droite (3,4,2)
    glBegin(GL_POLYGON);
        glColor3f(0.99607f+0.05f*1, 0.70196f+0.05f*1, 0.31372f+0.05f*1);
        glVertex3f(longueur, 0, 0);
        glVertex3f(translationX, hauteur, translationZ);
        glVertex3f(longueur, 0, largeur);
    glEnd();

    // face derrière (0,4,3)
    glBegin(GL_POLYGON);
        glColor3f(0.99607f+0.05f*0, 0.70196f+0.05f*0, 0.31372f+0.05f*0);
        glVertex3f(0, 0, 0);
        glVertex3f(translationX, hauteur, translationZ);
        glVertex3f(longueur, 0, 0);
    glEnd();
}

/**
 * @brief Méthode de dessin du cou de Spyro
 * @param NM int nombre de subdivision du cou
 * @param rayon float rayon du cou
 * @param hauteur float hauteur du cou
 * @param decalage float Décalage en avant du cou
 */
const void Dessin::Cou(int NM, float rayon, float hauteur, float decalage){

    vector<float> x(NM * 2); // NM --> taille du nombre de subdivison d'une base * 2 (base du bas + base du haut)
    vector<float> y(NM * 2);
    vector<float> z(NM * 2);

    // Remplissage des coordonnées des points dans x et y et z;
    for(int i = 0; i < NM*2; i++)
    {
        x[i] = (float)(rayon*cos(2*i*M_PI/NM -M_PI/NM));
        z[i] = (float)(rayon*sin(2*i*M_PI/NM -M_PI/NM));

        if (i < NM){  //Base du bas
            y[i] = 0;
            x[i] += decalage;
        }
        else{  //Base du haut
            y[i] = hauteur;
        }
    }

    //Dessin de la base bas
    glBegin(GL_POLYGON);
    for(int i = 0; i < NM; i++)
    {
        glColor3f(0.40784f, 0.19607f, 0.50980f);
        glVertex3f(x[i], y[i], z[i]);
    }
    glEnd();

    //Dessin de la base haut
    glBegin(GL_POLYGON);
    for(int i = NM; i < NM*2; i++)
    {
        glColor3f(0.40784f, 0.19607f, 0.50980f);
        glVertex3f(x[i], y[i], z[i]);
    }
    glEnd();

    //Dessin des faces sur les côtés
    for (int i = 0; i < NM; i++){
        glBegin(GL_POLYGON);
            if(i == 3 || i == 2)
            {
                glColor3f(0.99607f+0.05f, 0.70196f+0.05f, 0.31372f+0.05f);
            }
            else
            {
               glColor3f(0.40784f, 0.19607f, 0.50980f);
            }
            glVertex3f(x[i], y[i], z[i]);
            glVertex3f(x[(i+1)%NM], y[(i+1)%NM], z[(i+1)%NM]);
            glVertex3f(x[((i+1)%NM)+NM], y[((i+1)%NM)+NM], z[((i+1)%NM)+NM]);
            glVertex3f(x[i+NM], y[i+NM], z[i+NM]);
        glEnd();
    }
}


/**
 * @brief Méthode appelant la méthode glColor3f avec des valeurs aléatoires
 */
const void Dessin::RandomColor3f(){
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);  //Donne une valeur entre 0.0 et 1.0 inclus
    float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    glColor3f(r,g,b);
}

/**
 * @brief Affiche les axes X Y Z avec des lignes R G B à l'origine par rapport aux transformations actuelles (translations, rotations, etc.)
 * @param translationX      Translation du dessin des axes sur l'axe X (optionnelle, défaut: 0)
 * @param translationY      Translation du dessin des axes sur l'axe Y (optionnelle, défaut: 0)
 * @param translationZ      Translation du dessin des axes sur l'axe Z (optionnelle, défaut: 0)
 */
const void Dessin::AxesActuels(float translationX, float translationY, float translationZ){

    glPushMatrix();
        glTranslatef(translationX, translationY, translationZ);

        //axe des x en rouge
        glBegin(GL_LINES);
            glColor3f(1,0,0);
            glVertex3f(0,0,0);
            glVertex3f(1,0,0);
        glEnd();

        //axe des y en vert
        glBegin(GL_LINES);
            glColor3f(0,1,0);
            glVertex3f(0,0,0);
            glVertex3f(0,1,0);
        glEnd();

        //axe des z en bleu
        glBegin(GL_LINES);
            glColor3f(0,0,1);
            glVertex3f(0,0,0);
            glVertex3f(0,0,1);
        glEnd();
    glPopMatrix();
}
