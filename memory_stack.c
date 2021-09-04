#ifndef MEMORY_STACK
#define MEMORY_STACK

#include <stdio.h> // printf, only in debug builds (if not defined MEMORY_STACK_RELEASE)
#include <stdlib.h> // exit, only in debug builds (if not defined MEMORY_STACK_RELEASE)
#include <stdint.h>
#define MEMORY_STACK_BYTE_MAX 64000000 // using 64Mo
// #define MEMORY_STACK_RELEASE 1

/******************************************** DEBUG/RELEASE MODES ******************************************/
// For Release
#ifdef MEMORY_STACK_RELEASE
    #define memory_stack_dealloc(pointer)                             memory_stack_dealloc_release((void*) pointer)
    #define memory_stack_alloc(variable_type, variable_name, number)\
        variable_type* variable_name = (variable_type*)memory_stack_alloc_release((sizeof(variable_type) * (number)));
#else
    // For Debug
    #include <stdio.h> // for printf
    #include <stdlib.h> // for exit
    #define memory_stack_dealloc(pointer)                             memory_stack_dealloc_debug((void*) pointer, __LINE__, __FILE__, #pointer)
    #define memory_stack_alloc(variable_type, variable_name, number)\
        variable_type* variable_name = (variable_type*)memory_stack_alloc_debug((sizeof(variable_type) * (number)), __LINE__, __FILE__, #variable_name);
#endif


/******************************************** VARIABLES ****************************************************/
static char     memory_stack_internal_bytes_stack[MEMORY_STACK_BYTE_MAX];
static int      memory_stack_internal_bytes_allocated = 0;


/******************************************** PROCEDURES ***************************************************/
void* memory_stack_alloc_release(int in_bytes)
{
    char* pointed_address = memory_stack_internal_bytes_stack + memory_stack_internal_bytes_allocated;
    memory_stack_internal_bytes_allocated += in_bytes;
    return pointed_address;
}

void* memory_stack_alloc_debug(int in_bytes, int in_line, char* in_file, char* in_variable_name)
{
    int max_bytes_available = sizeof(memory_stack_internal_bytes_stack)/sizeof(memory_stack_internal_bytes_stack[0]);
    if (memory_stack_internal_bytes_allocated + in_bytes > max_bytes_available)
    {
        printf("\n[MEMORY]: line %d in %s| Can't allocate more than %d bytes in this program\n", in_line, in_file, max_bytes_available);
        exit(1);
    }

    char* pointed_address = memory_stack_internal_bytes_stack + memory_stack_internal_bytes_allocated;
    memory_stack_internal_bytes_allocated += in_bytes;
    printf("[MEMORY]: %s \t\t\tline %d: in %s \t\t\t| %12d bytes allocated\t| TOTAL BYTES ALLOCATED: %d\n", in_variable_name, in_line, in_file, in_bytes, memory_stack_internal_bytes_allocated);
    return pointed_address;
}

void memory_stack_dealloc_release(void* out_value)
{
    void* current_address_available = memory_stack_internal_bytes_stack + memory_stack_internal_bytes_allocated;
    uintptr_t number_deallocated = (uintptr_t)current_address_available - (uintptr_t)out_value;
    memory_stack_internal_bytes_allocated -= number_deallocated;
}

void memory_stack_dealloc_debug(void* out_value, int in_line, char* in_file, char* in_variable_name)
{
    void* current_address_available = memory_stack_internal_bytes_stack + memory_stack_internal_bytes_allocated;
    if (out_value >= current_address_available)
    {
        printf("\n[MEMORY]: Error line %d in %s | Try to deallocate memory that wasn't the last allocated (%s)\n", in_line, in_file, in_variable_name);
        exit(1);
    }
    uintptr_t number_deallocated = (uintptr_t)current_address_available - (uintptr_t)out_value;
    memory_stack_internal_bytes_allocated -= number_deallocated;
    printf("[MEMORY]: %s \t\t\tline %d: in %s \t\t\t| %12llu bytes freed\t| TOTAL BYTES ALLOCATED: %d\n", in_variable_name, in_line, in_file, number_deallocated, memory_stack_internal_bytes_allocated);
}

#endif