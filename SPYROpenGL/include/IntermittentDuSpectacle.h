/**
 * @file include/IntermittentDuSpectacle.h
 * @brief Contient la définition de la classe gérant les sons et lumières
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 1.4
 * @date 16/06/2024
 */

#ifndef INTERMITTENTDUSPECTACLE_H
#define INTERMITTENTDUSPECTACLE_H

#include <thread>

/**
 * @brief Classe de gestion des sons et lumières
 */
class IntermittentDuSpectacle
{
	public:
		/**
		* @brief Méthode permettant de jouer la voix de Spyro lors de l'appui sur la touche associée
		* @param SPACE_PRESSED indique si la barre espace à été appuyée (true pour oui, false pour non)
		*/
		static const void CrieSurLaVoiePublique(bool* SPACE_PRESSED);
		/**
		* @brief Méthode permettant de jouer le son en arrière plan de l'application, la musique boucle sans répéter la même.
		*/
		static const void JoueDeLaMusique();
		/**
		* @brief Méthode permettant de fermer la voix de Spyro après qu'il est fini de crier
		* @param voice thread utilisé pour la voix de Spyro
		*/
		static const void ArreteCrieSurLaVoiePublique(std::thread& voice);
		/**
		* @brief Méthode permettant de fermer le son en arrière plan de l'application immédiatement.
		* @param bgMusic thread utilisé pour le son en arrière plan de l'application.
		*/
		static const void ArreteJoueDeLaMusique(std::thread& bgMusic);
		/**
		* @brief Méthode permettant d'appliquer la lumière statique
		*/
		static const void PlaceLaLumiereStatique();
		/**
		* @brief Méthode permettant d'appliquer la lumière en rotation autour de Spyro
		* @param angle de rotation de la lumière
		*/
		static const void PlaceLaLumiereQuiBouge(int angle);
};

#endif // INTERMITTENTDUSPECTACLE_H
