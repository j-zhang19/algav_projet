#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
#include <stdbool.h>

typedef struct decomp {
    unsigned int taille; // taille de la liste
    bool *liste;         // liste de boolean
} IntDecomposition;

void libereIntDecomp(IntDecomposition *d);
void afficheListeDecomp(IntDecomposition *d);

// ---
IntDecomposition *decomposition(unsigned int x);
IntDecomposition *completion(IntDecomposition *d, unsigned int n);
IntDecomposition *table(unsigned int x, unsigned int n);

IntDecomposition *partieGauche(IntDecomposition *d);
IntDecomposition *partieDroite(IntDecomposition *d);



#endif