#include"hash.h"

#define SIZE_TABLE 1021
#define P 31

//******************************************************************************
//      STRUCTS AND GLOBALS
//******************************************************************************
typedef struct Hash_Entry {
    int key;
    void* value;
    int inArray;
    struct Hash_Entry* next;
} hash_t;
static hash_t h[SIZE_TABLE];

//******************************************************************************
//      PRIVATE FUNCTIONS
//******************************************************************************
static int hash (int key)
{
    int index;

    index = (P * key) % SIZE_TABLE;

    return index; // this would be the result of the hashing
}

static hash_t* entry_create (int key, void* value)
{
    hash_t* entry = (hash_t*)malloc(sizeof(struct Hash_Entry));
    entry->key = key;
    entry->value = value;
    entry->next = NULL;
    entry->inArray = 0;

    return entry;
}

static hash_t* find_entry (int key, hash_t** prev)
{
    hash_t* entry = h + hash(key);
    *prev = NULL;

    while(entry && (key != entry->key))
    {
        *prev = entry;
        entry = entry->next;
    }

    return entry;
}

//******************************************************************************
//      PUBLIC FUNCTIONS
//******************************************************************************
int hash_insert (int key, void* value)
{
    // Starting location in the array
    hash_t* location = h + hash(key);

    // If the slot is empty, add it in
    if(!location->inArray)
    {
        location->key = key;
        location->value = value;
        location->inArray = 1;
        //CAUTION: purposefully not changing the next pointer
    }

    // Walk the linked list for empty next pointer
    else
    {
        while(location->next)
        {
            // Already in the list
            if(location->key == key)
                return -1;

            location = location->next;
        }

        if(location->key == key)
            return -1;

        hash_t* new = entry_create(key, value);
        location->next = new;
    }

    return 0;
}

int hash_remove (int key, void** value)
{
    hash_t* prev;
    hash_t* entry = find_entry(key, &prev);

    // Key not found
    if(!entry || !(prev || entry->inArray))
        return -1;

    if(value)
        *value = entry->value;

    // In the pre-allocated array
    if(!prev)
        entry->inArray = 0;

    // Part of the linked list
    else
    {
        prev->next = entry->next;
        free(entry);
    }

    return 0;
}

int hash_find (int key, void** value)
{
    hash_t* prev;
    hash_t* entry = find_entry(key, &prev);

    // Couldn't find it
    if(!entry || !(prev || entry->inArray))
        return -1;

    // Assigns return value only if pointer exists
    if(value)
        *value = entry->value;

    return 0;
}

void hash_print()
{
    hash_t* entry;
    int newline;
    int i;
    for(i = 0; i < SIZE_TABLE; i++)
    {
        newline = 0;
        entry = h + i;
        if(entry->inArray)
        {
            newline = 1;
            printf("%d", entry->key);
        }

        while(entry->next)
        {
            newline = 1;
            entry = entry->next;
            printf(" ,%d", entry->key);
        }

        if(newline)
            printf("\n");
    }
}
