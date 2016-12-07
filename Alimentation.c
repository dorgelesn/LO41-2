#include "Alimentation.h"

#include <stdio.h>
#include <stdlib.h>

#include "Affichage.h"

Alimentation* alimentation_new()
{

    afficher_debug("[Alimentation] : constructor\n");

    Alimentation* a = malloc(sizeof(Alimentation));
    a->m__base = machine_new(&alimentation_start);

    return a;

}


void alimentation_delete(Alimentation* alimentation)
{

    afficher_debug("[Alimentation]: destructor\n");
    //free attente

    machine_delete(alimentation->m__base);

    free(alimentation);

}


void* alimentation_start(void* argv)
{

    afficher_debug("[Alimentation] : ==alimentation_start==\n");

    return 0;

}
