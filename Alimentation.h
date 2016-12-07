#ifndef ALIMENTATION_H
#define ALIMENTATION_H

#include "Machine.h"
#include "Produit.h"

typedef struct
{

    Machine* m__base;

    Produit** m__attente;

} Alimentation;

Alimentation* alimentation_new();
void alimentation_delete(Alimentation* alimentation);

void* alimentation_start(void* args);

#endif
