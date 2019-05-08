#include "stack.h"

//******************************************************************************
//      STRUCTS
//******************************************************************************
typedef struct Node* node_t;
struct Node {
    void* data;
    node_t next;
};

struct Stack {
    int size;
    node_t root;
};

//******************************************************************************
//      LOCAL FUNCTIONS
//******************************************************************************
static node_t node_create (void* new_data) {
    node_t return_node = (node_t)malloc(sizeof(struct Node));
    return_node->data = new_data;
    return_node->next = NULL;
    return return_node;
}

//******************************************************************************
//      PUBLIC FUNCTIONS
//******************************************************************************
stack_t stack_create() {
    stack_t return_stack = (stack_t)malloc(sizeof(struct Stack));
    return_stack->size = 0;
    return_stack->root = NULL;
    return return_stack;
}

int stack_destroy(stack_t S) {

    if(!S)
        return -1;

    while(S->root) {
        node_t next_node = S->root->next;
        free(S->root);
        S->root = next_node;
    }
    free(S);
    return 0;
}

int stack_push(stack_t S, void* data)
{
    if(!S || !data)
        return -1;

    node_t new_node = node_create(data);
    new_node->next = S->root;
    S->root = new_node;

    S->size++;
    return 0;
}

int stack_pop(stack_t S, void** return_data)
{
    if(!S)
        return -1;

    if(return_data)
        *return_data = S->root->data;

    node_t new_root = S->root->next;
    free(S->root);
    S->root = S->root->next;

    S->size--;
    return 0;
}

int stack_count(stack_t S)
{
    if(!S)
        return -1;

    return S->size;
}

int stack_is_empty (stack_t S)
{
    if(!S)
        return -1;

    return (S->size == 0) ? 1 : 0;
}
