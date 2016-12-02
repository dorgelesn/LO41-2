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

    delete_alimentation(convoyeur->m__alimentation);
    delete_retrait(convoyeur->m__retrait);

    //free all the tables

    free(convoyeur);

}


void convoyeur_set_produit(Convoyeur* convoyeur, Produit* produit)
{



}
