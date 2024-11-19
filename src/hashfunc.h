
#ifndef HASHFUNC_H
#define HASHFUNC_H

#include "ancc.h"

#include <stdint.h>
#include <stddef.h>

typedef uint32_t (*Ihashfunc_t)(size_t, void *);

#ifndef IDJB2HASHFUNC_BASE
#define IDJB2HASHFUNC_BASE 5381
#endif

#ifndef IDJB2HASHFUNC_FACTOR
#define IDJB2HASHFUNC_FACTOR 33
#endif

uint32_t Idjb2hashfunc(size_t size, void *data);

#ifndef IFNV1AHASHFUNC_BASE
#define IFNV1AHASHFUNC_BASE 0x811c9dc5
#endif

#ifndef IFNV1AHASHFUNC_FACTOR
#define IFNV1AHASHFUNC_FACTOR 0x1000193
#endif

uint32_t Ifnv1ahashfunc(size_t size, void *data);

#endif/*HASHFUNC_H*/
