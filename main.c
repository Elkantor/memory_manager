#include <stdio.h>
#include "memory_manager.c"


int main()
{
    // Here is a quick example how to use the memory_manager module
    {
        memory_manager_alloc(int, array, 2000000);
        for (int i = 0; i < 2000000; ++i)
            array[i] = 10;

        memory_manager_alloc(float, array2, 12);
        for (int i = 0; i < 12; ++i)
            array2[i] = 2.f;
    }

    return 0;
}