#include "queue.h"

/**
 * DESIGN:
 * enqueue->tail->next->...->next->head->dequeue
 *              <-prev<-...<-prev<-head
 */

//******************************************************************************
//      STRUCTS
//******************************************************************************
typedef struct Node* node_t;
struct Node {
    void* data;
    node_t next;
    node_t prev;
};

struct Queue {
    int size;
    node_t head;
    node_t tail;
};

//******************************************************************************
//      PRIVATE FUNCTIONS
//******************************************************************************
static node_t node_create (void* new_data)
{
    node_t N = malloc(sizeof(struct Node));
    N->data = new_data;
    N->next = NULL;
    N->prev = NULL;
    return N;
}

//******************************************************************************
//      PUBLIC FUNCTIONS
//******************************************************************************
kgqueue_t queue_create()
{
    kgqueue_t Q = malloc(sizeof(struct Queue));
    Q->size = 0;
    Q->head = NULL;
    Q->tail = NULL;
    return Q;
}

int queue_destroy(kgqueue_t* Q_ptr)
{
    if(!Q_ptr || !(*Q_ptr))
        return -1;

    kgqueue_t Q = *Q_ptr;

    // Iterate and free all elements in the queue
    while(Q->tail) {
        node_t next_node = Q->tail->next;
        free(Q->tail);
        Q->tail = next_node;
    }
    free(Q);
    *Q_ptr = NULL;
    return 0;
}

int queue_enqueue(kgqueue_t Q, void* data)
{
    if(!Q || !data)
        return -1;

    node_t N = node_create(data);

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

int queue_front(kgqueue_t Q, void** return_data)
{
    if(!Q || !(return_data) || !queue_count(Q))
        return -1;

    *return_data = Q->head->data;
    return 0;
}

int queue_dequeue(kgqueue_t Q, void** return_data)
{
    if(!Q || !queue_count(Q))
        return -1;

    // Dequeue at the head
    if(return_data)
        *return_data = Q->head->data;

    // Move the head to be the next in line element
    node_t new_head = Q->head->prev;
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

int queue_count(kgqueue_t Q)
{
    if(!Q)
        return -1;

    return Q->size;
}
