
#ifndef ANCC_H
#define ANCC_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

#ifndef ANCC_NAME
#define ANCC_NAME "ancc"
#endif

#ifndef EXTERN
#define EXTERN extern
#endif
#ifndef INLINE
#define INLINE inline
#endif
#ifndef REGISTER
#define REGISTER register
#endif
#ifndef RESTRICT
#define RESTRICT restrict
#endif
#ifndef STATIC
#define STATIC static
#endif
#ifndef VOLATILE
#define VOLATILE volatile
#endif

#ifndef NOTRET
#define NOTRET
#endif
#ifndef UNUSED
#define UNUSED(x) x
#endif

#define ANCC_STDC89 89
#define ANCC_STDC99 99

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

#ifndef _WARNING_MINIMUM_LEVEL
#define _WARNING_MINIMUM_LEVEL 0
#endif

EXTERN
int _warning_minimum_level;

#ifndef _WARNING_MAXIMUM_LEVEL
#define _WARNING_MAXIMUM_LEVEL 127
#endif

EXTERN
int _warning_maximum_level;

void _warning(
    const char *file,
    int line,
    int level,
    const char *fmt,
    ...
    );

#define warning_novarg(level, fmt) _warning(        \
    __FILE__,                                       \
    __LINE__,                                       \
    level,                                          \
    fmt                                             \
    )

#define warning(level, fmt, ...) _warning(          \
    __FILE__,                                       \
    __LINE__,                                       \
    level,                                          \
    fmt,                                            \
    ##__VA_ARGS__                                   \
    )

void *guarantees_realloc(
	void *ptr,
	size_t old_size,
	size_t new_size
	);

char *duplicate_string(const char *str);

#endif/*ANCC_H*/
