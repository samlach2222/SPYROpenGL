/**
 * @file include/Point.h
 * @brief Contient la définition de la classe gérant un point et ses coordonnées
 * @author Loïs PAZOLA
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
        /**
        * @brief Constructeur de point
        * @param x     Valeur d'initialisation des coordonnées du point en X
        * @param y     Valeur d'initialisation des coordonnées du point en Y
        * @param z     Valeur d'initialisation des coordonnées du point en Z
        */
        Point(double x = 0, double y = 0, double z = 0);

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
};

#endif // POINT_H
