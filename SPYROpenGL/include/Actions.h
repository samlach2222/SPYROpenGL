#ifndef ACTIONS_H
#define ACTIONS_H

#include "Point.h"

class Actions
{
    public:
        Actions();
        virtual ~Actions();

    private:
        char presse;
        int anglex;
        int angley;
        int x;
        int y;
        int xold;
        int yold;

        /* Prototype des fonctions */;
        void clavier(unsigned char touche,int x,int y);
        void reshape(int x,int y);
        void idle();
        void mouse(int bouton,int etat,int x,int y);
        void mousemotion(int x,int y);
};

#endif // ACTIONS_H
