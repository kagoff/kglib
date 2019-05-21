#include <assert.h>
#include <stdio.h>

#include "hash.h"

#define TEST_DATA_ARRAY_SIZE (2*TEST_TABLE_SIZE_SMALL)
#define TEST_TABLE_SIZE_SMALL 10
#define TEST_DEFAULT_KEY 0xFFFF
#define TEST_DATA_SIZE 512

void
test_hash(void)
{
    /***************************************************************************
     * Shared variables
     **************************************************************************/
    char* datum = "datum";
    char* found = NULL;
    int key = TEST_DEFAULT_KEY;
    char* data[TEST_DATA_ARRAY_SIZE];
    kghash_t H = NULL;

    /***************************************************************************
     * Exercise all APIs correctly
     **************************************************************************/
    H = hash_create(TEST_TABLE_SIZE_SMALL);
    assert(H);
    assert(!hash_insert(H, (void*)datum, key));
    assert(hash_count(H) == 1);
    assert(!hash_find(H, key, (void**)&found));
    assert(found == datum);
    found = NULL;
    assert(!hash_remove(H, key, (void**)&found));
    assert(found == datum);
    assert(hash_count(H) == 0);
    assert(!hash_destroy(&H));
    assert(!H);

    /***************************************************************************
     * hash_create tests
     **************************************************************************/
    H = NULL;
    H = hash_create(0);
    assert(!H);
    H = hash_create(0x7FFFFFFF);
    assert(!H);
    H = hash_create(TEST_TABLE_SIZE_SMALL);
    assert(H);

    /***************************************************************************
     * hash_insert tests
     **************************************************************************/
    assert(hash_insert(NULL, (void*)datum, key));
    assert(hash_insert(H, NULL, key));
    assert(!hash_count(H));
    for(int index = 0; index < TEST_DATA_ARRAY_SIZE; index++) {
        data[index] = malloc(TEST_DATA_SIZE * sizeof(char));
        sprintf(data[index], "data%d", index);
        assert(!hash_insert(H, (void*)data[index], index));
        assert(hash_count(H) == (index+1));
    }

    /***************************************************************************
     * hash_find tests
     **************************************************************************/
    found = NULL;
    assert(hash_find(NULL, 1, (void**)&found));
    assert(!found);
    assert(hash_find(H, 1, NULL));
    assert(hash_find(H, TEST_DEFAULT_KEY, (void**)&found));
    assert(!found);
    for(int index = 0; index < TEST_DATA_ARRAY_SIZE; index++) {
        assert(!hash_find(H, index, (void**)&found));
        assert(found == data[index]);
    }
    assert(hash_count(H) == TEST_DATA_ARRAY_SIZE);

    /***************************************************************************
     * hash_remove tests
     **************************************************************************/
    found = NULL;
    assert(hash_remove(NULL, 1, (void**)&found));
    assert(!found);
    assert(hash_remove(H, TEST_DEFAULT_KEY, (void**)&found));
    assert(!found);
    for(int index = (TEST_DATA_ARRAY_SIZE-1); index >= 0; index--) {
        assert(!hash_remove(H, index, (void**)&found));
        assert(found);
        assert(found == data[index]);
        free(data[index]);
        data[index] = NULL;
        assert(hash_count(H) == index);
    }
    assert(!hash_count(H));

    /***************************************************************************
     * hash_destroy tests
     **************************************************************************/
    kghash_t empty_hash = NULL;
    assert(hash_destroy(NULL));
    assert(hash_destroy(&empty_hash));
    assert(!hash_destroy(&H));
    assert(!H);
}