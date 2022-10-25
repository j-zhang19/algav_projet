#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


void afficheListeDecomp(IntDecomposition *d) {
    printf("taille: %d \n| ", d->taille);
    for (unsigned int i = 0; i < d->taille; i++) {
        printf("%s ", d->liste[i] ? "T |" : "F |");
    }
    printf("\n");
}

IntDecomposition *decomposition(unsigned int x) {
    IntDecomposition *d = (IntDecomposition *)malloc(sizeof(IntDecomposition));
    if (!d) { exit(1); }

    d->taille = (int)floor(log2(x)) + 1;
    d->liste = (bool *)malloc(d->taille * sizeof(bool));

    if (!(d->liste)) { exit(1); }

    for (unsigned int i = 0; i < d->taille; i++) {
        d->liste[i] = (x >> i) & 1;
    }

    return d;
}

void libereIntDecomp(IntDecomposition *d) {
    if (d) {
        if (d->liste) {
            free(d->liste);
        }
        free(d);
    }
}

IntDecomposition *completion(IntDecomposition *d, unsigned int n) {
    if (!d || d->taille == n) { return d; }

    // ajout de cases
    if (d->taille < n) {
        d->liste = (bool *)realloc(d->liste, n * sizeof(bool));
        
        for (unsigned int i = d->taille; i < n; i++) {
            d->liste[i] = false;
        }

        d->taille = n;
        return d;
    }

    // suppression de cases = nouvelle struct
    IntDecomposition *dp = (IntDecomposition *)malloc(sizeof(IntDecomposition));
    if (!dp) { exit(1); }
    dp->liste = (bool *)malloc(n * sizeof(bool));
    dp->taille = n;

    for (unsigned int i = 0; i < n; i++) {
        dp->liste[i] = d->liste[i];
    }

    libereIntDecomp(d);
    return dp;
}

IntDecomposition *table(unsigned int x, unsigned int n) {
    IntDecomposition *T = decomposition(x);
    T = completion(T, n);

    return T;
}

IntDecomposition *partieGauche(IntDecomposition *d) {
    if (!d) { exit(1); }
    // si impossible de couper en 2 parties égales
    if (d->taille <= 1) { return d; }
    
    IntDecomposition *dg = (IntDecomposition *)malloc(sizeof(IntDecomposition));
    if (!dg) { exit(1); }
    
    dg->taille = d->taille / 2;
    dg->liste = (bool *)malloc(dg->taille * sizeof(bool));
    
    for (unsigned int i = 0; i < dg->taille; i++) {
        dg->liste[i] = d->liste[i];
    }

    return dg;
}

IntDecomposition *partieDroite(IntDecomposition *d) {
    if (!d) { exit(1); }
    // si impossible de couper en 2 parties égales
    if (d->taille <= 1) { return d; }
    
    IntDecomposition *dd = (IntDecomposition *)malloc(sizeof(IntDecomposition));
    if (!dd) { exit(1); }
    
    dd->taille = d->taille / 2;
    dd->liste = (bool *)malloc(dd->taille * sizeof(bool));
    
    for (unsigned int i = 0; i < dd->taille; i++) {
        dd->liste[i] = d->liste[i + dd->taille];
    }

    return dd;
}