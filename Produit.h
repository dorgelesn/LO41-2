#ifndef PRODUIT_H
#define PRODUIT_H

#include "Type.h"

typedef int bool;
#define true 1
#define false 0

typedef struct
{

    Type* m__type;
    bool m__defaillance;

} Produit;

Produit* produit_new(Type* t);
void produit_delete(Produit* produit);

bool produit_get_defaillance(Produit* produit);

#endif
