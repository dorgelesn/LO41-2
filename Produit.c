#include "Produit.h"

#include <stdio.h>
#include <stdlib.h>

Produit* new_produit(Type* t)
{

    Produit* p = malloc(sizeof(Produit));

    p->m__type = t;
    p->m__defaillance = false;

    return p;

}


void delete_produit(Produit* produit)
{

    free(produit);

}


bool produit_get_defaillance(Produit* produit)
{

    return false;

}
