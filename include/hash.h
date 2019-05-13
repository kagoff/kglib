#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct Hash* kghash_t;

kghash_t    hash_create     (size_t table_size);

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
 *  Prints the hash table top to bottom, showing the items sharing a key as a
 *  comma separate list.
 *
 *  INPUT:  None
 *  OUTPUT: None
 */
// void     hash_print_keys      (void);

#endif
