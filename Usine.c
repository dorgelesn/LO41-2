#include "Usine.h"

#include <stdio.h>
#include <stdlib.h>

Usine* new_usine()
{

    Usine* u = malloc(sizeof(Usine));

    Alimentation* alim = new_alimentation();
    Retrait* retrait = new_retrait();
    Table** tables = (Table**) malloc(sizeof(Table) * 3);

    u->m__convoyeur = new_convoyeur(alim, retrait, tables);
    u->m__superviseur = new_superviseur();

    return u;

}


void delete_usine(Usine* usine)
{

    delete_convoyeur(usine->m__convoyeur);
    delete_superviseur(usine->m__superviseur);

    free(usine);

}

void start_usine(Usine* usine)
{

    printf("[Usine] : start_usine\n");

    printf("[Usine] start_usine() : %p \n", usine);

}
