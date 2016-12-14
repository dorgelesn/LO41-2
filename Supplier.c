#include "Supplier.h"

#include <stdio.h>
#include <stdlib.h>

#include "Display.h"

Supplier* supplier_new(Conveyor* conveyor, Product** products, int num_products)
{

    display_debug("[Supplier] : constructor\n");

    Supplier* a = malloc(sizeof(Supplier));
    a->m__base = machine_new();

    a->m__conveyor = conveyor;
    a->m__products = products;
    a->m__num_products = num_products;

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
    return machine_join(supplier->m__base);

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

    Supplier* alim = (Supplier*) argv;

    int i = 0;
    for(; i < alim->m__num_products; i++)
    {

        if(conveyor_get_product(alim->m__conveyor))
            machine_wait(alim->m__base);
        conveyor_receive_product_supplier(alim->m__conveyor, alim->m__products[i]);

    }

    while(!machine_get_should_stop(alim->m__base))
    {

        machine_lock(alim->m__base);
        {

            //Sleep
            machine_sleep(alim->m__base);

        }
        machine_unlock(alim->m__base);

    }

    return 0;

}
