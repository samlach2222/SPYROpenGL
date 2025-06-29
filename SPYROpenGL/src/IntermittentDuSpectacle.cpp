/**
 * @file src/IntermittentDuSpectacle.cpp
 * @brief Implémentation de la classe gérant les sons et lumières du projet
 * @author Loïs PAZOLA
 * @author Samuel LACHAUD
 * @version 1.3
 * @date 16/06/2024
 */

#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systèmes */
#endif

#ifdef _WIN32
#include <MMSystem.h>
#endif

#include "IntermittentDuSpectacle.h"

#include <thread>

// Visual Studio affiche un warning car il ne reconnait pas le pragma GCC
#if defined(__GNUC__) && !defined(__clang__)
// Désactive les warnings causés par l'absence d'utilisation de la valeur retournée par system()
// Seulement appliqué sur le fichier
#pragma GCC diagnostic ignored "-Wunused-result"
#endif

const void IntermittentDuSpectacle::JoueDeLaMusique()
{
	#ifdef _WIN32
	// Note : Puisqu'il est impossible de commenter à l'intérieur de la commande ci-dessous, tous les commentaires se trouvent ici
	// - title n'est pas nécessaire mais est utile pour l'utilisateur. Récupérer le processus par nom de fenêtre serait trop
	//   risqué car sur Windows Terminal il s'agit uniquement de l'onglet actif
	// - SPYROpenGL_Music_Command est très important : c'est ce qui permet de détecter le processus en regardant sa
	//   CommandLine et ainsi de le fermer à la fermeture de SPYROpenGL, sinon la musique continue de jouer en arrière plan
	// - <#SPYROpenGL_Music_Command#> enveloppe SPYROpenGL_Music_Command dans un commentaire
	// - [System.Console]::TreatControlCAsInput sert à ne pas quitter le script si l'utilisateur appuie sur CTRL-C
	// - RANDOM_VALUE -eq $LAST_VALUE ne fonctionne pas car il n'est pas possible de comparer 2 arrays, on compare donc une
	//   valeur à l'intérieur. @() permet d'éviter une erreur (impossible à cacher) d'index dans null en forçant un array vide
	// - Transmettre les arrays à Get-Random avec | ne fonctionne pas, il faut utiliser -InputObject pour retourner un array
	// - """ = " dans une commande CMD
	// - Start-Job ne conserve pas le working directory, le chemin complet est donc intégré dans les valeurs du Get-Random
	// - System.Media.SoundPlayer PlaySync() est bloquant même avec Ctrl-C ou en stoppant $JOB, mais avec Play() il est impossible
	//   de savoir quand la musique est terminée. Play() est donc combinée avec Start-Sleep pour attendre la durée de la musique
	// - Il ne semble pas possible de mettre la valeur d'une variable dans un ScriptBlock de Start-Job, ils doivent être passés en
	//   paramètres. De plus le ScriptBlock considère que deux valeurs séparées ont été envoyées au lieu de l'array lui-même
	// - if ($Host.UI.RawUI.KeyAvailable -and (3 -eq [int]$Host.UI.RawUI.ReadKey('AllowCtrlC, IncludeKeyUp, NoEcho').Character))
	//   détecte Ctrl-C de façon non bloquante pour également sortir du while lorsque $JOB fini (fin de la musique)
	system("                                                                \
		cd Ressources\\Audio                                                \
		& title SPYROpenGL Musique                                          \
		& echo Ctrl-C : Changer de musique                                  \
		& powershell.exe -NoProfile -NonInteractive                         \
		-ExecutionPolicy Bypass -Command \"& {                              \
			<#SPYROpenGL_Music_Command#>                                    \
			[System.Console]::TreatControlCAsInput = $true;                 \
			while ($true) {                                                 \
				while (@($RANDOM_VALUE)[1] -eq @($LAST_VALUE)[1]) {         \
					$RANDOM_VALUE = Get-Random -InputObject                 \
						(\"\"\"$PWD\\Dark Hollow.wav\"\"\", 330),           \
						(\"\"\"$PWD\\Enchanted Towers.wav\"\"\", 345),      \
						(\"\"\"$PWD\\Sgt. Byrd's Theme.wav\"\"\", 314.6)    \
				}                                                           \
				$LAST_VALUE = $RANDOM_VALUE;                                \
				Write-Output ('Lecture ''' +                                \
					$RANDOM_VALUE[0].Split('\\')[-1] + '''');               \
				$JOB = Start-Job -ArgumentList $RANDOM_VALUE -ScriptBlock { \
					param($PATH,$DURATION)                                  \
					(New-Object System.Media.SoundPlayer $PATH).Play();     \
					Start-Sleep -Seconds $DURATION                          \
				};                                                          \
				while ($JOB.State -eq 'Running') {                          \
					if ($Host.UI.RawUI.KeyAvailable -and (                  \
							3 -eq [int]$Host.UI.RawUI.ReadKey(              \
								'AllowCtrlC, IncludeKeyUp, NoEcho'          \
					).Character)) {                                         \
						Remove-Job -Force -Job $JOB                         \
					}                                                       \
				}                                                           \
			}                                                               \
		}\"                                                                 \
	");
	#elif __linux__ || __unix || __unix__
	// Note : Puisqu'il est impossible de commenter à l'intérieur de la commande ci-dessous, tous les commentaires se trouvent ici
	// - SPYROpenGL_Music_Command est très important : c'est ce qui permet de détecter les processus en regardant
	//   leur commande et ainsi de les fermer à la fermeture de SPYROpenGL, sinon la musique continue de jouer en arrière plan
	// - SPYROpenGL_Music_Command= sert uniquement à avoir le texte SPYROpenGL_Music_Command dans le script, la commande elle-même
	//   affecte une valeur vide à SPYROpenGL_Music_Command. Techniquement tout ce script se trouve sur une seule ligne et bash
	//   supporte uniquement les commentaires # en fin de ligne
	// - Si bash est kill, le processus exécutant system() finira ensuite sa commande normalement
	// - $(()) est une expansion arithmétique, différent de $()
	// - $RANDOM n'est disponible qu'en bash. Alternative : $(od -vAn -N1 -tu1 < /dev/urandom)
	// - '\\'' est transformé en un ' (le backslash est échappé du string system())
	system("                                                            \
		cd Ressources/Audio ;                                           \
		bash -c '                                                       \
			SPYROpenGL_Music_Command= ;                                 \
			while true ; do                                             \
				while [ \"$RANDOM_VALUE\" = \"$LAST_VALUE\" ] ; do      \
					RANDOM_VALUE=$(($RANDOM % 3)) ;                     \
				done ;                                                  \
				LAST_VALUE=$RANDOM_VALUE ;                              \
				case $RANDOM_VALUE in                                   \
					0)                                                  \
						aplay \"Dark Hollow.wav\" ;                     \
						;;                                              \
					1)                                                  \
						aplay \"Enchanted Towers.wav\" ;                \
						;;                                              \
					2)                                                  \
						aplay \"Sgt. Byrd'\\''s Theme.wav\" ;           \
						;;                                              \
				esac ;                                                  \
			done                                                        \
		'                                                               \
	");
	#endif
}

