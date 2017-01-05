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


#include "Product.h"

#include <stdio.h>
#include <stdlib.h>

#include "Display.h"

Product* product_new(Type* t)
{

    Product* p = malloc(sizeof(Product));

    p->m__type = t;
    p->m__progression = 0;
    p->m__defaillance = false;

    return p;

}


void product_delete(Product* product)
{

    display_debug("[Product]: destructor\n");
    free(product);

}


bool product_get_defaillance(Product* product)
{

    return false;

}


bool product_treat(Product* product)
{

    sleep(1);
    product->m__progression++;

    return product->m__progression > type_get_time(product->m__type);

}


bool product_treated(Product* product)
{

    return product->m__progression >= type_get_time(product->m__type);

}


Type* product_get_type(Product* product)
{

    return product->m__type;

}


void product_display(Product* product, int* line)
{

    *(line) = *(line) + 1;

    display("    Product : %i", *line, product->m__progression);

}
