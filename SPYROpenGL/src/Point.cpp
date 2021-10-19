/**
 * @file src/Point.cpp
 * @brief Implémentation de la classe gérant un point et ses coordonnées
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 1.0
 * @date 16/10/2021
 */

#include "Point.h"

/**
 * @brief Constructeur de point
 */
Point::Point(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}
