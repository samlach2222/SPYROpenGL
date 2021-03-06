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

        /**
         * @brief Largeur de l'image de la skybox
         */
        static const int widthSkybox=1280;
        /**
         * @brief Hauteur de l'image de la skybox
         */
        static const int heightSkybox=720;
        /**
         * @brief Largeur de l'image d'un œil (identique pour chaque)
         */
        static const int widthOeil=32;
        /**
         * @brief Hauteur de l'image d'un œil (identique pour chaque)
         */
        static const int heightOeil=32;
        /**
         * @brief Largeur de l'image de la crinière
         */
        static const int widthCriniere=428;
        /**
         * @brief Hauteur de l'image de la crinière
         */
        static const int heightCriniere=428;
};

#endif // TEXTURES_H

/**
 * @brief Variable stockant la texture de la skybox
 */
extern unsigned char textureSkybox[Textures::widthSkybox*Textures::heightSkybox*3];
/**
 * @brief Variable stockant la texture d'un œil (identique pour chaque)
 */
extern unsigned char textureOeil[Textures::widthOeil*Textures::heightOeil*3];
/**
 * @brief Variable stockant la texture de la crinière
 */
extern unsigned char textureCriniere[Textures::widthCriniere*Textures::heightCriniere*3];
