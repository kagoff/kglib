#ifndef QUEUE_H
#define QUEUE_H

#include<stdlib.h>

typedef struct Queue* kgqueue_t;

/**
 *  Allocates a queue object and returns pointer to it.
 *
 *  INPUT:  None
 *  OUTPUT: Pointer to the allocated queue object data
 */
kgqueue_t queue_create    (void);

/**
 *  Frees a queue object and sets the queue data to NULL when complete. This
 *  does not free the actual data stored in the queue, so be careful not to
 *  lose memory here.
 *
 *  INPUT:  Pointer to queue object data pointer to free and reset to NULL
 *  OUTPUT: 0 on success
 *.         -1 on NULL arguments
 */
int     queue_destroy   (kgqueue_t* Q_ptr);

/**
 *  Enqueue a data object in the back of the queue.
 *
 *  INPUT:  Queue object pointer
 *          Data to enqueue
 *  OUTPUT: 0 on success
 *          -1 on NULL arguments
 */
int     queue_enqueue   (kgqueue_t Q, void* data);

/**
 *  Peek at the front element from the queue, but do not dequeue it.
 *
 *  INPUT:  Queue object pointer
 *          Address of data object pointer to return on
 *  OUTPUT: 0 on success
 *          -1 on NULL arguments
 */
int     queue_front   (kgqueue_t Q, void** return_data);

/**
 *  Remove the front element from the queue. When return_data is NULL, still
 *  dequeues the front element. Careful not to lose memory here!
 *
 *  INPUT:  Queue object pointer
 *          Address of data object pointer to return on
 *  OUTPUT: 0 on success
 *          -1 on NULL queue
 */
int     queue_dequeue   (kgqueue_t Q, void** return_data);

/**
 *  Get the number of elements currently in the queue.
 *
 *  INPUT:  Queue object pointer
 *  OUTPUT: Elements of queue on success
 *          -1 on NULL pointer
 */
int     queue_count     (kgqueue_t Q);

#endif
