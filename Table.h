#ifndef TABLE_H
#define TABLE_H

#include "Machine.h"
#include "Type.h"
#include "Product.h"

typedef struct
{

    Machine* m__base;

    Type** m__types;
    Product* m__product;

} Table;

Table* table_new(Type** types);
void table_delete(Table* table);

int table_start(Table* table);
int table_join(Table* table);
int table_stop(Table* table);
void table_wake(Table* table);
void* table_thread(void* args);

void table_receive_product_conveyor(Table* table, void* conveyor, Product* product);
void table_donner_product_conveyor(Table* table, void* conveyor);

Product* table_get_product(Table* table);
bool table_is_occupe(Table* table);

#endif
