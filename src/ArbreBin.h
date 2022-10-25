#ifndef __ARBRE_BIN_H__
#define __ARBRE_BIN_H__
#include "functions.h"

typedef struct ArbreBin {
    bool b;                     // boolean associé au noeud
    bool estFeuille;            // true si feuille false sinon
    struct ArbreBin *gauche;    // AB gauche
    struct ArbreBin *droite;    // AB droite
} ArbreBin;

ArbreBin *cons_arbre(IntDecomposition *T);
void libereArbreBin(ArbreBin *ab);

void afficheAB(ArbreBin *ab, unsigned int level);


#endif