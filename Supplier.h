#ifndef ALIMENTATION_H
#define ALIMENTATION_H

#include "Machine.h"

#include "Conveyor.h"
#include "Product.h"

typedef struct
{

    Machine* m__base;

    Conveyor* m__conveyor;

    Product** m__products;
    int m__num_products;

} Supplier;

Supplier* supplier_new();
void supplier_delete(Supplier* supplier);

int supplier_start(Supplier* supplier);
int supplier_join(Supplier* supplier);
int supplier_stop(Supplier* supplier);
void supplier_wake(Supplier* supplier);
void* supplier_thread(void* args);

#endif
