/**
 * @file include/Point.h
 * @brief Contient la définition de la classe gérant un point et ses coordonnées
 * @author Samuel LACHAUD
 * @version 1.0
 * @date 15/10/2021
 */

#ifndef POINT_H
#define POINT_H


/**
 * @brief Classe de création d'un point
 */
class Point
{
    public:
        Point();
    private:

        //coordonnées x, y et z du point
        /**
         * @brief coordonnée x
         */
        double x;

        /**
         * @brief coordonnée y
         */
        double y;

        /**
         * @brief coordonnée z
         */
        double z;

        // couleur r, v et b du point
        /**
         * @brief couleur rouge
         */
        float r;

        /**
         * @brief couleur verte
         */
        float g;

        /**
         * @brief couleur bleu
         */
        float b;
};

#endif // POINT_H
