#ifndef CONVOYEUR_H
#define CONVOYEUR_H

#include "Machine.h"
#include "Retrait.h"
#include "Table.h"
#include "Product.h"

typedef struct
{

    Machine* m__base;

    Retrait* m__retrait;

    Table** m__tables;
    int m__num_tables;

    Product* m__product;
    int m__position;

} Conveyor;

Conveyor* conveyor_new(Retrait* retrait, Table** tables, int num_tables);
void conveyor_delete(Conveyor* conveyor);

int conveyor_start(Conveyor* conveyor);
int conveyor_join(Conveyor* conveyor);
int conveyor_stop(Conveyor* conveyor);
void conveyor_wake(Conveyor* conveyor);
void* conveyor_thread(void* args);

void conveyor_receive_product_supplier(Conveyor* conveyor, Product* product);
void conveyor_receive_product_table(Conveyor* conveyor, Table* table, Product* product);

void conveyor_donner_product_table(Conveyor* conveyor, Table* table);
void conveyor_donner_product_retrait(Conveyor* conveyor);

int conveyor_position_max(Conveyor* conveyor);
Product* conveyor_get_product(Conveyor* conveyor);

#endif
