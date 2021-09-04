#include <stdio.h>
#include "memory_stack.c"


int main()
{
    // Here is a quick example how to use the memory_manager module
    {
        memory_stack_alloc(int, array, 2000000);
        for (int i = 0; i < 2000000; ++i)
            array[i] = 10;

        memory_stack_alloc(float, array2, 12);
        for (int i = 0; i < 12; ++i)
            array2[i] = 2.f;

        memory_stack_dealloc(array);
        /*  Because it's a stack, if we deallocate a higher rank variables, the variables which
            are allocated after that are deallocated too.
            So when calling memory_stack_dealloc(array), we dealloc the entire stack up to array.
            So array2 is also deallocated.
        */
    }

    return 0;
}