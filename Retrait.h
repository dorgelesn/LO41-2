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
