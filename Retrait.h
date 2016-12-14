#ifndef RETRAIT_H
#define RETRAIT_H

#include "Machine.h"

#include "Product.h"

typedef struct
{

    Machine* m__base;

    Product* m__product;

} Retrait;

Retrait* retrait_new();
void retrait_delete(Retrait* retrait);


int retrait_start(Retrait* retrait);
int retrait_join(Retrait* retrait);
int retrait_stop(Retrait* retrait);
void retrait_wake(Retrait* retrait);
void* retrait_thread(void* args);

void retrait_receive_product_conveyor(Retrait* retrait, Product* product);
void retrait_donner_product(Retrait* retrait);

#endif
