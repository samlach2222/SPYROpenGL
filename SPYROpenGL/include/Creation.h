/**
 * @file include/Creation.h
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
        static const void Jambes(float taille, float hauteur, bool sens, float agrendissement);
        static const void Pieds(float taille);
        static const void JambesPlusPieds(float taille, float hauteurJambes, float agrendissementJambes);
        static const void ComposantsTete(float taille, float hauteurCorne, float largeurCorne, float rayonCou, float hauteurCou, float decallageCou);
        static const void Queue(float taille = 1);
        static const void Aile(float ecart, float largeur, float longueur, float hauteur);
        static const void Corps(int NM, float rayon, float longueur);
};

#endif // CREATION_H
