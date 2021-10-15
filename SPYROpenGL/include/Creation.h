/**
 * @file Creation.h
 * @brief Contient les définition des méthodes de création des parties de Spyro
 * @author Samuel LACHAUD
 * @version 1.0
 * @date 15/10/2021
 */

#ifndef CREATION_H
#define CREATION_H

/**
 * @brief Classe de création des parties de Spyro
 */
class Creation
{
    public:
        static const void Jambes(float taille, float hauteur, bool sens);
        static const void Pieds(float taille);
        static const void JambesPlusPieds(float taille, float hauteurJambes);
        static const void ComposantsTete(float taille, float hauteurCorne, float largeurCorne);
        static const void Queue(float taille = 1);
        static const void Aile(float ecart, float largeur, float longueur, float hauteur);
};

#endif // CREATION_H
