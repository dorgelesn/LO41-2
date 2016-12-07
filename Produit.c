#include "Produit.h"

#include <stdio.h>
#include <stdlib.h>

#include "Affichage.h"

Produit* produit_new(Type* t)
{

    Produit* p = malloc(sizeof(Produit));

    p->m__type = t;
    p->m__defaillance = false;

    return p;

}


void produit_delete(Produit* produit)
{

    free(produit);

}


bool produit_get_defaillance(Produit* produit)
{

    return false;

}
