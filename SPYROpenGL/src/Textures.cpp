/**
 * @file src/Textures.cpp
 * @brief Implémentation de la classe gérant l'application des textures sur Spyro
 * @author Loïs PAZOLA
 * @version 1.1
 * @date 04/10/2022
 */

#include "Textures.h"

#include <thread>  //Nécessaire pour les textures
#include <jpeglib.h>
#include <jerror.h>
#include <cstring>

/**
 * @brief Méthode permettant de charger un fichier JPEG
 * @param *fichier  pointeur vers le nom du fichier
 * @param *texture  pointeur vers la texture
 */
const void Textures::LoadJpegImage(char *fichier, unsigned char* texture)
{
    struct jpeg_decompress_struct cinfo{};
    struct jpeg_error_mgr jerr{};
    unsigned char *ligne;
    FILE *file;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    #ifdef _WIN32
    if (fopen_s(&file,fichier,"rb") != 0)
    {
        //variable du message d'erreur avec nom de fichier
        char message[100] = "Impossible d'ouvrir le fichier ";
        strcat_s(message, fichier);
        printf("%s", message);
    }
    #elif __GNUC__
    if ((file = fopen(fichier,"rb")) == 0)
    {
        //variable du message d'erreur avec nom de fichier
        char message[strlen(fichier)+66];
        strcpy(message, "Erreur : impossible d'ouvrir le fichier ");
        strcat(message, fichier);
        strcat(message, "\n");

        fprintf(stderr,message);
        exit(1);
    }
    #endif
    jpeg_stdio_src(&cinfo, file);
    jpeg_read_header(&cinfo, TRUE);

    if (cinfo.jpeg_color_space==JCS_GRAYSCALE) {
        fwprintf(stdout,L"Erreur : l'image doit etre de type RGB\n");
        exit(1);
    }

    jpeg_start_decompress(&cinfo);
    ligne=texture;
    while (cinfo.output_scanline<cinfo.output_height)
    {
        ligne=texture+3*cinfo.output_width*cinfo.output_scanline;
        jpeg_read_scanlines(&cinfo,&ligne,1);
    }
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
}
