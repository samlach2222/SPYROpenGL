/**
 * @file src/Creation.cpp
 * @brief Implémentation des méthodes de création des parties de Spyro
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 2.5
 * @date 04/10/2022
 */

#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systèmes */
#endif

#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif

#include "Creation.h"
#include "Dessin.h"

#include <math.h>

/**
 * @brief Méthode de création des jambes de Spyro
 * @param taille     largeur de la jambe
 * @param hauteur     hauteur de la jambe
 * @param sens      sens de la rotation de la face supérieure
 * @param agrandissement agrandissement de la jambe
 * @param largeurDUnCoteDuCorps donne la largeur d'un coté du cylindre formant le corps de Spyro
 */
const void Creation::Jambes(float taille, float hauteur, bool sens, float agrandissement, float largeurDUnCoteDuCorps)
{
    glPushMatrix();
        glRotatef(45,0,-1,0);
        glTranslatef(-sqrtf((taille*taille)/2),taille,0);
        Dessin::Jambes(sqrtf((taille*taille)/2), sqrtf((taille*taille)/2), hauteur, sens, agrandissement, largeurDUnCoteDuCorps);
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
        glTranslatef(-sqrtf((taille * taille) / 2), 0, 0);
        Dessin::Prisme(sqrtf((taille*taille)/2), sqrtf((taille*taille)/2), taille);
    glPopMatrix();
}

/**
 * @brief Méthode de combinaison des pieds et des jambes de Spyro
 * @param taille     taille de l'ensemble
 * @param hauteurJambes     hauteur de la jambe
 * @param agrandissementJambes agrandissement des jambes
 * @param largeurDUnCoteDuCorps donne la largeur du cylindre formant le corps
 */
const void Creation::JambesPlusPieds(float taille, float hauteurJambes, float agrandissementJambes, float largeurDUnCoteDuCorps)
{
    glPushMatrix();
        float hypotenuseDeBase = sqrtf(2*(taille * taille));
        float hypotenuseAgrandie = largeurDUnCoteDuCorps;
        float ecartEntreCentreEtJambe = (hypotenuseAgrandie-hypotenuseDeBase)/2;

        glTranslatef(-ecartEntreCentreEtJambe,0,0);
        Creation::Pieds(taille); // PIED 1
        Creation::Jambes(taille, hauteurJambes, false, agrandissementJambes, largeurDUnCoteDuCorps); // JAMBE 1
    glPopMatrix();
    glPushMatrix();
        glTranslatef(taille,0,0); // passer de l'autre coté de l'âxe
        glTranslatef(ecartEntreCentreEtJambe,0,0);
        Creation::Pieds(taille); // PIED 2
        Creation::Jambes(taille, hauteurJambes, true, agrandissementJambes, largeurDUnCoteDuCorps); // JAMBE 2
    glPopMatrix();
}

/**
 * @brief Méthode de combinaison de la têtes, des cornes et de la crinière
 * @param taille     rayon de la tête
 * @param hauteurCorne     hauteur des cornes
 * @param largeurCorne      largeur des cornes
 * @param rayonCou  rayon du coup
 * @param hauteurCou hauteur du cou
 * @param decalageCou décalage du coup vers l'avant
 */
const void Creation::ComposantsTete(float taille, float hauteurCorne, float largeurCorne, float rayonCou, float hauteurCou, float decalageCou)
{
    glPushMatrix();
        glPushMatrix();
            glTranslatef(0,taille + 0.80f*hauteurCou,0);
            //Dessin de la tête de SPYRO
            Dessin::Sphere(taille, 5, 5, true);

            //Dessin de la crinière de SPYRO
            Dessin::Criniere(taille*1.3f);

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
        Dessin::Cou(5,rayonCou,hauteurCou, decalageCou);
        //Dessin du cou de Spyro
    glPopMatrix();
}

/**
 * @brief Méthode de création de la queue de Spyro
 * @param longueurRayonCorps     longueur du rayon du corps
 * @param deuxPointsBaseCorps     Tuple de deux points correspondant à un coté du corps
 * @param taille     taille de la queue
 */
