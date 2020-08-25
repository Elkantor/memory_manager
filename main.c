#include <stdio.h>
#include "memory_manager.c"

int main()
{
    // Here is a quick example how to use the memory_manager module

    int* array          = memory_manager_alloc(3 * sizeof(int));
    int* array2         = memory_manager_alloc(100 * sizeof(int));
    float* array_float  = memory_manager_alloc(5 * sizeof(float));

    memory_manager_dealloc(array_float);
    memory_manager_dealloc(array2);
    memory_manager_dealloc(array);

    return 0;
}