#include "hashfunc.h"

uint32_t Idjb2hashfunc(size_t size, void *data)
{

    uint32_t hash = IDJB2HASHFUNC_BASE;

    if (data != NULL)
    {

        unsigned char *src = data;

        size_t index = 0;

        for ( ; index < size; ++index)
        {

#if IDJB2HASHFUNC_FACTOR == 33
            hash = ((hash << 5) + hash) + src[index];
#else
            hash = (hash * IDJB2HASHFUNC_FACTOR) + src[index];
#endif

        }

    }

    return hash;

}

uint32_t Ifnv1ahashfunc(size_t size, void *data)
{

    uint32_t hash = IFNV1AHASHFUNC_BASE;

    if (data != NULL)
    {

        unsigned char *src = data;

        size_t index = 0;

        for ( ; index < size; ++index)
        {

            hash = (hash ^ (uint32_t)src[index]) * IFNV1AHASHFUNC_FACTOR;

        }

    }

    return hash;

}
