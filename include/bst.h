#ifndef BST_H
#define BST_H

#include<stdio.h>
#include<stdlib.h>
#include"stack.h"
#include"queue.h"

typedef struct BST* bst_t;
typedef void (*bst_func_t)(int key, void** data, void* arg1, void* arg2);

//******************************************************************************
//      BASIC TREE OPERATIONS
//******************************************************************************
/*
    Creates an empty tree. Allocates memory on the heap which must be removed
    by calling destroy! Tree does not support duplicates.

    INPUT:  None
    OUTPUT: Pointer to an empty tree
*/
bst_t   bst_create      (void);

/*
    Creates a new tree and adds all the elements in level order (to avoid extra
    balancing) from the given tree.

    INPUT:  Pointer to BST with some nodes
    OUTPUT: NULL if input tree does not exist or is empty
            Pointer to new tree otherwise
*/
bst_t   bst_duplicate      (bst_t T);

/*
    Destroys a tree recursively. Must be called to clean up memory!

    INPUT:  Tree object
    OUTPUT: -1 if tree doesn't exist
            0 otherwise
*/
int     bst_destroy     (bst_t T);

/*
    Inserts a new element into the tree. Does not support duplicates. NULL data
    pointers are allowed.

    INPUT:  Tree object, key, pointer to data
    OUTPUT: -1 if tree doesn't exist or if key already in tree
            0 otherwise
*/
int     bst_insert      (bst_t T, int key, void* data);

/*
    Removes an element from the tree, assigning a pointer to its data pointer.
    NULL data pointers are allowed and will not be assigned.

    INPUT:  Tree object, key, pointer to data pointer for return
    OUTPUT: -1 if tree doesn't exist or key is not found
            0 otherwise
*/
int     bst_remove      (bst_t T, int key, void** data);

/*
    Finds and assigns a pointer to the data pointer of the given key.
    NULL data pointer arguments are NOT allowed!

    INPUT:  Tree object, key, pointer to data pointer for return
    OUTPUT: -1 if tree doesn't exist, key is not found, or data argument is NULL
            0 otherwise
*/
int     bst_find        (bst_t T, int key, void** data);

//******************************************************************************
//      TRAVERSALS
//          - All traversals operate the same way, by iterating over the
//              elements in the order indicated and performing the function
//              passed in as an arugment.
//          - The first three are recursive, whereas levelorder uses a queue.
//          - The function is only allowed to change the data, not the key. This
//              avoids issues where the user could cause the tree to not be in
//              sorted order anymore.
//******************************************************************************
void    bst_preorder    (bst_t T, bst_func_t func, void* arg1, void* arg2);
void    bst_inorder     (bst_t T, bst_func_t func, void* arg1, void* arg2);
void    bst_postorder   (bst_t T, bst_func_t func, void* arg1, void* arg2);
void    bst_levelorder  (bst_t T, bst_func_t func, void* arg1, void* arg2);

//******************************************************************************
//      OTHER USEFUL FUNCTIONS
//******************************************************************************
/*
    Returns the key of the least common ancestor in O(log n) time.

    INPUT:  Tree object, the keys of which to compare their ancestors
    OUTPUT: -1 if tree or either key doesn't exist
            0 otherwise
*/
int     bst_lca         (bst_t T, int data1, int data2);

#endif
