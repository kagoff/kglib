#include"bst.h"

#define MAX(x,y) ( (x) > (y) ? (x) : (y) )

//******************************************************************************
//      STRUCTS
//******************************************************************************
typedef struct BSTnode* node_t;
struct BSTnode {
    int key;
    void* data;
    int diff;
    node_t parent;
    node_t left;
    node_t right;
};

struct BST {
    int count;
    void* arg1;
    void* arg2;
    bst_func_t func;
    node_t root;
};

//******************************************************************************
//      LOCAL FUNCTIONS
//******************************************************************************
static node_t node_create(int key, void* data, node_t parent)
{
    node_t N = (node_t)malloc(sizeof(struct BSTnode));
    N->key = key;
    N->data = data;
    N->diff = 0;
    N->parent = parent;
    N->left = NULL;
    N->right = NULL;

    return N;
}

// Returns 1 on success
static int insert_rec (node_t root, int key, void* data)
{
    if(!root || key == root->key)
        return 0;

    // Try to attach to self
    if(!root->left && (key < root->key))
    {
        node_t N = node_create(key, data, root);
        root->left = N;
        return 1;
    }
    else if(!root->right && (key > root->key))
    {
        node_t N = node_create(key, data, root);
        root->right = N;
        return 1;
    }

    // Recursively try left and right
    else if(key < root->key)
    {
        return insert_rec(root->left, key, data);
    }
    else if(key > root->key)
    {
        return insert_rec(root->right, key, data);
    }

    // Should not reach this line unless already in the tree
    return 0;
}

static void destroy_rec (node_t root)
{
    // Recursively delete left and right
    if(root->left)
        destroy_rec(root->left);
    if(root->right)
        destroy_rec(root->right);

    // Remove current node
    free(root);
}

static void preorder_rec (bst_t T, node_t root)
{
    (*T->func)(root->key, &root->data, T->arg1, T->arg2);

    if(root->left)
        preorder_rec(T, root->left);
    if(root->right)
        preorder_rec(T, root->right);
}

static void inorder_rec (bst_t T, node_t root)
{
    if(root->left)
        inorder_rec(T, root->left);

    (*T->func)(root->key, &root->data, T->arg1, T->arg2);

    if(root->right)
        inorder_rec(T, root->right);
}

static void postorder_rec (bst_t T, node_t root)
{
    if(root->left)
        postorder_rec(T, root->left);
    if(root->right)
        postorder_rec(T, root->right);

    (*T->func)(root->key, &root->data, T->arg1, T->arg2);
}

static void find_path (node_t root, stack_t S, int key)
{
    if(!root || !S)
        return;

    stack_push( S, (void*)&(root->key) );

    if(key < root->key)
        find_path(root->left, S, key);
    else if (key > root->key)
        find_path(root->right, S, key);
    else
        return;
}

static node_t find_rec (node_t root, int key)
{
    if(!root)
        return NULL;

    if(key < root->key)
        return find_rec(root->left, key);
    else if(key > root->key)
        return find_rec(root->right, key);
    else
        return root;
}

static node_t find_min (node_t root)
{
    node_t min = root;

    while(min->left)
        min = min->left;

    return min;
}

static node_t delete_rec (node_t root, int key)
{
    if(!root)
        return NULL;

    // Not match, look right, return root (after else)
    if(key > root->key)
        root->right = delete_rec(root->right, key);

    // Not match, look left, return root (after else)
    else if(key < root->key)
        root->left = delete_rec(root->left, key);

    // Key matches
    else
    {

        // No children
        if(!root->left && !root->right)
        {
            free(root);
            return NULL;
        }

        // 1 child
        else if(root->left && !root->right)
        {
            node_t left = root->left;
            node_t parent = root->parent;
            *root = *left;
            root->parent = parent;
            free(left);
        }
        else if(root->right && !root->left)
        {
            node_t right = root->right;
            node_t parent = root->parent;
            *root = *root->right;
            root->parent = parent;
            free(right);
        }

        // 2 children
        else
        {
            node_t min = find_min(root->right);
            node_t parent = root->parent;
            *root = *min;
            root->right = delete_rec(root->right, min->key);
            root->parent = parent;
        }
    }

    return root;
}

static void left_rotate(bst_t T, node_t x)
{
    node_t right = x->right;
    x->right = right->left;

    if(right->left)
        right->left->parent = x;

    node_t parent = x->parent;
    right->parent = parent;
    if(parent)
    {
        if(x == parent->left)
            parent->left = right;
        else
            parent->right = right;
    }
    else
        T->root = right;

    right->left = x;
    x->parent = right;
}

static void right_rotate(bst_t T, node_t x)
{
    node_t left = x->left;
    x->left = left->right;

    if(left->right)
        left->right->parent = x;

    node_t parent = x->parent;
    left->parent = parent;
    if(parent)
    {
        if(x == parent->left)
            parent->left = left;
        else
            parent->right = left;
    }
    else
        T->root = left;

    left->right = x;
    x->parent = left;
}

// returns height
static int avl_fix (bst_t T, node_t root)
{
    if(!root)
        return -1;

    int left = avl_fix(T, root->left);
    int right = avl_fix(T, root->right);

    int diff = root->diff = (right-left);

    // Right heavy
    if(diff > 1)
    {
        // Right child is right heavy or balanced
        if(root->right->diff >= 0)
        {
            left_rotate(T, root);
        }
        // Right child is left heavy
        else
        {
            right_rotate(T, root->right);
            left_rotate(T, root);
        }
    }
    // Left heavy
    else if (diff < -1)
    {
        // Left child is right heavy or balanced
        if(root->left->diff <= 0)
        {
            right_rotate(T, root);
        }
        // Left child is left heavy
        else
        {
            left_rotate(T, root->left);
            right_rotate(T, root);
        }
    }

    return MAX(left,right) + 1;
}

