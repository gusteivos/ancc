#include "ancc.h"

NOTRET
void _error(
    const char *file,
    int line,
    int exit_status,
    const char *fmt,
    ...
    )
{

    fprintf(stderr, "\nError from FILE: %s on LINE: %d.\n\n", file, line);

	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	putc('\n', stderr);

	fflush(stderr);

	exit(exit_status);

}

void *guarantees_realloc(void *ptr, size_t old_size, size_t new_size)
{

    if (new_size == 0)
    {

        free(ptr);

        return NULL;

    }

    if (ptr == NULL)
    {

        return malloc(new_size);

    }

    if (new_size == old_size)
    {

        return ptr;

    }

    void *new_ptr = realloc(ptr, new_size);

    if (new_ptr == NULL)
    {

        new_ptr = malloc(new_size);

        if (new_ptr == NULL)
        {

            return NULL;

        }

        memcpy(new_ptr, ptr, old_size);

        free(ptr);

    }

    return new_ptr;

}
