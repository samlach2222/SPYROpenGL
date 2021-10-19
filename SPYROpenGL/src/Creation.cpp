/**
 * @file src/Creation.cpp
 * @brief Implémentation des méthodes de création des parties de Spyro
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 1.0
 * @date 16/10/2021
 */

#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systemes */
#endif

#include "Creation.h"
#include "Dessin.h"
#include "math.h"

/**
 * @brief Méthode de création des jambes de Spyro
 * @param taille     largeur de la jambe
 * @param hauteur     hauteur de la jambe
 * @param sens      sens de la rotation de la face supérieure
 */
const void Creation::Jambes(float taille, float hauteur, bool sens, float agrendissement)
{
    glPushMatrix();
        glRotatef(45,0,-1,0);
        glTranslatef(-sqrt((taille*taille)/2),taille,0);
        Dessin::Jambes(sqrt((taille*taille)/2), sqrt((taille*taille)/2), hauteur, sens,agrendissement);
    glPopMatrix();
}

/**
 * @brief Méthode des créations des pieds de Spyro
 * @param taille     taille des éléments du pieds
 */
const void Creation::Pieds(float taille)
{
    glPushMatrix();
        glRotatef(90,0,0,1);
        glTranslatef(0,0,taille);
        Dessin::Prisme(taille, 2*taille, taille);
    glPopMatrix();

	glPushMatrix();
        glTranslatef(-taille,0,0);
        Dessin::Cube(taille);
	glPopMatrix();

	glPushMatrix();
        glRotatef(45,0,-1,0);
        glTranslatef(-sqrt((taille*taille)/2),0,0);
        Dessin::Prisme(sqrt((taille*taille)/2), sqrt((taille*taille)/2), taille);
    glPopMatrix();
}

/**
 * @brief Méthode de combinaison des pieds et des jambes de Spyro
 * @param taille     taille de l'ensemble
 * @param hauteurJambes     hauteur de la jambe
 */
const void Creation::JambesPlusPieds(float taille, float hauteurJambes, float agrendissementJambes)
{
    Creation::Pieds(taille); // PIED 1
    Creation::Jambes(taille, hauteurJambes, false, agrendissementJambes); // JAMBE 1
    glTranslatef(3*taille,0,0); // TRANSLATION 2EME PARTIE
    Creation::Pieds(taille); // PIED 2
    Creation::Jambes(taille, hauteurJambes, true, agrendissementJambes); // JAMBE 2
    glTranslatef(-3*taille,0,0); // RETOUR ORIGINE
}

/**
 * @brief Méthode de combinaison de la têtes, des cornes et de la crinière
 * @param taille     rayon de la tête
 * @param hauteurCorne     hauteur des cornes
 * @param largeurCorne      largeur des cornes
 */
const void Creation::ComposantsTete(float taille, float hauteurCorne, float largeurCorne, float rayonCou, float hauteurCou, float decallageCou)
{
    glPushMatrix();
        glTranslatef(0,taille + 0.80*hauteurCou,0);
        //Dessin de la tête de SPYRO
        Dessin::Sphere(taille, 5, 5);

        //Dessin de la crinière de SPYRO
        Dessin::Criniere(taille);

        //Dessin des cornes de SPYRO
        glPushMatrix();
            glRotatef(15,1,0,-1);
            glTranslatef(taille/10,0,taille/7);
            Dessin::Cone(hauteurCorne, largeurCorne, 100);
        glPopMatrix();

        glPushMatrix();
            glRotatef(15,1,0,1);
            glTranslatef(-taille/10,0,taille/7);
            Dessin::Cone(hauteurCorne, largeurCorne, 100);
        glPopMatrix();
    glPopMatrix();
    //glTranslatef(0,-hauteurCou,0);
    glRotatef(90,0,1,0);
    Dessin::Cou(5,rayonCou,hauteurCou, decallageCou);
    //Dessin du cou de Spyro
}

/**
 * @brief Méthode de création de la queue de Spyro
 * @param taille     taille de la queue
 */
