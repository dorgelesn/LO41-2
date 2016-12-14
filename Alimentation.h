#ifndef ALIMENTATION_H
#define ALIMENTATION_H

#include "Machine.h"

#include "Convoyeur.h"
#include "Produit.h"

typedef struct
{

    Machine* m__base;

    Convoyeur* m__convoyeur;

    Produit** m__produits;
    int m__num_produits;

} Alimentation;

Alimentation* alimentation_new();
void alimentation_delete(Alimentation* alimentation);

int alimentation_start(Alimentation* alimentation);
int alimentation_join(Alimentation* alimentation);
int alimentation_stop(Alimentation* alimentation);
void alimentation_wake(Alimentation* alimentation);
void* alimentation_thread(void* args);

#endif
