#include "Retrait.h"

#include <stdio.h>
#include <stdlib.h>

#include "Affichage.h"

Retrait* retrait_new()
{

    afficher_debug("[Retrait]: constructor\n");

    Retrait* r = malloc(sizeof(Retrait));

    r->m__base = machine_new(&retrait_start);

    return r;

}


void retrait_delete(Retrait* retrait)
{

    afficher_debug("[Retrait]: destructor\n");

    machine_delete(retrait->m__base);

    free(retrait);

}


void* retrait_start(void* args)
{

    afficher_debug("[Retrait]: ==retrait_start==\n");

    return 0;

}
