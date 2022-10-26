#include "ArbreBin.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

ArbreBin *creerAB(bool b, bool estFeuille, unsigned int id) {
    ArbreBin *ab = (ArbreBin *)malloc(sizeof(ArbreBin));
    if (!ab) { exit(1); }

    ab->b = b;
    ab->estFeuille = estFeuille;
    ab->id = id;
    ab->gauche = NULL;
    ab->droite = NULL;

    return ab;
}

ArbreBin *cons_arbre_b(IntDecomposition *T, unsigned int i) {
    if (!T) { return NULL; }
    if (T->taille == 1) { return creerAB(T->liste[0], true, 0); }
    
    ArbreBin *ab = creerAB(0, false, i);

    IntDecomposition *t_g = partieGauche(T);
    IntDecomposition *t_d = partieDroite(T);

    ab->gauche = cons_arbre_b(t_g, i-1);
    ab->droite = cons_arbre_b(t_d, i-1);

    libereIntDecomp(t_g);
    libereIntDecomp(t_d);

    return ab;
}

ArbreBin *cons_arbre(IntDecomposition *T) {
    return cons_arbre_b(T, (int)floor(log2(T->taille)));
}

void libereArbreBin(ArbreBin *ab) {
    if (ab) {
        libereArbreBin(ab->gauche);
        libereArbreBin(ab->droite);
        free(ab);
    }
}

void afficheAB(ArbreBin *ab) {
    if (!ab) { return; }
    printf("noeud: %d\n", ab->id);
    if (ab->estFeuille) {
        printf("feuille: %s\n", ab->b ? "True":"False");
    }
    afficheAB(ab->gauche);
    afficheAB(ab->droite);
}

void createNodes(ArbreBin *ab, FILE* f, unsigned int i) {
    if (!ab) { return; }
    fprintf(f, "%d%d [label=\"x%d\"];\n", ab->id, i, ab->id);

    if (!ab->estFeuille) {
        createNodes(ab->gauche, f, i);
        fprintf(f, "%d%d -> %d%d [style=dashed]\n", ab->id, i, ab->gauche->id, i);
        createNodes(ab->droite, f, i+1*2);
        fprintf(f, "%d%d -> %d%d \n", ab->id,i, ab->droite->id, i+1*2);
    }
}

void createDotFile(ArbreBin *ab, char *filename) {
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%s.dot", filename);

    FILE* f = fopen(buffer, "w+");

    fprintf(f, "digraph {\n");

    createNodes(ab, f, 0);

    fprintf(f, "}");
    
    fclose(f);
    snprintf(buffer, sizeof(buffer), "dot -Tsvg %s.dot > %s.html", filename, filename);
    system(buffer);
    // snprintf(buffer, sizeof(buffer), "open %s.html", filename);
    // system(buffer);
}

void luka(ArbreBin *ab) {
    if (!ab) { return; }
    printf("(");
    luka(ab->gauche);
    luka(ab->droite);
    printf(")");
}