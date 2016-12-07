#ifndef TABLE_H
#define TABLE_H

#include "Machine.h"
#include "Type.h"
#include "Produit.h"

typedef struct
{

    Machine* m__base;

    Type** m__types;
    Produit* m__produit;

} Table;

Table* table_new(Type** types);
void table_delete(Table* table);

void* table_start(void* args);

Produit* table_get_produit(Table* table);
bool table_is_occupe(Table* table);

#endif
