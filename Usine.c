#include "Usine.h"

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include "Affichage.h"

Usine* usine_new(char* produits, char* types, char* tables)
{

    afficher_debug("[Usine]: constructor\n");

    Usine* u = malloc(sizeof(Usine));

    u->m__superviseur = superviseur_new(produits, types, tables);

    return u;

}


void usine_delete(Usine* usine)
{

    afficher_debug("[Usine]: destructor\n");

    superviseur_delete(usine->m__superviseur);

    free(usine);

}

int usine_start(Usine* usine)
{

    afficher_debug("[Usine] : ==usine_start==\n");

    return superviseur_start(usine->m__superviseur);

}


int usine_join(Usine* usine)
{

    afficher_debug("[Usine]: ==usine_join==\n");
    return superviseur_join(usine->m__superviseur);

}


int usine_stop(Usine* usine)
{

    afficher_debug("[Usine]: ==usine_stop==\n");
    return superviseur_stop(usine->m__superviseur);

}

