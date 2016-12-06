#include "Usine.h"

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

Usine* new_usine()
{

    Usine* u = malloc(sizeof(Usine));

    Alimentation* alim = new_alimentation();
    Retrait* retrait = new_retrait();
    Table** tables = (Table**) malloc(sizeof(Table) * 3);

    Type* t1 = new_type(10, 30);

    Type* types[1] = {t1};
    tables[0] = new_table(types);
    tables[1] = new_table(types);
    tables[2] = new_table(types);

    u->m__types[0] = t1;

    u->m__convoyeur = new_convoyeur(alim, retrait, tables);
    u->m__superviseur = new_superviseur();

    return u;

}


void delete_usine(Usine* usine)
{

    printf("[Usine]: destructor\n");

    printf("[Usine] destructor(): 0\n");
    delete_convoyeur(usine->m__convoyeur);
    printf("[Usine] destructor(): 1\n");
    delete_superviseur(usine->m__superviseur);
    printf("[Usine] destructor(): 2\n");

    delete_type(usine->m__types[0]);
    printf("[Usine] destructor(): 3\n");

    free(usine);

}

void start_usine(Usine* usine)
{

    printf("[Usine] : start_usine\n");

    printf("[Usine] start_usine() : %p \n", usine);

    sleep(1);

}