const void Creation::Queue(float longueurRayonCorps, std::tuple<Point, Point> deuxPointsBaseCorps, float taille)
{
    glPushMatrix();
        //Orientation de la queue à l'horizontale et avec la bonne rotation
        glRotatef(-90,1,0,0);
        glRotatef(180,0,1,0);

        //Dessin de la première partie de la queue de SPYRO
        const float longueurPremierePartieQueue = 0.6f;
        const float coeffPremierePartieQueue = 0.15f;
        glPushMatrix();
            //Dessin::Prisme(longueurRayonCorps*taille,longueurRayonCorps*taille,longueurPremierePartieQueue*taille,0.25,0.25);
            Dessin::PremierePartieQueue(longueurRayonCorps*taille, deuxPointsBaseCorps,longueurPremierePartieQueue*taille, coeffPremierePartieQueue);
        glPopMatrix();

        //Dessin de la deuxième partie de la queue
        const float longueurDeuxiemePartieQueue = 0.05f;
        const float coteDeuxiemePartieQueue = longueurRayonCorps*0.2f;
        glPushMatrix();
            glTranslatef(0,longueurPremierePartieQueue*taille,0);

            Point p1 = std::get<0>(deuxPointsBaseCorps);
            Point p2 = std::get<1>(deuxPointsBaseCorps);
            p1.x = p1.x*coeffPremierePartieQueue;
            p1.z = p1.z*coeffPremierePartieQueue;
            p2.x = p2.x*coeffPremierePartieQueue;
            p2.z = p2.z*coeffPremierePartieQueue;
            deuxPointsBaseCorps = std::make_tuple(p1, p2);
            const float ratioDecalageSXToDecalageSZ = 0.726f;
            const float coeffDeuxiemePartieQueue = 1.8f;
            const float decalageS = 0.04f;

            Dessin::DeuxiemePartieQueue(coteDeuxiemePartieQueue*taille,coteDeuxiemePartieQueue*taille,longueurDeuxiemePartieQueue*taille,deuxPointsBaseCorps,coeffDeuxiemePartieQueue,coeffDeuxiemePartieQueue,-decalageS*taille,decalageS*ratioDecalageSXToDecalageSZ*taille);
            //Pas de glPopMatrix maintenant car il reste la troisième partie de la queue à dessiner

            //Dessin de la troisième partie de la queue
            p1.x = p1.x*coeffDeuxiemePartieQueue;
            p1.z = p1.z*coeffDeuxiemePartieQueue;
            p2.x = p2.x*coeffDeuxiemePartieQueue;
            p2.z = p2.z*coeffDeuxiemePartieQueue;
            deuxPointsBaseCorps = std::make_tuple(p1, p2);
            glTranslatef(0, longueurDeuxiemePartieQueue*taille, 0);

            const float longueurTroisiemePartieQueue = 0.1f;

            Dessin::TroisiemePartieQueue(0.06f*taille, 0.06f*taille, longueurTroisiemePartieQueue*taille, deuxPointsBaseCorps, -decalageS*taille, decalageS*ratioDecalageSXToDecalageSZ*taille, -0.02f*taille, -0.02f*taille);
        glPopMatrix();
    glPopMatrix();
}

/**
 * @brief Méthode permettant de créer les deux ailes de Spyro
 * @param ecart écart du rectangle au trapèze
 * @param largeur largeur de l'aile
 * @param longueur de l'aile
 * @param hauteur de l'aile
 * @param decalageCentre décalage entre le centre et l'aile
 * @param rotationAiles correspond à l'angle de rotation de l'aile
 */
