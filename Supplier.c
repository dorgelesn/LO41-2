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


#include "Supplier.h"

#include <stdio.h>
#include <stdlib.h>

#include "Display.h"

Supplier* supplier_new(Conveyor* conveyor)
{

    display_debug("[Supplier] : constructor\n");

    Supplier* a = malloc(sizeof(Supplier));
    a->m__base = machine_new();

    a->m__conveyor = conveyor;
    a->m__product = NULL;
    return a;

}


void supplier_delete(Supplier* supplier)
{

    display_debug("[Supplier]: destructor\n");

    machine_delete(supplier->m__base);

    free(supplier);

}


int supplier_start(Supplier* supplier)
{

    return machine_start(supplier->m__base, &supplier_thread, supplier);

}


int supplier_join(Supplier* supplier)
{

    display_debug("[Supplier]: ==supplier_thread_join==\n");
    int res = machine_join(supplier->m__base);

    display_debug("[Supplier]: ==supplier_thread_join_2==\n");

    return res;

}


int supplier_stop(Supplier* supplier)
{

    display_debug("[Supplier]: ==supplier_thread_stop==\n");
    return machine_stop(supplier->m__base);

}


void supplier_wake(Supplier* supplier){

    machine_wake(supplier->m__base);
    return;

}


void* supplier_thread(void* argv)
{

    display_debug("[Supplier] : ==supplier_thread==\n");

    Supplier* supplier = (Supplier*) argv;

    while(!machine_get_should_stop(supplier->m__base))
    {

        if(!supplier->m__product)
            machine_sleep(supplier->m__base);

        if(!machine_get_should_stop(supplier->m__base))
            supplier_give_product_conveyor(supplier);

    }

    pthread_exit(0);

    return 0;

}


void supplier_receive_product_supervisor(Supplier* supplier, Product* product)
{

    machine_lock(supplier->m__base);
    {

        if(supplier->m__product)
            machine_wait_receive(supplier->m__base);

    }
    machine_unlock(supplier->m__base);

    if(!machine_get_should_stop(supplier->m__base))
    {

        supplier->m__product = product;

        machine_wake(supplier->m__base);

    }

}


void supplier_give_product_conveyor(Supplier* supplier)
{

        conveyor_receive_product_supplier(supplier->m__conveyor, supplier, supplier->m__product);
        supplier->m__product = NULL;

}


void supplier_display(Supplier* supplier, int* line)
{

    *(line) = *(line) + 1;

    display("Supplier: %p", *line, supplier->m__product);

}
