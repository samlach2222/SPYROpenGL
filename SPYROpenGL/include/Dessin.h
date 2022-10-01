/**
 * @file include/Dessin.h
 * @brief Contient les définition des méthodes de création des formes géométrique et sous-parties de Spyro
 * @author Loïs PAZOLA
 * @author Samuel LACHAUD
 * @version 3.2
 * @date 12/11/2021
 */

#ifndef DESSIN_H
#define DESSIN_H

#include "Point.h"

#include <tuple>

/**
 * @brief Classe de création des formes géométrique et sous-parties de Spyro
 */
class Dessin
{
    public:
        static const std::tuple<Point, Point> Cylindre(int NM, float rayon, float hauteur, float rotation = 0);
        static const void LiaisonCorpsCou(int NM, float rayon, float hauteur, float rotation = 0, float coeff = 1);
        static const void Sphere(float taille, int NP, int NM, bool yeux = false);
        static const void Cone(float hauteur, float rayon, int NM);
        static const void Criniere(float rayonSphere);
        static const void Prisme(float longueurX, float longueurZ, float hauteur, float coeffX = 1, float coeffZ = 1, float decalageSX = 0, float decalageSZ = 0);
        static const void Bouche(float rayonCou, float hauteur, float coeffX = 1, float coeffZ = 1, float decalageSZ = 0, float decalageSY = 0);
        static const void Nez(float rayonVersBouche, float hauteur, float boucheCoeffX, float coeffBoucheZ, float coeffIY = 1, float decalageZ = 0);
        static const void PremierePartieQueue(float longueurRayonCorps, std::tuple<Point, Point> deuxPointsBaseCorps, float hauteur, float coeff);
        static const void DeuxiemePartieQueue(float longueurX, float longueurZ, float hauteur, std::tuple<Point, Point> deuxPointsBaseCorps, float coeffX = 1, float coeffZ = 1, float decalageSX = 0, float decalageSZ = 0);
        static const void TroisiemePartieQueue(float longueurX, float longueurZ, float hauteur, std::tuple<Point, Point> deuxPointsBaseCorps, float decalageBX = 0, float decalageBZ = 0, float decalageSX = 0, float decalageSZ = 0);
        static const void Jambes(float longueurX, float longueurZ, float hauteur, bool sens, float agrandissement, float largeurDUnCoteDuCorps);
        static const void Cube(float taille);
        static const void Tetraedre(float longueurX, float longueurZ, float hauteur, float decalageBX = 0, float decalageBZ = 0, float decalageSX = 0, float decalageSZ = 0);
        static const void PyramideTronquee(float hauteur, float largeur, float longueur, float ecart);
        static const void Pyramide(float largeur, float longueur, float hauteur, float translationX = 0, float translationZ = 0);
        static const void Cou(int NM, float rayon, float hauteur, float decallage);

        static const void RandomColor3f();
        static const void AxesActuels(float translationX = 0, float translationY = 0, float translationZ = 0);
};

#endif // DESSIN_H