const void Creation::Aile(float ecart, float largeur, float longueur, float hauteur,float decalageCentre, float rotationAiles)
{
    float angleRotationRadian = atanf(ecart/largeur); // TOA
    float angleRotationDegree = (float) (angleRotationRadian*180/M_PI); // Rad --> Deg

    // Aile 1

    glPushMatrix();
        // Dessin de la sphère de jonction
        glPushMatrix();
            glTranslatef(0,0,largeur/4);
            glTranslatef(decalageCentre,0,0);
            glTranslatef(0,hauteur/2,0); // mise au centre de l'aile
            Dessin::Sphere(largeur/2,30,30);
        glPopMatrix();

        glTranslatef(decalageCentre,0,0); // décalage du centre
        glRotatef(angleRotationDegree, 0, 1, 0);

        //animation des ailes
        glRotatef(rotationAiles,0,0,1); // rotation pour battre verticalement
        glRotatef(rotationAiles/2,0,-1,0); // rotation pour battre sur l'horizontale

        glPushMatrix();
            // Dessin de la pyramide tronquée
            Dessin::PyramideTronquee(hauteur,largeur,longueur,ecart);

            // dessi du tétraèdre
            glTranslatef(longueur, hauteur, 0);
            glRotatef(angleRotationDegree, 0, 1, 0);
            glRotatef(90,0,0,-1);
            //animation de la seconde partie de l'aile
            glRotatef(rotationAiles/2,0,0,1); // rotation pour battre verticalement

            Dessin::Pyramide(sqrtf(ecart*ecart + largeur*largeur),hauteur,longueur*2, hauteur, 0);
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
            glTranslatef(decalageCentre,0,0);
            glTranslatef(0,hauteur/2,0); // mise au centre de l'aile
            Dessin::Sphere(largeur/2,30,30);
        glPopMatrix();

        glTranslatef(decalageCentre,0,0); // décalage du centre
        glRotatef(angleRotationDegree, 0, 1, 0);

        //animation des ailes
        glRotatef(rotationAiles,0,0,-1); // rotation pour battre verticalement
        glRotatef(rotationAiles/2,0,-1,0); // rotation pour battre sur l'horizontale


        glPushMatrix();
            // Dessin de la pyramide tronquée
            Dessin::PyramideTronquee(hauteur,largeur,longueur,ecart);

            // Dessin du tétraèdre
            glTranslatef(longueur, hauteur, 0);
            glRotatef(angleRotationDegree, 0, 1, 0);
            glRotatef(90,0,0,-1);
            //animation de la seconde partie de l'aile
            glRotatef(rotationAiles/2,0,0,-1); // rotation pour battre verticalement

            Dessin::Pyramide(sqrtf(ecart*ecart + largeur*largeur),hauteur,longueur*2, -hauteur, 0);
        glPopMatrix();
    glPopMatrix();
}

/**
 * @brief Méthode permettant de créer le corps de Spyro
 * @param NM    Nombre de cotés de chaque base du corps
 * @param rayon     Longueur du rayon du corps
 * @param longueur      Longueur du corps
 * @return un tuple de deux points correspondant à un coté du corps
 */
const std::tuple<Point, Point> Creation::Corps(int NM, float rayon, float longueur){
    glPushMatrix();
        glRotatef(90,1,0,0);
        //glRotatef((3*M_PI/10)*(180/M_PI), 0, 1, 0);  //angle en radians * 180/pi --> angle en degrés
        std::tuple<Point, Point> tuplePointsBaseCorps = Dessin::Cylindre(NM, rayon, longueur, -1.5);
    glPopMatrix();

    return tuplePointsBaseCorps;
}

/**
 * @brief Méthode permettant de créer la liaison du corps au cou de Spyro
 * @param NM    Nombre de côtés de chaque base
 * @param rayon     Longueur du rayon
 * @param hauteur     Hauteur de la liaison corps <--> cou
 * @param rotation       Rotation supplémentaire de "rotation*pi / NM" (optionnelle, défaut: 0)
 * @param coeff     Coefficient d'agrandissement de la base qui sera liée au cou par rapport à la base liée au corps
 */
const void Creation::LiaisonCorpsCou(int NM, float rayon, float hauteur, float rotation, float coeff){
    glPushMatrix();
        glTranslatef(0,0,1);
        glRotatef(90,1,0,0);

        Dessin::LiaisonCorpsCou(5,rayon,hauteur,rotation,coeff);  //La partie vers le cou se trouve
    glPopMatrix();
}
