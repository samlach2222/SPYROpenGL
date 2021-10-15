#ifndef CREATION_H
#define CREATION_H


class Creation
{
    public:
        static const void Jambes(float taille, float hauteur, bool sens);
        static const void Pieds(float taille);
        static const void JambesPlusPieds(float taille, float hauteurJambes);
        static const void ComposantsTete(float taille, float hauteurCorne, float largeurCorne);
        static const void Queue(float taille = 1);
};

#endif // CREATION_H
