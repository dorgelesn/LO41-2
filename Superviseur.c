#include "Superviseur.h"

#include <stdio.h>
#include <stdlib.h>

Superviseur* new_superviseur()
{

    Superviseur* s = malloc(sizeof(Superviseur));

    return s;

}


void delete_superviseur(Superviseur* superviseur)
{

    printf("[Machine]: destructor\n");

    free(superviseur);

}
