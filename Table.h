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


#ifndef TABLE_H
#define TABLE_H

#include "Machine.h"
#include "Type.h"
#include "Product.h"

typedef struct
{

    Machine* m__base;
    void* m__conveyor;

    Type* m__type;
    Product* m__product;

} Table;

Table* table_new(Type* type);
void table_delete(Table* table);

int table_start(Table* table);
int table_join(Table* table);
int table_stop(Table* table);
void table_wake(Table* table);
void* table_thread(void* args);

void table_receive_product_conveyor(Table* table, void* conveyor, Product* product);
void table_give_product_conveyor(Table* table);

Product* table_get_product(Table* table);
Type* table_get_type(Table* table);

void table_display(Table* table, int* line);

#endif
