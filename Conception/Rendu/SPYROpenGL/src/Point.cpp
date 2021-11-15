/**
 * @file src/Point.cpp
 * @brief Implémentation de la classe gérant un point et ses coordonnées
 * @author Loïs PAZOLA
 * @version 1.0
 * @date 16/10/2021
 */

#include "Point.h"

/**
 * @brief Constructeur de point
 * @param x     Valeur d'initialisation des coordonnées du point en X
 * @param y     Valeur d'initialisation des coordonnées du point en Y
 * @param z     Valeur d'initialisation des coordonnées du point en Z
 */
Point::Point(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}
