#include"hash.h"

#define MAX_TABLE_SIZE (1 << 10)

#define FNV_OFFSET 0xcbf29ce484222325
#define FNV_PRIME  0x100000001b3

//******************************************************************************
//      STRUCTS AND GLOBALS
//******************************************************************************
typedef struct Hash_Entry* hash_entry_t;
struct Hash_Entry {
    void* data;
    int key;
    hash_entry_t next;
};

struct Hash {
    hash_entry_t* table;
    size_t table_size;
    size_t count;
};

//******************************************************************************
//      PRIVATE FUNCTIONS
//******************************************************************************
static inline uint64_t hash_key (int key)
{
    uint64_t hash = FNV_OFFSET;
    uint8_t* key_byte;

    // FNV-1a hash algorithm
    for (uint64_t byte = 0; byte < sizeof(int); byte++) {
        hash = hash ^ key_byte[byte];
        hash = hash * FNV_PRIME;
    }

    return hash;
}

static hash_entry_t entry_create (void* data, int key)
{
    if(!data) {
        return NULL;
    }

    hash_entry_t entry = malloc(sizeof(struct Hash_Entry));
    entry->key = key;
    entry->data = data;
    entry->next = NULL;
    return entry;
}

static inline hash_entry_t find_entry (kghash_t H, int key, hash_entry_t* prev)
{
    if(!H) {
        return NULL;
    }

    // Find the index
    size_t index = hash_key(key) % H->table_size;
    hash_entry_t entry_slot = H->table[index];

    // Key not found
    if(!entry_slot)
        return NULL;

    // Walk the linked list to find matching entry
    hash_entry_t prev_slot;
    while(entry_slot && (entry_slot->key != key)) {
        prev_slot = entry_slot;
        entry_slot = entry_slot->next;
    }

    // Could not match the key with an existing element
    if(!entry_slot) {
        return NULL;
    }

    // For a remove, need to know the previous slot
    if(prev) {
        *prev = prev_slot;
    }

    return entry_slot;
}

//******************************************************************************
//      PUBLIC FUNCTIONS
//******************************************************************************
kghash_t hash_create (size_t table_size)
{
    if(table_size > MAX_TABLE_SIZE) {
        return NULL;
    }

    kghash_t H = malloc(sizeof(struct Hash));
    H->table = malloc(table_size * sizeof(hash_entry_t));
    H->table_size = table_size;
    H->count = 0;

    return H;
}

int hash_destroy (kghash_t* H_ptr)
{
    if(!H_ptr || !(*H_ptr)) {
        return -1;
    }

    kghash_t H = *H_ptr;
    for(uint64_t index = 0; index < MAX_TABLE_SIZE; index++) {
        if(H->table[index]) {
            ;// TODO:Walk list and free each element
        }
    }
    return 0;
}

int hash_insert (kghash_t H, void* data, int key)
{
    if(!H || !data) {
        return -1;
    }

    // Find the index
    size_t index = hash_key(key) % H->table_size;
    hash_entry_t entry_slot = H->table[index];

    // If the slot is empty, add it in
    if(!entry_slot) {
        H->table[index] = entry_create(data, key);
        if(!H->table[index]) {
            return -1;
        }
    } else { // Walk the linked list for next open slot
        hash_entry_t prev_slot;
        while(entry_slot) {
            prev_slot = entry_slot;
            entry_slot = entry_slot->next;
        }
        entry_slot = entry_create(data, key);
        if(!entry_slot) {
            return -1;
        }
        prev_slot->next = entry_slot;
    }

    return 0;
}

int hash_remove (kghash_t H, int key, void** data_ptr)
{
    if(!H || !data_ptr) {
        return -1;
    }

    // Find the entry
    hash_entry_t prev = NULL;
    hash_entry_t entry = find_entry(H, key, &prev);
    if(!entry || !prev) {
        return -1;
    }

    // Set return data and free the entry
    *data_ptr = entry->data;
    free(entry);
    prev->next = NULL;

    return 0;
}

int hash_find (kghash_t H, int key, void** data_ptr)
{
    if(!H || !data_ptr) {
        return -1;
    }

    // Find the entry
    hash_entry_t entry = find_entry(H, key, NULL);
    if(!entry) {
        return -1;
    }

    // Set the data
    *data_ptr = entry->data;
    return 0;
}

// void hash_print_keys(kghash_t H)
// {
//     kghash_t* entry;
//     int newline;
//     int i;
//     for(i = 0; i < SIZE_TABLE; i++)
//     {
//         newline = 0;
//         entry = h + i;
//         if(entry->inArray)
//         {
//             newline = 1;
//             printf("%d", entry->key);
//         }

//         while(entry->next)
//         {
//             newline = 1;
//             entry = entry->next;
//             printf(" ,%d", entry->key);
//         }

//         if(newline)
//             printf("\n");
//     }
// }
