#include "Convoyeur.h"

#include <stdio.h>
#include <stdlib.h>

#include "Affichage.h"

Convoyeur* convoyeur_new(Alimentation* alim, Retrait* retrait, Table** tables)
{

    afficher_debug("[Convoyeur]: constructor\n");

    Convoyeur* c = malloc(sizeof(Convoyeur));

    c->m__alimentation = alim;
    c->m__retrait = retrait;
    c->m__tables = tables;

    c->m__base = machine_new(&convoyeur_start);

    return c;

}


void convoyeur_delete(Convoyeur* convoyeur)
{

    afficher_debug("[Convoyeur]: destructor\n");

    alimentation_delete(convoyeur->m__alimentation);
    retrait_delete(convoyeur->m__retrait);

    //free all the tables

    table_delete(convoyeur->m__tables[0]);
    table_delete(convoyeur->m__tables[1]);
    table_delete(convoyeur->m__tables[2]);

    free(convoyeur->m__tables);

    machine_delete(convoyeur->m__base);

    free(convoyeur);

}


void* convoyeur_start(void* args)
{

    afficher_debug("[Convoyeur]: ==convoyeur_start==\n");

    return 0;

}


void convoyeur_set_produit(Convoyeur* convoyeur, Produit* produit)
{



}
