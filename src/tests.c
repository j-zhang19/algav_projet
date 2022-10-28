#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"
#include "ArbreBin.h"


int main(int argc, char const *argv[]) {
    // test 1 ------------------------
    // IntDecomposition *d = decomposition(38);
    // afficheListeDecomp(d);
    // d = completion(d, 16);
    // afficheListeDecomp(d);
    // d = completion(d, 4);
    // afficheListeDecomp(d);
    // libereIntDecomp(d);
    // -------------------------------
    // test 2 ------------------------
    // IntDecomposition *d = decomposition(38);
    // d = completion(d, 8);
    
    // afficheListeDecomp(d);

    // IntDecomposition *dg, *dd;
    // dg = partieGauche(d);
    // dd = partieDroite(d);

    // afficheListeDecomp(dg);
    // afficheListeDecomp(dd);

    // libereIntDecomp(d);
    // libereIntDecomp(dg);
    // libereIntDecomp(dd);
    // -------------------------------
    // test 2bis ---------------------
    IntDecomposition *d = decomposition(38);
    d = completion(d, 8);
    
    afficheListeDecomp(d);

    ArbreBin *ab = cons_arbre(d);
    afficheAB(ab);


    luka(ab); // (((()())(()()))((()())(()())))
    printf("\n");


    char *filename = "sortie";
    createDotFile(ab, filename);

    libereArbreBin(ab);
    libereIntDecomp(d);
    // -------------------------------

    return 0;
}


// macOS 
// leaks -atExit -- ./main