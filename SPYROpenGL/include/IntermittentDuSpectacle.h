/**
 * @file include/IntermittentDuSpectacle.h
 * @brief Contient la définition de la classe gérant les sons et lumières
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 1.0
 * @date 20/10/2021
 */

#ifndef INTERMITTENTDUSPECTACLE_H
#define INTERMITTENTDUSPECTACLE_H
#include <string>

/**
 * @brief Classe de gestion des sons et lumières
 */
class IntermittentDuSpectacle
{
    public:
        static const void CrieSurLaVoiePublique(bool* SPACE_PRESSED);
        static const void JoueDeLaMusique();
};

#endif // INTERMITTENTDUSPECTACLE_H
