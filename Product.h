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

} Product;

Product* product_new(Type* t);
void product_delete(Product* product);

bool product_get_defaillance(Product* product);

#endif
