#ifndef __ARBRE_BIN_H__
#define __ARBRE_BIN_H__
#include "functions.h"
#include <stdio.h>

typedef struct Leaf {
    bool b;
} Leaf;

typedef struct ArbreBin {
    int b;                      // boolean associé au noeud; -1 si pas une feuille
    bool estFeuille;            // true si feuille false sinon
    unsigned int h;             // hauteur du noeud dans l'arbre
    struct ArbreBin *gauche;    // AB gauche
    struct ArbreBin *droite;    // AB droite
} ArbreBin;

ArbreBin *creerAB(int b, bool estFeuille, unsigned int v);

ArbreBin *cons_arbre_b(IntDecomposition *T, unsigned int h);
ArbreBin *cons_arbre(IntDecomposition *T);
void libereArbreBin(ArbreBin *ab);

void afficheAB(ArbreBin *ab);

void createDotFile(ArbreBin *ab, char *filename);

void luka(ArbreBin *ab);

#endif