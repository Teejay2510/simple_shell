#include "shell.h"

/**
 * bfree - Frees a pointer and sets it to NULL.
 * @ptr: Address of the pointer to free.
 *
 * Return: 1 if freed, 0 if the pointer was already NULL.
 */
int bfree(void **ptr)
{
    if (ptr != NULL && *ptr != NULL)
    {
        free(*ptr);
        *ptr = NULL;
        return 1; // Freed successfully
    }
    return 0; // Pointer was already NULL or invalid
}

