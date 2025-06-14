/**
 * @file include/IntermittentDuSpectacle.h
 * @brief Contient la définition de la classe gérant les sons et lumières
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 1.3
 * @date 14/06/2024
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
        static const void CrieSurLaVoiePublique(bool* SPACE_PRESSED);
        static const void JoueDeLaMusique();
        static const void ArreteCrieSurLaVoiePublique(std::thread& voice);
        static const void PlaceLaLumiereStatique();
        static const void PlaceLaLumiereQuiBouge(int angle);
};

#endif // INTERMITTENTDUSPECTACLE_H
