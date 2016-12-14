#ifndef SUPERVISEUR_H
#define SUPERVISEUR_H

#include "Machine.h"
#include "Supplier.h"
#include "Conveyor.h"
#include "Type.h"
#include "Table.h"
#include "Product.h"

typedef struct
{

    Machine* m__base;

    Conveyor* m__conveyor;
    Supplier* m__supplier;
    Retrait* m__retrait;

    Type** m__types;
    int m__num_types;

    Table** m__tables;
    int m__num_tables;

    Product** m__products;
    int m__num_products;

} Supervisor;

Supervisor* supervisor_new(char* products, char* types, char* tables);
void supervisor_delete(Supervisor* supervisor);

int supervisor_start(Supervisor* supervisor);
int supervisor_join(Supervisor* supervisor);
int supervisor_stop(Supervisor* supervisor);
void* supervisor_thread(void* args);

void supervisor_import_products(Supervisor* supervisor, char* fichier_products);
void supervisor_import_types(Supervisor* supervisor, char* fichier_types);
void supervisor_import_tables(Supervisor* supervisor, char* fichier_tables);

#endif
