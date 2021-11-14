/**
 * @file include/Textures.h
 * @brief Contient la définition de la classe gérant l'application des textures
 * @author Loïs PAZOLA
 * @version 1.0
 * @date 14/11/2021
 */

#ifndef TEXTURES_H
#define TEXTURES_H

/**
 * @brief Classe permettant l'application des textures
 */
class Textures
{
    public:
        static const void LoadJpegImage(char *fichier, unsigned char* texture);
};

#endif // TEXTURES_H
