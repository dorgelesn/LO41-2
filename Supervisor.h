/*
 * Gnikwo < gnikwo AT hotmail DOT com >
 *
 * Copyright (c) 2016 Gnikwo
 *
 * Permission is hereby granted, free of charge,
 * to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction,
 * including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice
 * shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */


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
    int m__current_product;

    int m__num_finished;

} Supervisor;

Supervisor* supervisor_new(int num_products, int num_types, int num_tables);
void supervisor_delete(Supervisor* supervisor);

int supervisor_start(Supervisor* supervisor);
int supervisor_join(Supervisor* supervisor);
int supervisor_stop(Supervisor* supervisor);
void supervisor_wake(void* supervisor);
void* supervisor_thread(void* args);

void supervisor_give_product_supplier(Supervisor* supervisor, Product* product);

void supervisor_import_products(Supervisor* supervisor, int num_products);
void supervisor_import_types(Supervisor* supervisor, int num_types);
void supervisor_import_tables(Supervisor* supervisor, int num_tables);

void supervisor_product_finished(Supervisor* supervisor);
bool supervisor_finished(Supervisor* supervisor);

void supervisor_display(Supervisor* supervisor, int* line);

#endif