const void Creation::Queue(float taille)
{
    //Dessin de la première partie de la queue de SPYRO
    srand(32);
    const float longueurPremierePartieQueue = 2.0;
    Dessin::Prisme(0.8*taille,0.8*taille,longueurPremierePartieQueue*taille,0.25,0.25);

    //Dessin de la deuxième partie de la queue
    srand(64);
    const float longueurDeuxiemePartieQueue = 0.2;
    glPushMatrix();
        glTranslatef(0,longueurPremierePartieQueue*taille,0);
        Dessin::Prisme(0.2*taille,0.2*taille,longueurDeuxiemePartieQueue*taille,2,2,-0.1*taille,-0.1*taille);
    glPopMatrix();

    //Dessin de la troisième partie de la queue
    srand(128);
    const float longueurTroisiemePartieQueue = 0.4;
    glPushMatrix();
        glTranslatef(0, longueurPremierePartieQueue*taille + longueurDeuxiemePartieQueue*taille, 0);
        Dessin::Tetraedre(0.4*taille, 0.4*taille, longueurTroisiemePartieQueue*taille, -0.1*taille, -0.1*taille);
    glPopMatrix();
}

/**
 * @brief Méthode permettant de créer les deux ailes de Spyro
 * @param ecart écart du rectaugle au trapèze
 * @param largeur largeur de l'aile
 * @param longueur de l'aile
 * @param hauteur de l'aile
 */
const void Creation::Aile(float ecart, float largeur, float longueur, float hauteur)
{
    float angleRotationRadian = atan(ecart/largeur); // TOA
    float angleRotationDegree = angleRotationRadian*180/M_PI; // Rad --> Deg

    // Aile 1

    glPushMatrix();
        // Dessin de la sphère de jonction
        glPushMatrix();
            glTranslatef(0,0,largeur/4);
            glTranslatef(largeur,0,0);
            glTranslatef(0,hauteur/2,0); // mise au centre de l'aile
            Dessin::Sphere(largeur/2,30,30);
        glPopMatrix();

        glRotatef(angleRotationDegree, 0, 1, 0);
        glTranslatef(largeur,0,0); // décallage du centre
        glPushMatrix();
            // Dessin de la pyramide tronquée
            Dessin::PyramideTronquee(hauteur,largeur,longueur,ecart);

            // dessi du tétraèdre
            srand(128);
            glTranslatef(longueur, hauteur, 0);
            glRotatef(angleRotationDegree, 0, 1, 0);
            glRotatef(90,0,0,-1);

            Dessin::Pyramide(sqrt(ecart*ecart + largeur*largeur),hauteur,longueur*2, hauteur, 0);
        glPopMatrix();
    glPopMatrix();

    // Aile 2

    glPushMatrix();
        // Transformation pour passer à l'autre coté
        glRotatef(180,0,0,1);
        glTranslatef(0,-hauteur,0);

        // Dessin de la sphère de jonction
        glPushMatrix();
            glTranslatef(0,0,largeur/4); // même niveau que l'aile
            glTranslatef(largeur,0,0);
            glTranslatef(0,hauteur/2,0); // mise au centre de l'aile
            Dessin::Sphere(largeur/2,30,30);
        glPopMatrix();

        glRotatef(angleRotationDegree, 0, 1, 0);
        glTranslatef(largeur,0,0); // décallage du centre
        glPushMatrix();
            // Dessin de la pyramide tronquée
            Dessin::PyramideTronquee(hauteur,largeur,longueur,ecart);

            // dessi du tétraèdre
            srand(128);
            glTranslatef(longueur, hauteur, 0);
            glRotatef(angleRotationDegree, 0, 1, 0);
            glRotatef(90,0,0,-1);

            Dessin::Pyramide(sqrt(ecart*ecart + largeur*largeur),hauteur,longueur*2, -hauteur, 0);
        glPopMatrix();
    glPopMatrix();
}

const void Creation::Corps(int NM, float rayon, float longueur){
    glPushMatrix();
        glRotatef(90,1,0,0);
        glRotatef((3*M_PI/10)*(180/M_PI), 0, 1, 0);  //angle en radians * 180/pi --> angle en degrés
        Dessin::Cylindre(NM, rayon, longueur);
    glPopMatrix();
}
