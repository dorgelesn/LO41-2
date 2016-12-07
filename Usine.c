#include "Usine.h"

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include "Affichage.h"

Usine* usine_new()
{

    afficher_debug("[Usine]: constructor\n");

    Usine* u = malloc(sizeof(Usine));

    Alimentation* alim = alimentation_new();
    Retrait* retrait = retrait_new();
    Table** tables = (Table**) malloc(sizeof(Table) * 3);

    Type* t1 = type_new(10, 30);

    Type* types[1] = {t1};
    tables[0] = table_new(types);
    tables[1] = table_new(types);
    tables[2] = table_new(types);

    u->m__types[0] = t1;

    u->m__convoyeur = convoyeur_new(alim, retrait, tables);
    u->m__superviseur = superviseur_new(alim);

    return u;

}


void usine_delete(Usine* usine)
{

    afficher_debug("[Usine]: destructor\n");

    convoyeur_delete(usine->m__convoyeur);
    superviseur_delete(usine->m__superviseur);

    type_delete(usine->m__types[0]);

    free(usine);

}

void* usine_start(void* args)
{

    afficher_debug("[Usine] : ==usine_start==\n");

    return 0;

}