const void IntermittentDuSpectacle::ArreteCrieSurLaVoiePublique(std::thread& voice)
{
	if (voice.joinable()) {
		voice.join(); // Attend que le son est fini avant de fermer le thread
		voice.~thread();
	}
}

const void IntermittentDuSpectacle::ArreteJoueDeLaMusique(std::thread& bgMusic)
{
	#ifdef _WIN32
	// Where-Object .CommandLine prend beaucoup de temps. Un premier tri rapide est fait sur le Name
	system("                                                            \
		powershell.exe -NoProfile -NonInteractive                       \
		-ExecutionPolicy Bypass -Command \"& {                          \
			Get-Process -Name powershell | Where-Object {               \
				(Get-CimInstance Win32_Process -Filter                  \
					('ProcessId = ' + $_.Id)                            \
				).CommandLine -like '*SPYROpenGL_Music_Command*'        \
			} | Stop-Process -Force                                     \
		}\"                                                             \
	");
	#elif __linux__ || __unix || __unix__
	// Récupère dans une variable le PID du aplay de la musique de fond, sans toucher à des aplay extérieur à SPYROpenGL. Pour
	// cela on récupère les PID des processus dont leur parent (parent direct uniquement, pas récursif) est le processus le plus
	// récent dont la commande contient SPYROpenGL_Music_Command (écrit comme 'SPYROpenGL'_Music_Command pour ne pas détecter le
	// processus exécutant le system())
	// Ensuite tous les processus dont la commande contient SPYROpenGL_Music_Command sont kill
	// Enfin le processus aplay de la musique de fond est kill
	system("                                                            \
		PID_APLAY=$(pgrep --parent $(pgrep --full --newest              \
		'SPYROpenGL'_Music_Command)) ;                                  \
		pkill --full 'SPYROpenGL'_Music_Command ;                       \
		kill $PID_APLAY                                                 \
	");
	#endif
	if (bgMusic.joinable()) {
		bgMusic.join();
		bgMusic.~thread();
	}
}

const void IntermittentDuSpectacle::CrieSurLaVoiePublique(bool* SPACE_PRESSED)
{
	#ifdef _WIN32
	PlaySound(TEXT("Ressources/Audio/SaluuutMoiCSpyro.wav"), FALSE, SND_FILENAME);
	#elif __linux__ || __unix || __unix__
	system("aplay 'Ressources/Audio/SaluuutMoiCSpyro.wav'");
	#endif

	*SPACE_PRESSED = false;

}

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
