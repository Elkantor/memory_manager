#include <stdlib.h> // for exit()

/******************************************** CONFIG *******************************************************/
// #define MEMORY_MANAGER_RELEASE 1
#define MEMORY_MANAGER_BYTE_MAX 64000000 // using 64Mo

#define defer _d0(__COUNTER__)
#define _d0(X) _d1(X)
#define _d1(X) _d2(s##X,f##X)
#define _d2(S,F) auto void F(void*);int S __attribute__((cleanup(F)));void F(void*_)

/******************************************** DEBUG/RELEASE MODES ******************************************/
#ifdef MEMORY_MANAGER_RELEASE
    // For Release
    #define memory_manager_dealloc(pointer)                             memory_manager_dealloc_release((void*) pointer)
    #define memory_manager_alloc(variable_type, variable_name, number)\
        variable_type* variable_name = memory_manager_alloc_release((sizeof(variable_type) * (number)));\
        defer { memory_manager_dealloc(variable_name); }
#else
    // For Debug
    #define memory_manager_dealloc(pointer)                             memory_manager_dealloc_debug((void*) pointer, __LINE__, __FILE__, #pointer)
    #define memory_manager_alloc(variable_type, variable_name, number)\
        variable_type* variable_name = memory_manager_alloc_debug((sizeof(variable_type) * (number)), __LINE__, __FILE__, #variable_name);\
        defer { memory_manager_dealloc(variable_name); }
#endif

/******************************************** VARIABLES ****************************************************/
static char     internal_memory_manager_bytes_stack[MEMORY_MANAGER_BYTE_MAX];
static int      internal_memory_manager_bytes_allocated = 0;


/******************************************** PROCEDURES ***************************************************/
void* memory_manager_alloc_release(int in_bytes)
{
    char* pointed_address = internal_memory_manager_bytes_stack + internal_memory_manager_bytes_allocated;
    internal_memory_manager_bytes_allocated += in_bytes;
    return pointed_address;
}

void* memory_manager_alloc_debug(int in_bytes, int in_line, char* in_file, char* in_variable_name)
{
    int max_bytes_available = sizeof(internal_memory_manager_bytes_stack)/sizeof(internal_memory_manager_bytes_stack[0]);
    if (internal_memory_manager_bytes_allocated + in_bytes > max_bytes_available)
    {
        printf("\n[MEMORY]: line %d in %s| Can't allocate more than %d bytes in this program\n", in_line, in_file, max_bytes_available);
        exit(1);
    }

    char* pointed_address = internal_memory_manager_bytes_stack + internal_memory_manager_bytes_allocated;
    internal_memory_manager_bytes_allocated += in_bytes;
    printf("[MEMORY]: %s \t\t\tline %d: in %s \t\t\t| %12d bytes allocated\t| TOTAL BYTES ALLOCATED: %d\n", in_variable_name, in_line, in_file, in_bytes, internal_memory_manager_bytes_allocated);
    return pointed_address;
}

void memory_manager_dealloc_release(void* out_value)
{
    void* current_address_available = internal_memory_manager_bytes_stack + internal_memory_manager_bytes_allocated;
    int number_deallocated = current_address_available - out_value;
    internal_memory_manager_bytes_allocated -= number_deallocated;
}

void memory_manager_dealloc_debug(void* out_value, int in_line, char* in_file, char* in_variable_name)
{
    void* current_address_available = internal_memory_manager_bytes_stack + internal_memory_manager_bytes_allocated;
    if (out_value >= current_address_available)
    {
        printf("\n[MEMORY]: Error line %d in %s | Try to deallocate memory that wasn't the last allocated (%s)\n", in_line, in_file, in_variable_name);
        exit(1);
    }
    int number_deallocated = current_address_available - out_value;
    internal_memory_manager_bytes_allocated -= number_deallocated;
    printf("[MEMORY]: %s \t\t\tline %d: in %s \t\t\t| %12d bytes freed\t| TOTAL BYTES ALLOCATED: %d\n", in_variable_name, in_line, in_file, number_deallocated, internal_memory_manager_bytes_allocated);
}
