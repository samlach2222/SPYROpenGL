#include "IntermittentDuSpectacle.h"
#include <time.h>
#include <cstdlib>


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
const void IntermittentDuSpectacle::CrieSurLaVoiePublique()
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
}


