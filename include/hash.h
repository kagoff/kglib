#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct Hash* kghash_t;
typedef int (kghash_func_t)(void* data, int key, void* arg1, void* arg2);

/**
 *  Allocates a hash object and returns pointer to it.
 *
 *  INPUT:  None
 *  OUTPUT: Pointer to the allocated hash object data
 */
kghash_t    hash_create     (size_t table_size);

/**
 *  Frees a hash object and sets the hash data to NULL when complete. This
 *  does not free the actual data stored in the hash, so be careful not to
 *  lose memory here.
 *
 *  INPUT:  Pointer to hash object data pointer to free and reset to NULL
 *  OUTPUT: 0 on success
 *.         -1 on NULL argument
 */
int         hash_destroy    (kghash_t* H);

/**
 *  Inserts an element into the hash table.
 *
 *  INPUT:  Key and pointer to data
 *  OUTPUT: -1 if already in the list
 *          0 otherwise
 */
int         hash_insert     (kghash_t H, void* value, int key);

/**
 *  Removes an element out of the hash table, returning its data pointer.
 *
 *  INPUT:  Key to find, pointer to return the data pointer on
 *  OUTPUT: -1 if cannot be found
 *          0 otherwise
 */
int         hash_remove     (kghash_t H, int key, void** value);

/**
 *  Finds and returns an element given a key. Does not change any data nor the
 *  state of the hash table.
 *
 *  INPUT:  Key to find, pointer to return the data pointer on
 *  OUTPUT: -1 if cannot be found
 *          0 otherwise
 */
int         hash_find       (kghash_t H, int key, void** value);

/**
 *  Get the number of elements currently in the hash table.
 *
 *  INPUT:  Hash object pointer
 *  OUTPUT: Elements of hash table on success
 *          -1 on NULL pointer
 */
size_t      hash_count      (kghash_t H);

/**
 *  Performs the given function on each entry in the hash table, with no order
 *  guaranteed. If "func" returns nonzero on any element, this function will
 *  return that error code and set the optional "failed_entry" pointer if
 *  available. Note that this function will explicitly nullify the
 *  "failed_entry" pointer.
 *
 *  INPUT:  Hash object pointer, function pointer, two optional arguments, and
 *          optional failed entry pointer
 *  OUTPUT: 0 on success
 *          -1 on NULL pointer
 *          Return value from func on failed entry
 */
int         hash_for_each    (kghash_t H, kghash_func_t func, void* arg1,
                             void* arg2, void** failed_entry);

#endif
