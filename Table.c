#include "Table.h"

#include <stdio.h>
#include <stdlib.h>

Table* new_table(Type** types)
{

    Table* t = malloc(sizeof(Table));

    t->m__types = types;

    return t;

}


void delete_table(Table* table)
{

    if(table_is_occupe(table))
        delete_produit(table->m__produit);

    free(table);

}


Produit* table_get_produit(Table* table)
{

    return NULL;

}


bool table_is_occupe(Table* table)
{

    return false;

}
