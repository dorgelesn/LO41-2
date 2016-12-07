#include "Table.h"

#include <stdio.h>
#include <stdlib.h>

#include "Affichage.h"

Table* table_new(Type** types)
{

    afficher_debug("[Table]: constructor\n");

    Table* t = malloc(sizeof(Table));

    t->m__types = types;
    t->m__base = machine_new(&table_start);

    return t;

}


void table_delete(Table* table)
{

    afficher_debug("[Table]: desctructor\n");

    machine_delete(table->m__base);
    free(table);

}


void* table_start(void* args)
{

    afficher_debug("[Table]: ==table_start==\n");

    return 0;

}


Produit* table_get_produit(Table* table)
{

    return NULL;

}


bool table_is_occupe(Table* table)
{

    return false;

}
