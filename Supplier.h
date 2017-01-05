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


#ifndef ALIMENTATION_H
#define ALIMENTATION_H

#include "Machine.h"

#include "Conveyor.h"
#include "Product.h"

typedef struct
{

    Machine* m__base;

    Conveyor* m__conveyor;

    Product* m__product;

} Supplier;

Supplier* supplier_new(Conveyor* conveyor);
void supplier_delete(Supplier* supplier);

int supplier_start(Supplier* supplier);
int supplier_join(Supplier* supplier);
int supplier_stop(Supplier* supplier);
void supplier_wake(Supplier* supplier);
void* supplier_thread(void* args);

void supplier_receive_product_supervisor(Supplier* supplier, Product* product);
void supplier_give_product_conveyor(Supplier* supplier);

Product* supplier_get_product(Supplier* supplier);

void supplier_display(Supplier* supplier, int* line);

#endif
