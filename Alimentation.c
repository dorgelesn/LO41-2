#include "Alimentation.h"

#include <stdio.h>
#include <stdlib.h>

void* alimentation_start(void* argv);

Alimentation* new_alimentation()
{

    Alimentation* a = malloc(sizeof(Alimentation));
    a->base = new_machine(alimentation_start);

    return a;

}


void delete_alimentation(Alimentation* alimentation)
{

    //free attente

    free(alimentation);

}


void* alimentation_start(void* argv)
{

    printf("[Alimentation] : alimentation_start\n");

    while(1)
    {

        printf("[Alimentation] alimentation_start(): test\n");

    }

}
