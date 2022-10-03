#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systèmes */
#endif

#include "IntermittentDuSpectacle.h"

#include <cstdlib>
#ifdef _WIN32
#include <MMSystem.h>
#endif

/**
 * @brief Méthode permettant de jouer le son en arrière plan de l'application, la musique boucle sans répéter la même.
 */
const void IntermittentDuSpectacle::JoueDeLaMusique()
{
    #ifdef _WIN32
    // Il ne semble pas être possible d'intercepter CTRL-C sur Windows
    // Le ^ pour ^| est nécessaire car | doit être échappé du CMD
    system("                                                                \
        cd Ressources\\Audio &                                              \
        powershell -c                                                       \
            FOR () {                                                        \
                while ($RANDOM_VALUE -eq $LAST_VALUE) {                     \
                    $RANDOM_VALUE =                                         \
                        'Dark Hollow.wav',                                  \
                        'Enchanted Towers.wav',                             \
                        'Sgt. Byrd''s Theme.wav'                            \
                        ^| get-random                                       \
                };                                                          \
                echo $RANDOM_VALUE;                                         \
                $LAST_VALUE = $RANDOM_VALUE;                                \
                (New-Object Media.SoundPlayer $RANDOM_VALUE).PlaySync();    \
            }                                                               \
    ");
    #elif __linux__ || __unix || __unix__
    system("                                                        \
        cd Ressources/Audio ;                                       \
        bash -c '                                                   \
        while : ;                                                   \
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
                    aplay \"Sgt. Byrd's Theme.wav\" ;               \
                    ;;                                              \
            esac ; LAST_VALUE=$RANDOM_VALUE ;                       \
        done ;'                                                     \
    ");
    #endif
}

/**
 * @brief Méthode permettant de jouer la voix de Spyro lors de l'appui sur la touche associée
 * @param SPACE_PRESSED indique si la barre espace à été appuyée (true pour oui, false pour non)
 */
const void IntermittentDuSpectacle::CrieSurLaVoiePublique(bool* SPACE_PRESSED)
{
    #ifdef _WIN32
    PlaySound(TEXT("Ressources/Audio/SaluuutMoiCSpyro.wav"), FALSE, SND_FILENAME);
    #elif __linux__ || __unix || __unix__
    system("                                                            \
           cd Ressources/Audio ;                                        \
           bash -c '                                                    \
           aplay \"SaluuutMoiCSpyro.wav\" ;'                            \
           ");
    #endif

    *SPACE_PRESSED = false;

}

/**
 * @brief Méthode permettant d'appliquer la lumière statique
 */
const void IntermittentDuSpectacle::PlaceLaLumiereStatique()
{
    // Déclaration de la GL_LIGHT0
    GLfloat light_position_0[] = {15.0, 5.0, 3.0, 1.0}; // position de la lumière
    GLfloat dif_0[] = {1.0, 1.0, 1.0, 1.0}; // diffusion de la lumière
    GLfloat amb_0[] = {1.0, 1.0, 1.0, 1.0}; // ambiance de la lumière
    GLfloat spec_0[] = {1.0, 1.0, 1.0, 1.0}; // Specular de la lumière

    glLightfv(GL_LIGHT0, GL_POSITION, light_position_0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb_0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif_0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec_0);
}

/**
 * @brief Méthode permettant d'appliquer la lumière en rotation autour de Spyro
 * @param angle de rotation de la lumière
 */
const void IntermittentDuSpectacle::PlaceLaLumiereQuiBouge(int angle)
{
    // Déclaration de la GL_LIGHT1
    GLfloat light_position_1[] = {4.0, -4.0, 0.0, 0.0};
    GLfloat dif_1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat amb_1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat spec_1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat dir_1[] = {-1, 1, 0}; // direction de la lumière

    glPushMatrix();
        glRotatef((float) angle, 0, 1, 0);

        glLightfv(GL_LIGHT1, GL_POSITION, light_position_1);
        glLightfv(GL_LIGHT1, GL_AMBIENT, amb_1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, dif_1);
        glLightfv(GL_LIGHT1, GL_SPECULAR, spec_1);
        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 60.0);
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir_1);
        glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);
    glPopMatrix();
}
