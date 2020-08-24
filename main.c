#include <stdio.h>
#include "memory_manager.c"

int main()
{
    memory_manager_init();
    int* array = memory_manager_int_alloc(3);

    int* array2 = memory_manager_int_alloc(2);

    for (int i = 0; i < 3; ++i)
        array[i] = 2;
    
    for (int i = 0; i < 3; ++i)
        printf("value array at %d = %d\n", i, array[i]);

    memory_manager_int_dealloc(array2);
    memory_manager_int_dealloc(array);

    memory_manager_destroy();
    return 0;
}