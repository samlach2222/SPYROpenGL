#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systemes */
#endif
#include <cstdlib>
#include <math.h>
#include <tuple>

#include "Point.h"
#include "Dessin.h"
#include "Creation.h"
#include "Montage.h"


const void Montage::MontageSpyro()
{
    /* param Corps */
	const float rayonCorps = 0.2;
    const float longueurCorps = 1;
    const float largeurDUnCoteDuCorps = sqrt(rayonCorps*rayonCorps + rayonCorps*rayonCorps - 2*rayonCorps*rayonCorps*cos(2*M_PI/5));  //théorème d'Al-Kashi : BC²=AB²+AC²-2.AB.AC.cos(BÂC)

    /* param Jambes */
    float taille = 0.1;
	float hauteurJambes = 0.2;
	float agrendissementJambes = (sqrt((taille*taille)/2) * largeurDUnCoteDuCorps / taille) - sqrt((taille*taille)/2); // Thales : Agrendissement = coté * (hypothénuse agrendie / hypothénuse) - coté

	/* param Ailes */
	float ecart = 0.05;
	float largeur = 0.2;
	float longueur = 0.3;
	float hauteur = 0.02;
	float decallageCentre = 0.2;

    glPushMatrix();
        /* Création du corps */
        glTranslatef(0,taille+2*hauteurJambes,0); // translation verticale de la hauteur de Jambe+Pied et translation horizontale de la largeur de la jambe
        glTranslatef(0,0,-3*sqrt(pow((sqrt((taille*taille)/2)),2)-pow(taille/2,2))); // translation pour placer le corps en adéquation avec les pieds
        std::tuple<Point, Point> deuxPointsBaseCorps = Creation::Corps(5,rayonCorps,longueurCorps);
        /* Création de la queue */
        Creation::Queue(rayonCorps, deuxPointsBaseCorps, 1);
        /* Création ailes */
        glPushMatrix();
            glTranslatef(0,0,longueurCorps);
            glTranslatef(0,largeurDUnCoteDuCorps/4,-2 * sqrt(pow((sqrt((taille*taille)/2))+agrendissementJambes,2) - pow(largeurDUnCoteDuCorps/2,2))); // placer les jambes avec le corps
            Creation::Aile(ecart, largeur, longueur, hauteur, decallageCentre);
        glPopMatrix();
    glPopMatrix();

    /* Création pattes arrières */
	Creation::JambesPlusPieds(taille, hauteurJambes, agrendissementJambes);
    glTranslatef(0,0,longueurCorps);
    glTranslatef(0,0,-2 * sqrt(pow((sqrt((taille*taille)/2))+agrendissementJambes,2) - pow(largeurDUnCoteDuCorps/2,2))); // placer les jambes avec le corps

    /* Création pattes avant */
    Creation::JambesPlusPieds(taille, hauteurJambes, agrendissementJambes);
    glTranslatef(0,0,-longueurCorps);
}
