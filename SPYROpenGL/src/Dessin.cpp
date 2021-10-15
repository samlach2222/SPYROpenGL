#include "Dessin.h"

#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systemes */
#endif
#include "math.h"

const void Dessin::Cylindre(int NM, float rayon, float hauteur){

    float x[NM*2]; // NM --> taille du nombre de subdivison d'une base * 2 (base du bas + base du haut)
    float y[NM*2];
    float z[NM*2];

    // Remplissage des coordonnées des points dans x et y et z;
    for(int i = 0; i < NM*2; i++)
    {
        x[i] = rayon*cos(2*i*M_PI/NM);
        z[i] = rayon*sin(2*i*M_PI/NM);

        if (i < NM){  //Base du bas
            y[i] = 0;
        }
        else{  //Base du haut
            y[i] = hauteur;
        }
    }

    //Dessin de la base bas
    glBegin(GL_POLYGON);
    for(int i = 0; i < NM; i++)
    {
        RandomColor3f();
        glVertex3f(x[i], y[i], z[i]);
    }
    glEnd();

    //Dessin de la base haut
    glBegin(GL_POLYGON);
    for(int i = NM; i < NM*2; i++)
    {
        RandomColor3f();
        glVertex3f(x[i], y[i], z[i]);
    }
    glEnd();

    //Dessin des faces sur les côtés
    for (int i = 0; i < NM; i++){
        glBegin(GL_POLYGON);
			Dessin::RandomColor3f();
			glVertex3f(x[i], y[i], z[i]);
			glVertex3f(x[(i+1)%NM], y[(i+1)%NM], z[(i+1)%NM]);
			glVertex3f(x[((i+1)%NM)+NM], y[((i+1)%NM)+NM], z[((i+1)%NM)+NM]);
			glVertex3f(x[i+NM], y[i+NM], z[i+NM]);
        glEnd();
    }
}

const void Dessin::RandomColor3f(){
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);  //Donne une valeur entre 0.0 et 1.0 inclus
    float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    glColor3f(r,g,b);
}