//******************************************************************************
//      PUBLIC FUNCTIONS
//******************************************************************************
bst_t bst_create ()
{
    bst_t T = (bst_t)malloc(sizeof(struct BST));
    T->root = NULL;
    T->arg1 = T->arg2 = T->func = NULL;
    T->count = 0;
    return T;
}

bst_t bst_duplicate(bst_t T)
{
    if(!T || !T->root)
        return NULL;

    bst_t newT = (bst_t)malloc(sizeof(struct BST));
    newT->root = NULL;
    newT->count = 0;

    // Level order algorithm from below
    queue_t Q = queue_create();
    node_t current = NULL;
    queue_enqueue(Q, (void*)T->root);
    while(queue_count(Q) > 0)
    {
        queue_dequeue(Q, (void*)&current);
        bst_insert(newT, current->key, current->data);
        if(current->left)
            queue_enqueue(Q, (void*)current->left);
        if(current->right)
            queue_enqueue(Q, (void*)current->right);
    }
    queue_destroy(Q);

    return newT;
}

int bst_destroy (bst_t T)
{
    if(!T)
        return -1;

    if(T->root)
        destroy_rec(T->root);

    free(T);

    return 0;
}

int bst_insert (bst_t T, int key, void* data)
{
    if(!T)
        return -1;

    // If there is no root yet, set the root to new item
    if(!T->root)
    {
        node_t N = node_create(key, data, NULL);
        T->root = N;
        T->count++;
        return 0;
    }

    // Otherwise, recursively find a spot
    if(insert_rec(T->root, key, data))
    {
        T->count++;
        avl_fix(T, T->root);
        return 0;
    }

    // Already in the tree
    else
        return -1;
}

int bst_find (bst_t T, int key, void** data)
{
    if(!T || !T->root)
        return -1;

    node_t N = find_rec(T->root, key);

    if(!N)
        return -1;

    if(data)
        *data = N->data;

    return 0;
}

int bst_remove (bst_t T, int key, void** data)
{
    if(!T || !T->root)
        return -1;

    node_t N = find_rec(T->root, key);

    if(!N)
        return -1;

    if(data)
        *data = N->data;

    T->root = delete_rec(T->root, key);
    avl_fix(T, T->root);

    return 0;
}

void bst_preorder (bst_t T, bst_func_t F, void* A1, void* A2)
{
    if(!T || !T->root || !F)
        return;

    T->func = F;
    T->arg1 = A1;
    T->arg2 = A2;
    preorder_rec(T, T->root);
}

void bst_inorder (bst_t T, bst_func_t F, void* A1, void* A2)
{
    if(!T || !T->root || !F)
        return;

    T->func = F;
    T->arg1 = A1;
    T->arg2 = A2;
    inorder_rec(T, T->root);
}

void bst_postorder (bst_t T, bst_func_t F, void* A1, void* A2)
{
    if(!T || !T->root || !F)
        return;

    T->func = F;
    T->arg1 = A1;
    T->arg2 = A2;
    postorder_rec(T, T->root);
}

void bst_levelorder (bst_t T, bst_func_t F, void* A1, void* A2)
{
    if(!T || !T->root || !F)
        return;

    queue_t Q = queue_create();

    node_t current = NULL;
    queue_enqueue(Q, (void*)T->root);

    while(queue_count(Q) > 0)
    {
        queue_dequeue(Q, (void*)&current);
        (*F)(current->key, &current->data, A1, A2);

        if(current->left)
            queue_enqueue(Q, (void*)current->left);
        if(current->right)
            queue_enqueue(Q, (void*)current->right);
    }

    queue_destroy(Q);
}

int bst_lca (bst_t T, int key1, int key2)
{
    if(!T)
        return -1;

    // Quick check if the elements are the same
    if(key1 == key2)
        return key1;

    // Store the paths to each node in separate stacks
    stack_t S1 = stack_create();
    stack_t S2 = stack_create();
    find_path(T->root, S1, key1);
    find_path(T->root, S2, key2);

    // If either of the stacks are empty, the node did not exist
    if(stack_is_empty(S1) || stack_is_empty(S2))
    {
        stack_destroy(S1);
        stack_destroy(S2);
        return -1;
    }

    // Store the top of each stack as they are popped off
    int *top1, *top2;
    top1 = &key1;
    top2 = &key2;

    int count1 = stack_count(S1);
    int count2 = stack_count(S2);

    // Pop off the longer stack until they are of equal length
    while(count1 != count2)
    {
        if(count1 > count2)
        {
            stack_pop(S1, (void*)&top1);
            count1 = stack_count(S1);
        }
        else
        {
            stack_pop(S2, (void*)&top2);
            count2 = stack_count(S2);
        }
    }

    // Continue popping until the elements match up or run out of elements
    while(*top1 != *top2
        && stack_count(S1) > 0
        && stack_count(S2) > 0)
    {
        stack_pop(S1, (void*)&top1);
        stack_pop(S2, (void*)&top2);
    }

    // If the top value matches, return it
    int return_value;
    if(*top1 == *top2)
        return_value = *top1;
    else
        return_value = -1;

    // Memory cleanup and return
    stack_destroy(S1);
    stack_destroy(S2);
    return return_value;
}
