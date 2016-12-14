#ifndef CONVOYEUR_H
#define CONVOYEUR_H

#include "Machine.h"
#include "Retrait.h"
#include "Table.h"
#include "Produit.h"

typedef struct
{

    Machine* m__base;

    Retrait* m__retrait;

    Table** m__tables;
    int m__num_tables;

    Produit* m__produit;
    int m__position;

} Convoyeur;

Convoyeur* convoyeur_new(Retrait* retrait, Table** tables, int num_tables);
void convoyeur_delete(Convoyeur* convoyeur);

int convoyeur_start(Convoyeur* convoyeur);
int convoyeur_join(Convoyeur* convoyeur);
int convoyeur_stop(Convoyeur* convoyeur);
void convoyeur_wake(Convoyeur* convoyeur);
void* convoyeur_thread(void* args);

void convoyeur_recevoir_produit_alimentation(Convoyeur* convoyeur, Produit* produit);
void convoyeur_recevoir_produit_table(Convoyeur* convoyeur, Table* table, Produit* produit);

void convoyeur_donner_produit_table(Convoyeur* convoyeur, Table* table);
void convoyeur_donner_produit_retrait(Convoyeur* convoyeur);

int convoyeur_position_max(Convoyeur* convoyeur);
Produit* convoyeur_get_produit(Convoyeur* convoyeur);

#endif
