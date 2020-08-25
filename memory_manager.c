#include <stdlib.h> // for exit()

/******************************************** CONFIG *******************************************************/
// #define MEMORY_MANAGER_RELEASE 1
#define MEMORY_MANAGER_BYTE_MAX 100000


/******************************************** DEBUG/RELEASE MODES ******************************************/
#ifdef MEMORY_MANAGER_RELEASE
    // For Release
    #define memory_manager_alloc(bytes)     memory_manager_alloc_release(bytes)
    #define memory_manager_dealloc(pointer) memory_manager_dealloc_release((void*) pointer)
#else
    // For Debug
    #define memory_manager_alloc(bytes)     memory_manager_alloc_debug(bytes, __LINE__, __FILE__)
    #define memory_manager_dealloc(pointer) memory_manager_dealloc_debug((void*) pointer, __LINE__, __FILE__)
#endif


/******************************************** VARIABLES ****************************************************/
static char internal_memory_manager_bytes_stack[MEMORY_MANAGER_BYTE_MAX];
static int  internal_memory_manager_bytes_allocated = 0;


/******************************************** PROCEDURES ***************************************************/
void* memory_manager_alloc_release(int in_bytes)
{
    char* pointed_address = internal_memory_manager_bytes_stack + internal_memory_manager_bytes_allocated;
    internal_memory_manager_bytes_allocated += in_bytes;
    return pointed_address;
}

void* memory_manager_alloc_debug(int in_bytes, int in_line, char* in_file)
{
    int max_bytes_available = sizeof(internal_memory_manager_bytes_stack)/sizeof(internal_memory_manager_bytes_stack[0]);
    if (internal_memory_manager_bytes_allocated + in_bytes > max_bytes_available)
    {
        printf("\n[MEMORY]: line %d in %s| Can't allocate more than %d bytes in this program\n", in_line, in_file, max_bytes_available);
        exit(1);
    }

    char* pointed_address = internal_memory_manager_bytes_stack + internal_memory_manager_bytes_allocated;
    internal_memory_manager_bytes_allocated += in_bytes;
    printf("[MEMORY]: line %d: in %s \t\t| %d bytes allocated\t\t| TOTAL BYTES ALLOCATED: %d\n", in_line, in_file, in_bytes, internal_memory_manager_bytes_allocated);
    return pointed_address;
}

void memory_manager_dealloc_release(void* out_value)
{
    void* current_address_available = internal_memory_manager_bytes_stack + internal_memory_manager_bytes_allocated;
    int number_deallocated = current_address_available - out_value;
    internal_memory_manager_bytes_allocated -= number_deallocated;
}

void memory_manager_dealloc_debug(void* out_value, int in_line, char* in_file)
{
    void* current_address_available = internal_memory_manager_bytes_stack + internal_memory_manager_bytes_allocated;
    if (out_value >= current_address_available)
    {
        printf("\n[MEMORY]: Error line %d in %s | Try to deallocate memory that wasn't the last allocated\n", in_line, in_file);
        exit(1);
    }
    int number_deallocated = current_address_available - out_value;
    internal_memory_manager_bytes_allocated -= number_deallocated;
    printf("[MEMORY]: line %d: in %s \t\t| %d bytes freed\t\t| TOTAL BYTES ALLOCATED: %d\n", in_line, in_file, number_deallocated, internal_memory_manager_bytes_allocated);
}
