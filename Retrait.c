#include "Retrait.h"

#include <stdio.h>
#include <stdlib.h>

Retrait* new_retrait()
{

    Retrait* r = malloc(sizeof(Retrait));

    return r;

}


void delete_retrait(Retrait* retrait)
{

    free(retrait);

}

