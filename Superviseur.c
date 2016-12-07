#include "Superviseur.h"

#include <stdio.h>
#include <stdlib.h>

#include "Affichage.h"

Superviseur* superviseur_new(Alimentation* alimentation)
{

    afficher_debug("[Superviseur]: constructor\n");

    Superviseur* s = malloc(sizeof(Superviseur));

    s->m__base = machine_new(&superviseur_start);

    s->m__alimentation = alimentation;

    return s;

}


void superviseur_delete(Superviseur* superviseur)
{

    afficher_debug("[Superviseur]: destructor\n");

    machine_delete(superviseur->m__base);

    free(superviseur);

}


void* superviseur_start(void* args)
{

    afficher_debug("[Superviseur]: ==superviseur_start==\n");

    return 0;

}
