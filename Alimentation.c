#include "Alimentation.h"

#include <stdio.h>
#include <stdlib.h>

void* alimentation_start(void* argv);

Alimentation* new_alimentation()
{

    printf("[Alimentation] : constructor\n");

    Alimentation* a = malloc(sizeof(Alimentation));
    a->base = new_machine(&alimentation_start);

    return a;

}


void delete_alimentation(Alimentation* alimentation)
{

    printf("[Alimentation]: destructeur\n");
    //free attente
    printf("[Alimentation] destructeur(): 1\n");

    delete_machine(alimentation->base);
    printf("[Alimentation] destructeur(): 2\n");

    free(alimentation);
    printf("[Alimentation] destructeur(): 3\n");

}


void* alimentation_start(void* argv)
{

    printf("[Alimentation] : alimentation_start\n");

    for(int i = 0; i < 100; i++)
    {

        printf("[Alimentation] alimentation_start(): test\n");

        usleep(10000);

    }

    return;

}
