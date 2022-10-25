#include "ArbreBin.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

ArbreBin *creerAB(bool b, bool estFeuille) {
    ArbreBin *ab = (ArbreBin *)malloc(sizeof(ArbreBin));
    if (!ab) { exit(1); }

    ab->b = b;
    ab->estFeuille = estFeuille;
    ab->gauche = NULL;
    ab->droite = NULL;

    return ab;
}


ArbreBin *cons_arbre(IntDecomposition *T) {
    if (!T) { return NULL; }
    if (T->taille == 1) { return creerAB(T->liste[0], true); }
    
    ArbreBin *ab = creerAB(0, false);

    IntDecomposition *t_g = partieGauche(T);
    IntDecomposition *t_d = partieDroite(T);

    ab->gauche = cons_arbre(t_g);
    ab->droite = cons_arbre(t_d);


    libereIntDecomp(t_g);
    libereIntDecomp(t_d);

    return ab;
}

void libereArbreBin(ArbreBin *ab) {
    if (ab) {
        libereArbreBin(ab->gauche);
        libereArbreBin(ab->droite);
        free(ab);
    }
}

void afficheAB(ArbreBin *ab, unsigned int level) {
    if (!ab) { return; }

    for (unsigned int i = 1; i < level; i++)
        printf(i == level - 1 ? "|———————" : "\t");
    if (!ab->estFeuille) { printf("%d\n", level); }
    else { printf("%s\n", (ab->estFeuille && ab->b) ? "True" : "False"); }
    afficheAB(ab->gauche, level + 1);
    afficheAB(ab->droite, level + 1);
}

void createDotFile(ArbreBin *ab, FILE* f) {
    fprintf(f, "graph {\n");
    fprintf(f, "%d -- ", ab->b);
}