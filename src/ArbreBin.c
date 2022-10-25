#include "ArbreBin.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

ArbreBin *creerAB(bool b, bool estFeuille, int level) {
    ArbreBin *ab = (ArbreBin *)malloc(sizeof(ArbreBin));
    if (!ab) { exit(1); }

    ab->b = b;
    ab->estFeuille = estFeuille;
    ab->level = level;
    ab->gauche = NULL;
    ab->droite = NULL;

    return ab;
}


ArbreBin *cons_arbre(IntDecomposition *T) {
    if (!T) { return NULL; }
    if (T->taille == 1) { return creerAB(T->liste[0], true, 0); }
    
    ArbreBin *ab = creerAB(0, false, T->taille);

    IntDecomposition *t_g = partieGauche(T);
    IntDecomposition *t_d = partieDroite(T);

    ab->gauche = cons_arbre(t_g);
    ab->droite = cons_arbre(t_d);


    libereIntDecomp(t_g);
    libereIntDecomp(t_d);

    return ab;
}


//
// ArbreBin *cons_arbre_2(IntDecomposition *T) {
//     unsigned int h = log2(T->taille);
//     ArbreBin *ab = creerAB(0, false, 0);

//     for (unsigned int i = 0; i < h; i++) {
        
//     }


//     return ab;
// }
//


void libereArbreBin(ArbreBin *ab) {
    if (ab) {
        libereArbreBin(ab->gauche);
        libereArbreBin(ab->droite);
        free(ab);
    }
}

void afficheAB(ArbreBin *ab) {
    if (!ab) { return; }
    printf("noeud: %d\n", ab->level);
    if (ab->estFeuille) {
        printf("feuille: %s\n", ab->b ? "True":"False");
    }
    afficheAB(ab->gauche);
    afficheAB(ab->droite);
}

void createDotFile(ArbreBin *ab, char *filename) {
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%s.dot", filename);

    FILE* f = fopen(buffer, "w+");

    fprintf(f, "digraph {\n");
    ArbreBin* ag = ab->gauche;
    // ArbreBin* ad = ab->droite;

    while (!ag->estFeuille) {
        fprintf(f, "%d -> %d [style=dashed]\n", ag->b, ag->gauche->b);
        ag = ag->gauche;
    }
    fprintf(f, "}");
    
    fclose(f);
    snprintf(buffer, sizeof(buffer), "dot -Tsvg %s.dot > %s.html", filename, filename);
    system(buffer);
    snprintf(buffer, sizeof(buffer), "open %s.html", filename);
    system(buffer);
}

void luka(ArbreBin *ab) {
    if (!ab) { return; }
    printf("(");
    luka(ab->gauche);
    luka(ab->droite);
    printf(")");
}