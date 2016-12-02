#ifndef CONVOYEUR_H
#define CONVOYEUR_H

#include "Machine.h"
#include "Alimentation.h"
#include "Retrait.h"
#include "Table.h"
#include "Produit.h"

typedef struct
{

    Machine base;

    Alimentation* m__alimentation;
    Retrait* m__retrait;

    Table** m__tables;

    Produit* m__produit;

} Convoyeur;

Convoyeur* new_convoyeur(Alimentation* alim, Retrait* retrait, Table** tables);
void delete_convoyeur(Convoyeur* convoyeur);

void convoyeur_set_produit(Convoyeur* convoyeur, Produit* produit);

#endif
