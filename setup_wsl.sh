cd "$(dirname "$0")"
echo "Installation des divers packages nécessaires"
sudo apt update
sudo apt install alsa-utils freeglut3-dev libasound2-plugins libjpeg-turbo8-dev
echo # Nouvelle ligne

echo "Lie les connexions ALSA vers PulseAudio"
if [ -f ~/.asoundrc ]
then
	# Le fichier existe déjà, il est plus prudent de le modifier manuellement
	echo "Veuillez ajouter les deux lignes suivantes dans ~/.asoundrc :"
	echo "pcm.default pulse"
	echo "ctl.default pulse"
	echo -e "pcm.default pulse\nctl.default pulse" | clip.exe
	echo "Lignes copiés dans le presse-papiers"
	read -p "Exécuter nano ~/.asoundrc ? [Y/y/O/o pour oui] : " -n1 executerNano
	echo
	if [[ $executerNano =~ ^[YyOo]$ ]]
	then
		nano ~/.asoundrc
	fi
else
    echo "pcm.default pulse" > ~/.asoundrc
    echo "ctl.default pulse" >> ~/.asoundrc
fi
echo

if ! command -v codeblocks >/dev/null 2>&1
then
	read -p "Voulez-vous installer Code::Blocks ? Un fichier de projet est disponible [Y/y/O/o pour oui] : " -n1 installerCodeBlocks
	echo
	if [[ $installerCodeBlocks =~ ^[YyOo]$ ]]
	then
		sudo apt install codeblocks
		echo "Le fichier du projet se trouve à SPYROpenGL/SPYROpenGL.cbp"
	fi
else
	echo "CodeBlocks déjà installé"
fi
echo

if command -v codeblocks >/dev/null 2>&1
then
	read -p "Voulez-vous ouvrir le projet dans Code::Blocks ? [Y/y/O/o pour oui] : " -n1 executerCodeBlocks
	echo
	echo
fi

# Affiche le message de setup terminé avant d'ouvrir CodeBlocks
echo "Setup terminé !"

if [[ $executerCodeBlocks =~ ^[YyOo]$ ]]
then
	echo
	codeblocks SPYROpenGL/SPYROpenGL.cbp
fi
