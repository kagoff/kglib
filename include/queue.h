#ifndef QUEUE_H
#define QUEUE_H

#include<stdlib.h>

typedef struct queue queue_s;

/**
 *  Allocates a queue object and returns pointer to it.
 *
 *  INPUT:  None
 *  OUTPUT: Pointer to the allocated queue object data
 */
queue_s* queue_create    (void);

/**
 *  Allocates a queue object and returns pointer to it. Sets the queue data
 *  to NULL when complete.
 *
 *  INPUT:  Pointer to queue object data pointer to free and reset to NULL
 *  OUTPUT: 0 on success
 *.         -1 on NULL arguments
 */
int     queue_destroy   (queue_s** Q_ptr);

/**
 *  Enqueue a data object in the back of the queue.
 *
 *  INPUT:  Queue object pointer
 *          Data to enqueue
 *  OUTPUT: 0 on success
 *          -1 on NULL arguments
 */
int     queue_enqueue   (queue_s* Q, void* data);

/**
 *  Remove the front element from the queue. When return_data is NULL, still
 *  dequeues the front element. Careful not to lose memory here!
 *
 *  INPUT:  Queue object pointer
 *          Address of data object pointer to return on
 *  OUTPUT: 0 on success
 *          -1 on NULL arguments
 */
int     queue_dequeue   (queue_s* Q, void** return_data);

/**
 *  Get the number of elements currently in the queue.
 *
 *  INPUT:  Queue object pointer
 *  OUTPUT: Elements of queue on success
 *          -1 on NULL pointer
 */
int     queue_count     (queue_s* Q);

#endif
