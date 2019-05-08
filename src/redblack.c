#include"bst.h"

//******************************************************************************
//      STRUCTS
//******************************************************************************
typedef struct BSTnode* node_t;
struct BSTnode {
    int key;
    void* data;
    bool black;
    node_t parent;
    node_t left;
    node_t right;
};

struct BST {
    int count;
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
    N->black = FALSE;
    N->parent = parent;
    N->left = NULL;
    N->right = NULL;

    return N;
}

// Returns 1 on success
static int insert_rec (bst_t T, node_t root, int key, void* data)
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
        return insert_rec(T, root->left, key, data);
    }
    else if(key > root->key)
    {
        return insert_rec(T, root->right, key, data);
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

static void preorder_rec (node_t root, bst_func_t func)
{
    (*func)(root->key, &root->data);

    if(root->left)
        preorder_rec(root->left, func);
    if(root->right)
        preorder_rec(root->right, func);
}

static void inorder_rec (node_t root, bst_func_t func)
{
    if(root->left)
        inorder_rec(root->left, func);

    (*func)(root->key, &root->data);

    if(root->right)
        inorder_rec(root->right, func);
}

static void postorder_rec (node_t root, bst_func_t func)
{
    if(root->left)
        postorder_rec(root->left, func);
    if(root->right)
        postorder_rec(root->right, func);

    (*func)(root->key, &root->data);
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
    if(root && key == root->key)
        return root;

    if(!root)
        return NULL;

    if(key < root->key)
        return find_rec(root->left, key);
    else if(key > root->key)
        return find_rec(root->right, key);

    return NULL;
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
            //min->left = root->left;
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

//******************************************************************************
//      PUBLIC FUNCTIONS
//******************************************************************************
bst_t bst_create ()
{
    bst_t T = (bst_t)malloc(sizeof(struct BSTnode));
    T->root = NULL;
    T->count = 0;
    return T;
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
        N->black = TRUE;
        T->root = N;
        T->count++;
        return 0;
    }

    // Otherwise, recursively find a spot
    if(insert_rec(T, T->root, key, data))
    {
        T->count++;
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

    return 0;
}

void bst_preorder (bst_t T, bst_func_t func)
{
    if(!T || !T->root)
        return;

    preorder_rec(T->root, func);
}

void bst_inorder (bst_t T, bst_func_t func)
{
    if(!T || !T->root)
        return;

    inorder_rec(T->root, func);
}

void bst_postorder (bst_t T, bst_func_t func)
{
    if(!T || !T->root)
        return;

    postorder_rec(T->root, func);
}

void bst_levelorder (bst_t T, bst_func_t func)
{
    if(!T || !T->root)
        return;

    queue_t Q = queue_create();

    node_t current = NULL;
    queue_enqueue(Q, (void*)T->root);

    while(queue_count(Q) > 0)
    {
        queue_dequeue(Q, (void*)&current);
        (*func)(current->key, &current->data);

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
