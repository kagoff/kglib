#ifndef HASH_H
#define HASH_H

#include<stdio.h>
#include<stdlib.h>

/**
 *  Inserts an element into the hash table.
 *
 *  INPUT:  Key and pointer to data
 *  OUTPUT: -1 if already in the list
 *          0 otherwise
 */
int     hash_insert     (int key, void* value);

/**
 *  Removes an element out of the hash table, returning its data pointer.
 *
 *  INPUT:  Key to find, pointer to return the data pointer on
 *  OUTPUT: -1 if cannot be found
 *          0 otherwise
 */
int     hash_remove     (int key, void** value);

/**
 *  Finds and returns an element given a key. Does not change any data nor the
 *  state of the hash table.
 *
 *  INPUT:  Key to find, pointer to return the data pointer on
 *  OUTPUT: -1 if cannot be found
 *          0 otherwise
 */
int     hash_find       (int key, void** value);

/**
 *  Prints the hash table top to bottom, showing the items sharing a key as a
 *  comma separate list.
 *
 *  INPUT:  None
 *  OUTPUT: None
 */
void    hash_print      (void);

#endif
