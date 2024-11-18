
#ifndef ANCC_H
#define ANCC_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

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

void *guarantees_realloc(void *ptr, size_t old_size, size_t new_size);

#endif/*ANCC_H*/
