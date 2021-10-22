/**
 * @file include/Creation.h
 * @brief Contient les définition des méthodes de création des parties de Spyro
 * @author Samuel LACHAUD
 * @version 1.0
 * @date 15/10/2021
 */

#ifndef CREATION_H
#define CREATION_H

#include <tuple>
#include "Point.h"

/**
 * @brief Classe de création des parties de Spyro
 */
class Creation
{
    public:
        static const void Jambes(float taille, float hauteur, bool sens, float agrendissement, float largeurDUnCoteDuCorps);
        static const void Pieds(float taille);
        static const void JambesPlusPieds(float taille, float hauteurJambes, float agrendissementJambes, float largeurDUnCoteDuCorps);
        static const void ComposantsTete(float taille, float hauteurCorne, float largeurCorne, float rayonCou, float hauteurCou, float decallageCou);
        static const void Queue(float longueurRayonCorps, std::tuple<Point, Point> deuxPointsBaseCorps, float taille = 1);
        static const void Aile(float ecart, float largeur, float longueur, float hauteur,float decallageCentre);
        static const std::tuple<Point, Point> Corps(int NM, float rayon, float longueur);
        static const void LiaisonCorpsCou(int NM, float rayon, float hauteur, float rotation = 0, float coeff = 1);
};

#endif // CREATION_H
