#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "hash.h"

#define TEST_DATA_ARRAY_SIZE (2*TEST_TABLE_SIZE_SMALL)
#define TEST_TABLE_SIZE_SMALL 10
#define TEST_DEFAULT_KEY 0xFFFF
#define TEST_DATA_SIZE 512
#define TEST_HASH_FOR_EACH_FIND_ELEMENT "data5"
#define TEST_HASH_FOR_EACH_FIND_INDEX 5

/**
 * Helpers to check the hash_for_each API function
 */
static int
hash_for_each_find (void* data, int key, void* arg1, void* arg2) {
    if(!data) {
        return -2;
    }
    int result = strncmp((char*)data,
                    TEST_HASH_FOR_EACH_FIND_ELEMENT,
                    sizeof(TEST_HASH_FOR_EACH_FIND_ELEMENT));
    if(result == 0) {
        return -1;
    }
    return 0;
}
static int
hash_for_each_args (void* data, int key, void* arg1, void* arg2) {
    if(!data || !arg1 || !arg2) {
        return -1;
    }
    return 0;
}
static int
hash_for_each_print_key (void* data, int key, void* arg1, void* arg2) {
    printf("%d\n", key);
    return 0;
}

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
     * hash_for_each tests
     **************************************************************************/
    assert(hash_for_each(H, hash_for_each_find, NULL, NULL, (void**)&found));
    assert(found == data[TEST_HASH_FOR_EACH_FIND_INDEX]);
    int arg1, arg2;
    assert(!hash_for_each(H, hash_for_each_args, &arg1, &arg2, (void**)&found));
    assert(!found);
    // TODO: make a print test that self checks and doesn't really print
    // assert(!hash_for_each(H, hash_for_each_print_key, NULL, NULL,
    //        (void**)&found));

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