#ifndef CONVOYEUR_H
#define CONVOYEUR_H

#include "Machine.h"
#include "Alimentation.h"
#include "Retrait.h"
#include "Table.h"
#include "Produit.h"

typedef struct
{

    Machine* m__base;

    Alimentation* m__alimentation;
    Retrait* m__retrait;

    Table** m__tables;

    Produit* m__produit;

} Convoyeur;

Convoyeur* convoyeur_new(Alimentation* alim, Retrait* retrait, Table** tables);
void convoyeur_delete(Convoyeur* convoyeur);

void* convoyeur_start(void* args);

void convoyeur_set_produit(Convoyeur* convoyeur, Produit* produit);

#endif
