#ifndef DESSIN_H
#define DESSIN_H


class Dessin
{
    public:
        static const void Cylindre(int NM, float rayon, float hauteur);
        static const void RandomColor3f();
        static const void Sphere(float taille, int NP, int NM);
        static const void Cone(float hauteur, float rayon, int NM);
        static const void Criniere(float rayonSphere);
        static const void Prisme(float longueurX, float longueurZ, float hauteur, float coeffX = 1, float coeffZ = 1, float decalageSX = 0, float decalageSZ = 0);
        static const void Jambes(float longueurX, float longueurZ, float hauteur, bool sens);
        static const void Cube(float taille);
        static const void Tetraedre(float longueurX, float longueurZ, float hauteur, float decalageBX = 0, float decalageBZ = 0, float decalageSX = 0, float decalageSZ = 0);
        static const void PyramideTronquee(float hauteur, float largeur, float longueur, float ecart);
};

#endif // DESSIN_H