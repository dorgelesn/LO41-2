#ifndef TABLE_H
#define TABLE_H

#include "Machine.h"
#include "Type.h"
#include "Produit.h"

typedef struct
{

    Machine base;

    Type** m__types;
    Produit* m__produit;

} Table;

Table* new_table(Type** types);
void delete_table(Table* table);

Produit* table_get_produit(Table* table);
bool table_is_occupe(Table* table);

#endif
