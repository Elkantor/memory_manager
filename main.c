#include <stdio.h>
#include "memory_manager.c"

int main()
{
    // Here is a quick example how to use the memory_manager module
    memory_manager_alloc(int, array, 10);
    memory_manager_alloc(int, array2, 100);
    memory_manager_alloc(float, array_float, 5);

    for (int i = 0; i < 5; ++i)
        array_float[i] = 2.f;

    memory_manager_dealloc(array_float);
    memory_manager_dealloc(array2);
    memory_manager_dealloc(array);

    return 0;
}