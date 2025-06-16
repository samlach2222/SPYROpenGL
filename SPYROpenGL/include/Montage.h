/**
 * @file include/Montage.h
 * @brief Contient la définition de la classe gérant le montage des différentes créations
 * @author Samuel LACHAUD
 * @version 2.0
 * @date 12/11/2021
 */

#ifndef MONTAGE_H
#define MONTAGE_H

/**
 * @brief Classe de montage des créations pour Spyro
 */
class Montage
{
	public:
		/**
		* @brief Méthode permettant de monter l'intégralité des membres de Spyro
		* @param rotationAiles donne l'angle de rotation des ailes
		* @param rotationBouche donne l'angle de rotation de la bouche
		*/
		static const void MontageSpyro(float rotationAiles, float rotationBouche);

};

#endif // MONTAGE_H
