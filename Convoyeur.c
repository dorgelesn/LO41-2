#include "Convoyeur.h"

#include <stdio.h>
#include <stdlib.h>

Convoyeur* new_convoyeur(Alimentation* alim, Retrait* retrait, Table** tables)
{

    Convoyeur* c = malloc(sizeof(Convoyeur));

    c->m__alimentation = alim;
    c->m__retrait = retrait;
    c->m__tables = tables;

    return c;

}


void delete_convoyeur(Convoyeur* convoyeur)
{

    printf("[Convoyeur]: destructor\n");

    printf("[Convoyeur] destructeur(): 1\n");
    delete_alimentation(convoyeur->m__alimentation);
    printf("[Convoyeur] destructeur(): 2\n");
    delete_retrait(convoyeur->m__retrait);
    printf("[Convoyeur] destructeur(): 3\n");

    //free all the tables

    delete_table(convoyeur->m__tables[0]);
    delete_table(convoyeur->m__tables[1]);
    delete_table(convoyeur->m__tables[2]);

    free(convoyeur->m__tables);

    free(convoyeur);

}


void convoyeur_set_produit(Convoyeur* convoyeur, Produit* produit)
{



}
