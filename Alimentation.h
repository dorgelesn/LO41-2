#ifndef ALIMENTATION_H
#define ALIMENTATION_H

#include "Machine.h"
#include "Produit.h"

typedef struct
{

    Machine* base;

    Produit** m__attente;

} Alimentation;

Alimentation* new_alimentation();
void delete_alimentation(Alimentation* alimentation);

#endif
