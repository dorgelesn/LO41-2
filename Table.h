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

int table_start(Table* table);
int table_join(Table* table);
int table_stop(Table* table);
void table_wake(Table* table);
void* table_thread(void* args);

void table_recevoir_produit_convoyeur(Table* table, void* convoyeur, Produit* produit);
void table_donner_produit_convoyeur(Table* table, void* convoyeur);

Produit* table_get_produit(Table* table);
bool table_is_occupe(Table* table);

#endif
