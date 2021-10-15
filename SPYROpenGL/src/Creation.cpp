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
 * @param[in] taille     largeur de la jambe
 * @param[in] hauteur     hauteur de la jambe
 * @param[in] sens      sens de la rotation de la face supérieure
 */
const void Creation::Jambes(float taille, float hauteur, bool sens)
{
    glPushMatrix();
        glRotatef(45,0,-1,0);
        glTranslatef(-sqrt((taille*taille)/2),taille,0);
        Dessin::Jambes(sqrt((taille*taille)/2), sqrt((taille*taille)/2), hauteur, sens);
    glPopMatrix();
}

/**
 * @brief Méthode des créations des pieds de Spyro
 * @param[in] taille     taille des éléments du pieds
 */
const void Creation::Pieds(float taille)
{
    glPushMatrix();
        glRotatef(90,0,0,1);
        glTranslatef(0,0,taille);
        Dessin::Prisme(taille, 1, taille);
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
 * @param[in] taille     taille de l'ensemble
 * @param[in] hauteurJambes     hauteur de la jambe
 */
const void Creation::JambesPlusPieds(float taille, float hauteurJambes)
{
    // ******** DESSIN DES PIEDS + JAMBES ********
    Creation::Pieds(taille); // PIED 1
    Creation::Jambes(taille, hauteurJambes, false); // JAMBE 1
    glTranslatef(2*taille,0,0); // TRANSLATION 2EME PARTIE
    Creation::Pieds(taille); // PIED 2
    Creation::Jambes(taille, hauteurJambes, true); // JAMBE 2
    glTranslatef(-2*taille,0,0); // RETOUR ORIGINE
    // ******** FIN DESSIN PIED + JAMBES ********
}

/**
 * @brief Méthode de combinaison de la têtes, des cornes et de la crinière
 * @param[in] taille     rayon de la tête
 * @param[in] hauteurCorne     hauteur des cornes
 * @param[in] largeurCorne      largeur des cornes
 */
const void Creation::ComposantsTete(float taille, float hauteurCorne, float largeurCorne)
{
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
}

/**
 * @brief Méthode de création de la queue de Spyro
 * @param[in] taille     taille de la queue
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
