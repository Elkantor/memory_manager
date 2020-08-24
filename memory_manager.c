#include <stdlib.h>

struct internal_memory_manager
{
    int     internal_memory_manager_int_array[1000];
    float   internal_memory_manager_float_array[1000];
    double  internal_memory_manager_double_array[1000];

    int     internal_memory_manager_ints_allocated;

    float   internal_memory_manager_floats_allocated;
    double  internal_memory_manager_doubles_allocated;
};

struct internal_memory_manager* internal_memory_manager_handle;

void memory_manager_init()
{
    internal_memory_manager_handle = malloc( (sizeof *internal_memory_manager_handle) );
    internal_memory_manager_handle->internal_memory_manager_ints_allocated              = 0;
    internal_memory_manager_handle->internal_memory_manager_floats_allocated            = 0;
    internal_memory_manager_handle->internal_memory_manager_doubles_allocated           = 0;
}

void memory_manager_destroy()
{
    free(internal_memory_manager_handle);
}

#define memory_manager_int_alloc(n) memory_manager_int_alloc_internal(n, __LINE__, __FILE__)

int* memory_manager_int_alloc_internal(int in_number, char* in_line, char* in_file)
{
    int* pointed_address = internal_memory_manager_handle->internal_memory_manager_int_array + internal_memory_manager_handle->internal_memory_manager_ints_allocated;
    internal_memory_manager_handle->internal_memory_manager_ints_allocated += in_number;
    printf("[MEMORY]: %d int allocated (%I64d bytes) | TOTAL INT ALLOCATED: %d\n", in_number, in_number * sizeof(int), internal_memory_manager_handle->internal_memory_manager_ints_allocated);
    return pointed_address;
}

void memory_manager_int_dealloc(int* out_value)
{
    int* current_address_available = internal_memory_manager_handle->internal_memory_manager_int_array + internal_memory_manager_handle->internal_memory_manager_ints_allocated;
    if (out_value >= current_address_available)
    {
        printf("[MEMORY]: Try to deallocate memory that wasn't the last allocated\n");
        free(internal_memory_manager_handle);
        exit(1);
    }


    int number_deallocated = current_address_available - out_value;
    internal_memory_manager_handle->internal_memory_manager_ints_allocated -= number_deallocated;
    printf("[MEMORY]: %d int freed (%I64d bytes) | TOTAL INT ALLOCATED: %d\n", number_deallocated, number_deallocated * sizeof(int), internal_memory_manager_handle->internal_memory_manager_ints_allocated);
}

int memory_manager_int_allocated_get()
{
    return internal_memory_manager_handle->internal_memory_manager_ints_allocated;
}

int* memory_manager_int_allocated_last()
{
    int* pointed_address = internal_memory_manager_handle->internal_memory_manager_int_array + internal_memory_manager_handle->internal_memory_manager_ints_allocated;
    return pointed_address;
}