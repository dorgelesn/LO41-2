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


#ifndef CONVOYEUR_H
#define CONVOYEUR_H

#include "Machine.h"
#include "Retrait.h"
#include "Table.h"
#include "Product.h"

typedef struct
{

    Machine* m__base;

    void* m__supervisor;

    Retrait* m__retrait;

    Table** m__tables;
    int m__num_tables;

    Product* m__product;
    int m__position;

} Conveyor;

Conveyor* conveyor_new(void* supervisor, Retrait* retrait, Table** tables, int num_tables);
void conveyor_delete(Conveyor* conveyor);

int conveyor_start(Conveyor* conveyor);
int conveyor_join(Conveyor* conveyor);
int conveyor_stop(Conveyor* conveyor);
void conveyor_wake(Conveyor* conveyor);
void* conveyor_thread(void* args);

void conveyor_receive_product_supplier(Conveyor* conveyor, void* supplier, Product* product);
void conveyor_receive_product_table(Conveyor* conveyor, Table* table, Product* product);

void conveyor_give_product_table(Conveyor* conveyor, Table* table);
void conveyor_give_product_retrait(Conveyor* conveyor);

int conveyor_position_max(Conveyor* conveyor);
Product* conveyor_get_product(Conveyor* conveyor);

void conveyor_display(Conveyor* conveyor, int* line);

#endif
