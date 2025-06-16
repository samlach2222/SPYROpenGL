/**
 * @file include/Creation.h
 * @brief Contient les définition des méthodes de création des parties de Spyro
 * @author Samuel LACHAUD
 * @version 2.4
 * @date 26/10/2021
 */

#ifndef CREATION_H
#define CREATION_H

#include "Point.h"

#include <tuple>

/**
 * @brief Classe de création des parties de Spyro
 */
class Creation
{
	public:
		/**
		* @brief Méthode de création des jambes de Spyro
		* @param taille     largeur de la jambe
		* @param hauteur     hauteur de la jambe
		* @param sens      sens de la rotation de la face supérieure
		* @param agrandissement agrandissement de la jambe
		* @param largeurDUnCoteDuCorps donne la largeur d'un coté du cylindre formant le corps de Spyro
		*/
		static const void Jambes(float taille, float hauteur, bool sens, float agrandissement, float largeurDUnCoteDuCorps);
		/**
		* @brief Méthode des créations des pieds de Spyro
		* @param taille     taille des éléments du pieds
		*/
		static const void Pieds(float taille);
		/**
		* @brief Méthode de combinaison des pieds et des jambes de Spyro
		* @param taille     taille de l'ensemble
		* @param hauteurJambes     hauteur de la jambe
		* @param agrandissementJambes agrandissement des jambes
		* @param largeurDUnCoteDuCorps donne la largeur du cylindre formant le corps
		*/
		static const void JambesPlusPieds(float taille, float hauteurJambes, float agrandissementJambes, float largeurDUnCoteDuCorps);
		/**
		* @brief Méthode de combinaison de la têtes, des cornes et de la crinière
		* @param taille     rayon de la tête
		* @param hauteurCorne     hauteur des cornes
		* @param largeurCorne      largeur des cornes
		* @param rayonCou  rayon du coup
		* @param hauteurCou hauteur du cou
		* @param decalageCou décalage du coup vers l'avant
		*/
		static const void ComposantsTete(float taille, float hauteurCorne, float largeurCorne, float rayonCou, float hauteurCou, float decalageCou);
		/**
		* @brief Méthode de création de la queue de Spyro
		* @param longueurRayonCorps     longueur du rayon du corps
		* @param deuxPointsBaseCorps     Tuple de deux points correspondant à un coté du corps
		* @param taille     taille de la queue
		*/
		static const void Queue(float longueurRayonCorps, std::tuple<Point, Point> deuxPointsBaseCorps, float taille = 1);
		/**
		* @brief Méthode permettant de créer les deux ailes de Spyro
		* @param ecart écart du rectangle au trapèze
		* @param largeur largeur de l'aile
		* @param longueur de l'aile
		* @param hauteur de l'aile
		* @param decalageCentre décalage entre le centre et l'aile
		* @param rotationAiles correspond à l'angle de rotation de l'aile
		*/
		static const void Aile(float ecart, float largeur, float longueur, float hauteur,float decalageCentre, float rotationAiles);
		/**
		* @brief Méthode permettant de créer le corps de Spyro
		* @param NM    Nombre de cotés de chaque base du corps
		* @param rayon     Longueur du rayon du corps
		* @param longueur      Longueur du corps
		* @return un tuple de deux points correspondant à un coté du corps
		*/
		static const std::tuple<Point, Point> Corps(int NM, float rayon, float longueur);
		/**
		* @brief Méthode permettant de créer la liaison du corps au cou de Spyro
		* @param NM    Nombre de côtés de chaque base
		* @param rayon     Longueur du rayon
		* @param hauteur     Hauteur de la liaison corps <--> cou
		* @param rotation       Rotation supplémentaire de "rotation*pi / NM" (optionnelle, défaut: 0)
		* @param coeff     Coefficient d'agrandissement de la base qui sera liée au cou par rapport à la base liée au corps
		*/
		static const void LiaisonCorpsCou(int NM, float rayon, float hauteur, float rotation = 0, float coeff = 1);
};

#endif // CREATION_H
