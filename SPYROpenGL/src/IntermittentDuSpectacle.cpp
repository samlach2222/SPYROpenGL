#include "IntermittentDuSpectacle.h"
#include <time.h>
#include <cstdlib>
#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systemes */
#endif

/**
 * @brief Méthode permettant de jouer le son en arrière plan de l'application, la musique boucle sans répéter la même.
 */
const void IntermittentDuSpectacle::JoueDeLaMusique()
{
    #ifdef _WIN32 || _WIN64
    srand(time(NULL));
    int randNum = (rand() % 3) + 1;
    switch(randNum)
    {
        case 1 :
            PlaySound("Dark Hollow.wav", NULL, SND_FILENAME|SND_LOOP);
            break;
        case 2 :
            PlaySound("Enchanted Towers.wav", NULL, SND_FILENAME|SND_LOOP);
            break;
        case 3 :
            PlaySound("Sgt. Byrd's Theme.wav", NULL, SND_FILENAME|SND_LOOP);
            break;
    }
    #elif __linux__ || __unix || __unix__
    system("                                                            \
           cd Ressources/Audio ;                                        \
           bash -c '                                                    \
           while : ;                                                    \
                do while : ;                                            \
                    do RANDOM_VALUE=$(($RANDOM % 3)) ;                  \
                    if [[ \"$RANDOM_VALUE\" != \"$LAST_VALUE\" ]] ;     \
                        then LAST_VALUE=$RANDOM_VALUE ;                 \
                        break ;                                         \
                    fi ;                                                \
                done ;                                                  \
                case $RANDOM_VALUE in                                   \
                    0)                                                  \
                        aplay \"Dark Hollow.wav\" ;                     \
                        ;;                                              \
                    1)                                                  \
                        aplay \"Enchanted Towers.wav\" ;                \
                        ;;                                              \
                    2)                                                  \
                        aplay \"Sgt. Byrd'\"'\"'s Theme.wav\" ;         \
                        ;;                                              \
                esac ; LAST_VALUE=$RANDOM_VALUE ;                       \
           done ;'                                                      \
           ");
    #endif
}

/**
 * @brief Méthode permettant de jouer la voie de Spyro lors de l'appuis sur la touche associée
 */
const void IntermittentDuSpectacle::CrieSurLaVoiePublique(bool* SPACE_PRESSED)
{
    #ifdef _WIN32 || _WIN64
    PlaySound("SaluuutMoiCSpyro.wav", NULL, SND_FILENAME|SND_LOOP);
    #elif __linux__ || __unix || __unix__
    system("                                                            \
           cd Ressources/Audio ;                                        \
           bash -c '                                                    \
           aplay \"SaluuutMoiCSpyro.wav\" ;'                            \
           ");
    #endif
    *SPACE_PRESSED = false;

}

const void IntermittentDuSpectacle::PlaceLaLumiereStatique(int angle)
{
    // Activation des lumières

    // Déclaration de la GL_LIGHT0
    GLfloat light_position_0[] = {15.0, 5.0, 3.0, 1.0}; // position de la lumière
    GLfloat dif_0[] = {1.0, 1.0, 1.0, 1.0}; // diffusion de la lumière
    GLfloat amb_0[] = {1.0, 1.0, 1.0, 1.0}; // ambiance de la lumière
    GLfloat spec_0[] = {1.0, 1.0, 1.0, 1.0}; // Specular de la lumière
    // Déclaration de la GL_LIGHT
    GLfloat light_position_1[] = {5.0, -5.0, 0.0, 0.0};
    GLfloat dif_1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat amb_1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat spec_1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat dir_1[] = {-1, 1, 0}; // direction de la lumière

    glLightfv(GL_LIGHT0, GL_POSITION, light_position_0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb_0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif_0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec_0);


    glPushMatrix();
        glRotatef(angle, 0, 1, 0);

        glLightfv(GL_LIGHT1, GL_POSITION, light_position_1);
        glLightfv(GL_LIGHT1, GL_AMBIENT, amb_1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, dif_1);
        glLightfv(GL_LIGHT1, GL_SPECULAR, spec_1);
        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 60.0);
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir_1);
        glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);
    glPopMatrix();
}

