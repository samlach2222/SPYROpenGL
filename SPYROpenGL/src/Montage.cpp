/**
 * @file src/Montage.cpp
 * @brief Implémentation du montage des différentes créations
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 2.0
 * @date 12/11/2021
 */

#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include "GL/glut.h"   /* Pour les autres systèmes */
#endif

#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif

#include <cstdlib>
#include <math.h>
#include <tuple>

#include "../include/Point.h"
#include "../include/Dessin.h"
#include "../include/Creation.h"
#include "../include/Montage.h"


/**
 * @brief Méthode permettant de monter l'intégralité des membres de Spyro
 * @param rotationAiles donne l'angle de rotation des ailes
 * @param rotationBouche donne l'angle de rotation de la bouche
 */
const void Montage::MontageSpyro(float rotationAiles, float rotationBouche)
{
    /* param Corps */
	const float rayonCorps = 0.2;
    const float longueurCorps = 1;
    const float largeurDUnCoteDuCorps = sqrt(rayonCorps*rayonCorps + rayonCorps*rayonCorps - 2*rayonCorps*rayonCorps*cos(2*M_PI/5));  //théorème d'Al-Kashi : BC²=AB²+AC²-2.AB.AC.cos(BÂC)

    /* param LiaisonCorpsCou */
    const float coeffLiaisonCorpsCouVersLeCou = 0.5;
    const float hauteurLiaisonCorpsCou = 0.2;

    /* param Jambes */
    float taille = 0.1;
	float hauteurJambes = 0.2;

	/* param Ailes */
	float ecart = 0.05;
	float largeur = 0.2;
	float longueur = 0.3;
	float hauteur = 0.02;
	float decalageCentre = 0.2;

	/* param Cou */
	float hauteurCou = 0.25;
	float decalageCou = 0;

	/* param Cornes */
	float hauteurCorne = 1;
	float largeurCorne = 0.15;

	/* param Tête */
    float tailleTete = 0.5;

    /* param Bouche */
    const float boucheCoeffX = 3;
    const float boucheCoeffZ = 5;
    const float boucheInclinaison = -0.1;

    /* param Nez */
    const float nezCoeffIY = 8;
    glPushMatrix();
        glTranslatef(0,taille+2*hauteurJambes,0); // translation verticale de la hauteur de Jambe+Pied et translation horizontale de la largeur de la jambe
        glTranslatef(0,0,-3*sqrt(pow((sqrt((taille*taille)/2)),2)-pow(taille/2,2))); // translation pour placer le corps en adéquation avec les pieds

        /* Création du corps */
        std::tuple<Point, Point> deuxPointsBaseCorps = Creation::Corps(5,rayonCorps,longueurCorps);
        /* Création de la queue */
        Creation::Queue(rayonCorps, deuxPointsBaseCorps, 1);
        /* Création de la liaison corps <--> cou */
        Creation::LiaisonCorpsCou(5,rayonCorps,hauteurLiaisonCorpsCou, -1.5, coeffLiaisonCorpsCouVersLeCou);  //La partie vers le cou se trouve
        /* Création cou et tête*/
        // translation hauteurLiaisonCorpsCou vers le devant (plus la longueur du corps puis vers le haut)
        glPushMatrix();
            //Cou, tête, cornes, crinière
            glTranslatef(0, hauteurLiaisonCorpsCou, 0);
            glTranslatef(0, 0, hauteurLiaisonCorpsCou+longueurCorps);
            Creation::ComposantsTete(tailleTete, hauteurCorne, largeurCorne,rayonCorps*coeffLiaisonCorpsCouVersLeCou, hauteurCou,decalageCou);

            //Bouche (et menton)
            //Déplacement de l'origine sur le milieu de la surface haute du cou
            glTranslatef(0, hauteurCou, 0);
            Dessin::Bouche(rayonCorps*coeffLiaisonCorpsCouVersLeCou, tailleTete*0.3, boucheCoeffX, boucheCoeffZ, tailleTete*0.2, tailleTete*boucheInclinaison);

            //Nez
            //Déplacement de l'origine sur le "milieu" (il n'y a pas réellement de point à cet endroit) du prolongement du cou utilisé pour la surface haute de la bouche
            glTranslatef(0,tailleTete*0.3,tailleTete*0.2);
            glRotatef(rotationBouche,-1,0,0); // animation bouche Spyro (quand appui sur ESPACE)
            Dessin::Nez(rayonCorps*coeffLiaisonCorpsCouVersLeCou, tailleTete*0.1, boucheCoeffX, boucheCoeffZ, nezCoeffIY, 0);
        glPopMatrix();
        /* Création ailes */
        glPushMatrix();
            glTranslatef(0,0,longueurCorps*0.7);
            Creation::Aile(ecart, largeur, longueur, hauteur, decalageCentre, rotationAiles);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        /* Création pattes arrières */
        Creation::JambesPlusPieds(taille, hauteurJambes, 0, largeurDUnCoteDuCorps); // agrandissement gèré en interne

        /* Création pattes avant */
        glTranslatef(0,0,longueurCorps-2*taille);
        Creation::JambesPlusPieds(taille, hauteurJambes, 0, largeurDUnCoteDuCorps);
    glPopMatrix();
}
