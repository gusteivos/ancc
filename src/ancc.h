
#ifndef ANCC_H
#define ANCC_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

void error(const char *, ...);


#ifndef ANCC_NAME
#define ANCC_NAME "ancc"
#endif

#ifndef EXTERN
#define EXTERN extern
#endif
#ifndef STATIC
#define STATIC static
#endif
#ifndef INLINE
#define INLINE inline
#endif

#ifndef NOTRET
#define NOTRET
#endif
#ifndef UNUSED
#define UNUSED(x) x
#endif

NOTRET
void _error(
    const char *file,
    int line,
    int exit_status,
    const char *fmt,
    ...
    );

#define error_novarg(exit_status, fmt) _error(      \
    __FILE__,                                       \
    __LINE__,                                       \
    exit_status,                                    \
    fmt                                             \
    )

#define error(exit_status, fmt, ...) _error(        \
    __FILE__,                                       \
    __LINE__,                                       \
    exit_status,                                    \
    fmt,                                            \
    ##__VA_ARGS__                                   \
    )

void *guarantees_realloc(void *ptr, size_t old_size, size_t new_size);

#endif/*ANCC_H*/
