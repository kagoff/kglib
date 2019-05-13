#include <assert.h>

#include "hash.h"

void
test_hash(void) {
    /***************************************************************************
     * Exercise all APIs correctly
     **************************************************************************/
    char* data = "data";
    char* found = NULL;
    int key = 0xFFFF;
    //TODO: use sprintf to generate data
    kghash_t H = hash_create(10);
    assert(H);
    assert(!hash_insert(H, (void*)data, key));
    assert(hash_count(H) == 1);
    assert(!hash_find(H, key, (void**)&found));
    assert(found == data);
    found = NULL;
    assert(!hash_remove(H, key, (void**)&found));
    assert(found == data);
    assert(hash_count(H) == 0);
    assert(!hash_destroy(&H));
    assert(!H);
}