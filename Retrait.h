#ifndef RETRAIT_H
#define RETRAIT_H

#include "Machine.h"

#include "Produit.h"

typedef struct
{

    Machine* m__base;

    Produit* m__produit;

} Retrait;

Retrait* retrait_new();
void retrait_delete(Retrait* retrait);


int retrait_start(Retrait* retrait);
int retrait_join(Retrait* retrait);
int retrait_stop(Retrait* retrait);
void retrait_wake(Retrait* retrait);
void* retrait_thread(void* args);

void retrait_recevoir_produit_convoyeur(Retrait* retrait, Produit* produit);
void retrait_donner_produit(Retrait* retrait);

#endif
