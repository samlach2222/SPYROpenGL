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

        static const int widthSkybox=1280;
        static const int heightSkybox=720;
        static const int widthOeil=32;
        static const int heightOeil=32;
        static const int widthCriniere=428;
        static const int heightCriniere=428;
};

#endif // TEXTURES_H

extern unsigned char textureSkybox[Textures::widthSkybox*Textures::heightSkybox*3];
extern unsigned char textureOeil[Textures::widthOeil*Textures::heightOeil*3];
extern unsigned char textureCriniere[Textures::widthCriniere*Textures::heightCriniere*3];
