#include "Product.h"

#include <stdio.h>
#include <stdlib.h>

#include "Display.h"

Product* product_new(Type* t)
{

    Product* p = malloc(sizeof(Product));

    p->m__type = t;
    p->m__defaillance = false;

    return p;

}


void product_delete(Product* product)
{

    free(product);

}


bool product_get_defaillance(Product* product)
{

    return false;

}
