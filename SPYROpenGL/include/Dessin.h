/**
 * @file include/Dessin.h
 * @brief Contient les définition des méthodes de création des formes géométrique et sous-parties de Spyro
 * @author Loïs PAZOLA
 * @author Samuel LACHAUD
 * @version 3.2
 * @date 12/11/2021
 */

#ifndef DESSIN_H
#define DESSIN_H

#include "Point.h"

#include <tuple>

/**
 * @brief Classe de création des formes géométrique et sous-parties de Spyro
 */
class Dessin
{
	public:
		/**
		* @brief Méthode de création d'un cylindre
		* @param NM       Nombre de côtés de chaque base
		* @param rayon       Longueur du rayon
		* @param hauteur       Hauteur du cylindre
		* @param rotation       Rotation supplémentaire de "rotation*pi / NM" (optionnelle, défaut: 0)
		* @return un tuple de deux points correspondant à un coté du cylindre
		*/
		static const std::tuple<Point, Point> Cylindre(int NM, float rayon, float hauteur, float rotation = 0);
		/**
		* @brief Méthode de création de la liaison du corps au cou
		* @param NM    Nombre de côtés de chaque base
		* @param rayon     Longueur du rayon
		* @param hauteur     Hauteur de la liaison corps <--> cou
		* @param rotation       Rotation supplémentaire de "rotation*pi / NM" (optionnelle, défaut: 0)
		* @param coeff     Coefficient d'agrandissement de la base qui sera liée au cou par rapport à la base liée au corps
		*/
		static const void LiaisonCorpsCou(int NM, float rayon, float hauteur, float rotation = 0, float coeff = 1);
		/**
		* @brief Méthode de création d'une sphère
		* @param taille    Taille de la sphère
		* @param NP    Nombre de côtés à la verticale
		* @param NM    Nombre de côtés à l'horizontale
		* @param yeux    Applique une texture d'œil sur 2 faces symétriques
		*/
		static const void Sphere(float taille, int NP, int NM, bool yeux = false);
		/**
		* @brief Méthode de création d'un cône
		* @param hauteur    Hauteur du cône
		* @param rayon     Longueur du rayon
		* @param NM    Nombre de côtés (à l'horizontale)
		*/
		static const void Cone(float hauteur, float rayon, int NM);
		/**
		* @brief Méthode de création d'une crinière
		* @param rayonSphere    Longueur du rayon de la sphère utilisé pour créer la crinière
		*/
		static const void Criniere(float rayonSphere);
		/**
		* @brief Méthode de création d'un prisme (isocèle, rectangle)
		* @param longueurX     Longueur du prisme sur l'axe X
		* @param longueurZ     Longueur du prisme sur l'axe Z
		* @param hauteur       Hauteur du prisme
		* @param coeffX        Coefficient d'agrandissement de la surface haute du prisme par rapport à la surface basse sur l'axe X (optionnelle, défaut:  1)
		* @param coeffZ        Coefficient d'agrandissement de la surface haute du prisme par rapport à la surface basse sur l'axe Z (optionnelle, défaut:  1)
		* @param decalageSX    Décalage sur l'axe X du point de la surface haute se trouvant à l'angle droit (optionnelle, défaut: 0)
		* @param decalageSZ    Décalage sur l'axe Z du point de la surface haute se trouvant à l'angle droit (optionnelle, défaut: 0)
		*/
		static const void Prisme(float longueurX, float longueurZ, float hauteur, float coeffX = 1, float coeffZ = 1, float decalageSX = 0, float decalageSZ = 0);
		/**
		* @brief Méthode de création de la bouche
		* @param rayonCou     Rayon du cou
		* @param hauteur     Hauteur entre le cou et la bouche
		* @param coeffX        Coefficient d'agrandissement de la surface haute (correspondant à la bouche) par rapport à la surface basse (accrochée au cou) sur l'axe X (optionnelle, défaut: 1)
		* @param coeffZ        Coefficient d'agrandissement de la surface haute (correspondant à la bouche) par rapport à la surface basse (accrochée au cou) sur l'axe Z (optionnelle, défaut: 1)
		* @param decalageSZ    Décalage sur l'axe Z du point isocèle de la surface haute (correspondant à la bouche) (optionnelle, défaut: 0)
		* @param decalageSY    Décalage sur l'axe Y du point isocèle de la surface haute (correspondant à la bouche) (optionnelle, défaut: 0)
		*/
		static const void Bouche(float rayonCou, float hauteur, float coeffX = 1, float coeffZ = 1, float decalageSZ = 0, float decalageSY = 0);
		/**
		* @brief Méthode de création du nez
		* @param rayonVersBouche     Rayon pour aller aux deux points sur les côtés de la bouche
		* @param hauteur     Hauteur du nez
		* @param boucheCoeffX        Le coefficient d'agrandissement sur l'axe X qui A ETAIT utilisé pour la surface haute de la bouche
		* @param coeffBoucheZ        Le coefficient d'agrandissement sur l'axe Z qui A ETAIT utilisé pour la surface haute de la bouche
		* @param coeffIY       Coefficient d'agrandissement des deux points sur les côtés sur l'axe Y (optionnelle, défaut: 1)
		* @param decalageZ    Décalage sur l'axe Z des deux points isocèle (le point isocèle de chaque surface) (optionnelle, défaut: 0)
		*/
		static const void Nez(float rayonVersBouche, float hauteur, float boucheCoeffX, float coeffBoucheZ, float coeffIY = 1, float decalageZ = 0);
		/**
		* @brief Méthode de création de la première partie de la queue
		* @param longueurRayonCorps      Longueur du rayon du corps
		* @param deuxPointsBaseCorps     Tuple de deux points correspondant à un coté du corps
		* @param hauteur       Hauteur de la première partie de la queue
		* @param coeff        Coefficient d'agrandissement de la surface haute de la première partie de la queue par rapport à la surface basse sur les axes X et Z (optionnelle, défaut: 1)
		*/
		static const void PremierePartieQueue(float longueurRayonCorps, std::tuple<Point, Point> deuxPointsBaseCorps, float hauteur, float coeff);
		/**
		* @brief Méthode de création de la deuxième partie de la queue
		* @param longueurX     Longueur de la deuxième partie de la queue sur l'axe X
		* @param longueurZ     Longueur de la deuxième partie de la queue sur l'axe Z
		* @param hauteur       Hauteur de la deuxième partie de la queue
		* @param deuxPointsBaseCorps     Tuple de deux points correspondant à un coté du corps
		* @param coeffX        Coefficient d'agrandissement de la surface haute de la deuxième partie de la queue par rapport à la surface basse sur l'axe X (optionnelle, défaut: 1)
		* @param coeffZ        Coefficient d'agrandissement de la surface haute de la deuxième partie de la queue par rapport à la surface basse sur l'axe Z (optionnelle, défaut: 1)
		* @param decalageSX    Décalage sur l'axe X du point du sommet (optionnelle, défaut: 0)
		* @param decalageSZ    Décalage sur l'axe Z du point du sommet (optionnelle, défaut: 0)
		*/
		static const void DeuxiemePartieQueue(float longueurX, float longueurZ, float hauteur, std::tuple<Point, Point> deuxPointsBaseCorps, float coeffX = 1, float coeffZ = 1, float decalageSX = 0, float decalageSZ = 0);
		/**
		* @brief Méthode de création de la troisième partie de la queue
		* @param longueurX     Longueur du tétraèdre sur l'axe X
		* @param longueurZ     Longueur du tétraèdre sur l'axe Z
		* @param hauteur       Hauteur du tétraèdre
		* @param deuxPointsBaseCorps     Tuple de deux points correspondant à un coté du corps
		* @param decalageBX    Décalage sur l'axe X du point de la surface basse se trouvant à l'angle droit (optionnelle, défaut: 0)
		* @param decalageBZ    Décalage sur l'axe Z du point de la surface basse se trouvant à l'angle droit (optionnelle, défaut: 0)
		* @param decalageSX    Décalage sur l'axe X du point du sommet (optionnelle, défaut: 0)
		* @param decalageSZ    Décalage sur l'axe Z du point du sommet (optionnelle, défaut: 0)
		*/
		static const void TroisiemePartieQueue(float longueurX, float longueurZ, float hauteur, std::tuple<Point, Point> deuxPointsBaseCorps, float decalageBX = 0, float decalageBZ = 0, float decalageSX = 0, float decalageSZ = 0);
		/**
		* @brief Méthode de création des jambes
		* @param longueurX     Longueur des jambes sur l'axe X
		* @param longueurZ     Longueur des jambes sur l'axe Z
		* @param hauteur   Hauteur des jambes
		* @param sens      Sens des jambes
		* @param agrandissement    Agrandissement de la surface du haut
		* @param largeurDUnCoteDuCorps donne la largeur d'un coté du cylindre formant le corps
		*/
		static const void Jambes(float longueurX, float longueurZ, float hauteur, bool sens, float agrandissement, float largeurDUnCoteDuCorps);
		/**
		* @brief Méthode de création d'un cube
		* @param taille    Taille du cube
		*/
		static const void Cube(float taille);
		/**
		* @brief Méthode de création d'un tétraèdre (le sommet se trouve par défaut au milieu de l'hypoténuse)
		* @param longueurX     Longueur du tétraèdre sur l'axe X
		* @param longueurZ     Longueur du tétraèdre sur l'axe Z
		* @param hauteur       Hauteur du tétraèdre
		* @param decalageBX    Décalage sur l'axe X du point de la surface basse se trouvant à l'angle droit (optionnelle, défaut: 0)
		* @param decalageBZ    Décalage sur l'axe Z du point de la surface basse se trouvant à l'angle droit (optionnelle, défaut: 0)
		* @param decalageSX    Décalage sur l'axe X du point du sommet (optionnelle, défaut: 0)
		* @param decalageSZ    Décalage sur l'axe Z du point du sommet (optionnelle, défaut: 0)
		*/
		static const void Tetraedre(float longueurX, float longueurZ, float hauteur, float decalageBX = 0, float decalageBZ = 0, float decalageSX = 0, float decalageSZ = 0);
		/**
		* @brief Méthode de création d'une pyramide tronquée
		* @param hauteur     Hauteur du prisme tronquée
		* @param largeur     Largeur du prisme tronquée
		* @param longueur    Longueur du prisme tronquée
		* @param ecart     Longueur du décalage de deux points dans une direction opposée
		*/
		static const void PyramideTronquee(float hauteur, float largeur, float longueur, float ecart);
		/**
		* @brief Méthode de création d'une pyramide
		* @param largeur     Largeur de la pyramide
		* @param longueur     Longueur de la pyramide
		* @param hauteur     Hauteur de la pyramide
		* @param translationX    Longueur de la translation du point du sommet sur l'axe X
		* @param translationZ    Longueur de la translation du point du sommet sur l'axe Z
		*/
		static const void Pyramide(float largeur, float longueur, float hauteur, float translationX = 0, float translationZ = 0);
		/**
		* @brief Méthode de dessin du cou de Spyro
		* @param NM int nombre de subdivision du cou
		* @param rayon float rayon du cou
		* @param hauteur float hauteur du cou
		* @param decalage float Décalage en avant du cou
		*/
		static const void Cou(int NM, float rayon, float hauteur, float decalage);

		/**
		* @brief Méthode appelant la méthode glColor3f avec des valeurs aléatoires
		*/
		static const void RandomColor3f();
		/**
		* @brief Affiche les axes X Y Z avec des lignes R G B à l'origine par rapport aux transformations actuelles (translations, rotations, etc.)
		* @param translationX      Translation du dessin des axes sur l'axe X (optionnelle, défaut: 0)
		* @param translationY      Translation du dessin des axes sur l'axe Y (optionnelle, défaut: 0)
		* @param translationZ      Translation du dessin des axes sur l'axe Z (optionnelle, défaut: 0)
		*/
		static const void AxesActuels(float translationX = 0, float translationY = 0, float translationZ = 0);
};

#endif // DESSIN_H
