#include "ArbreBin.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

ArbreBin *creerAB(int b, bool estFeuille, unsigned int h) {
    ArbreBin *ab = (ArbreBin *)malloc(sizeof(ArbreBin));
    if (!ab) { exit(1); }

    ab->b = b;
    ab->estFeuille = estFeuille;
    ab->h = h;
    ab->gauche = NULL;
    ab->droite = NULL;

    return ab;
}

ArbreBin *cons_arbre_b(IntDecomposition *T, unsigned int h) {
    if (!T) { return NULL; }
    if (T->taille == 1) { return creerAB(T->liste[0], true, 0); }
    
    ArbreBin *ab = creerAB(-1, false, h);

    IntDecomposition *t_g = partieGauche(T);
    IntDecomposition *t_d = partieDroite(T);

    ab->gauche = cons_arbre_b(t_g, h-1);
    ab->droite = cons_arbre_b(t_d, h-1);

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
    printf("noeud: %d\n", ab->h);
    if (ab->estFeuille) {
        printf("feuille: %s\n", ab->b ? "True":"False");
    }
    afficheAB(ab->gauche);
    afficheAB(ab->droite);
}

void createNodes(ArbreBin *ab, FILE* f, unsigned int id) {
    if (!ab) { return; }
    
    if (ab->estFeuille)
        fprintf(f, "%d [label=\"%s\"]\n", id, ab->b ? "True":"False");
    else
        fprintf(f, "%d [label=\"x%d\"]\n", id, ab->h);

    createNodes(ab->gauche, f, id-1);
    createNodes(ab->droite, f, (3*id)-2);

    if (!ab->estFeuille) {
        fprintf(f, "%d -> %d [style=dashed]\n", id, id-1);
        fprintf(f, "%d -> %d\n", id, (3*id)-2);
    }
}

void createDotFile(ArbreBin *ab, char *filename) {
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%s.dot", filename);

    FILE* f = fopen(buffer, "w+");

    fprintf(f, "digraph BST {\n");        

    createNodes(ab, f, (int)pow(2, ab->h));

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

ArbreBin *compression(ArbreBin *ab) {
    if (!ab) { return NULL; }
    
    

    return NULL;
}