/**
 * @file src/Textures.cpp
 * @brief Implémentation de la classe gérant l'application des textures sur Spyro
 * @author Loïs PAZOLA
 * @version 1.0
 * @date 14/11/2021
 */

#include "Textures.h"

#include <thread>  //Nécessaire pour les textures
#include <jpeglib.h>
#include <jerror.h>

/**
 * @brief Méthode permettant de charger un fichier JPEG
 * @param *fichier  pointeur vers le nom du fichier
 * @param *texture  pointeur vers la texture
 */
const void Textures::LoadJpegImage(char *fichier, unsigned char* texture)
{
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *file;
    unsigned char *ligne;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    #ifdef __WIN32
    if (fopen_s(&file,fichier,"rb") != 0)
    {
        fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
        exit(1);
    }
    #elif __GNUC__
    if ((file = fopen(fichier,"rb")) == 0)
    {
        fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
        exit(1);
    }
    #endif
    jpeg_stdio_src(&cinfo, file);
    jpeg_read_header(&cinfo, TRUE);

    /*
    if ((cinfo.image_width!=256)||(cinfo.image_height!=256)) {
    fprintf(stdout,"Erreur : l'image doit etre de taille 256x256\n");
    exit(1);
    }
    */
    if (cinfo.jpeg_color_space==JCS_GRAYSCALE) {
        fprintf(stdout,"Erreur : l'image doit etre de type RGB\n");
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
