#include "queue.h"

/**
 * DESIGN:
 * enqueue->tail->next->...->next->head->dequeue
 *              <-prev<-...<-prev<-head
 */

//******************************************************************************
//      STRUCTS
//******************************************************************************
typedef struct node node_s;
struct node {
    void* data;
    node_s* next;
    node_s* prev;
};

struct queue {
    int size;
    node_s* head;
    node_s* tail;
};

//******************************************************************************
//      PRIVATE FUNCTIONS
//******************************************************************************
static node_s* node_create (void* new_data)
{
    node_s* N = malloc(sizeof(node_s));
    N->data = new_data;
    N->next = NULL;
    N->prev = NULL;
    return N;
}

//******************************************************************************
//      PUBLIC FUNCTIONS
//******************************************************************************
queue_s* queue_create()
{
    queue_s* Q = malloc(sizeof(queue_s));
    Q->size = 0;
    Q->head = NULL;
    Q->tail = NULL;
    return Q;
}

int queue_destroy(queue_s** Q_ptr)
{
    if(!Q_ptr || !(*Q_ptr))
        return -1;

    queue_s* Q = *Q_ptr;

    // Iterate and free all elements in the queue
    while(Q->tail) {
        node_s* next_node = Q->tail->next;
        free(Q->tail);
        Q->tail = next_node;
    }
    free(Q);
    *Q_ptr = NULL;
    return 0;
}

int queue_enqueue(queue_s* Q, void* data)
{
    if(!Q || !data)
        return -1;

    node_s* N = node_create(data);

    // If an element is present, readjust the head's previous pointer
    if(!queue_count(Q))
        Q->head = N;
    else
        Q->tail->prev = N;

    // Push onto the head of the list
    N->next = Q->tail;
    Q->tail = N;

    Q->size++;
    return 0;
}

int queue_dequeue(queue_s* Q, void** return_data)
{
    if(!Q || !queue_count(Q))
        return -1;

    // Dequeue at the tail
    if(return_data)
        *return_data = Q->head->data;

    // Move the tail to be the next element
    node_s* new_head = Q->head->prev;
    if(queue_count(Q) > 1)
    {
        new_head->next = NULL;
        free(Q->head);
        Q->head = new_head;
    }
    // This was the last element, reset the queue
    else {
        free(Q->head);
        Q->head = Q->tail = NULL;
    }

    Q->size--;
    return 0;
}

int queue_count(queue_s* Q)
{
    if(!Q)
        return -1;

    return Q->size;
}
