#include <assert.h>

#include "queue.h"

void test_queue()
{
    queue_s* Q = queue_create();

    /***************************************************************************
     * Simple test
     **************************************************************************/
    int* front;
    int a = 1;
    // Add element
    assert(!queue_enqueue(Q, &a));
    // Remove and check it
    assert(!queue_dequeue(Q, (void*)&front));
    assert(*front == a);
    // Check that dequeue returns error when count it 0
    assert(queue_count(Q) == 0);

    /***************************************************************************
     * Multiple insertions and deletions
     **************************************************************************/
    int b = 2;
    int c = 3;
    // Add 3 unique elements
    assert(!queue_enqueue(Q, &a));
    assert(!queue_enqueue(Q, &b));
    assert(!queue_enqueue(Q, &c));
    // Dequeue and check each one
    assert(queue_count(Q) == 3);
    assert(!queue_dequeue(Q, (void*)&front));
    assert(*front == a);
    assert(queue_count(Q) == 2);
    assert(!queue_dequeue(Q, (void*)&front));
    assert(*front == b);
    assert(queue_count(Q) == 1);
    assert(!queue_dequeue(Q, (void*)&front));
    assert(*front == c);
    assert(queue_count(Q) == 0);

    /***************************************************************************
     * Error condition checking
     **************************************************************************/
    // Single enqueue, triple dequeue
    assert(!queue_enqueue(Q, &c));
    assert(!queue_dequeue(Q, NULL));
    assert(queue_dequeue(Q, NULL));
    assert(queue_dequeue(Q, (void*)&front));
    // Try to dequeue a NULL queue object
    assert(!queue_enqueue(Q, &c));
    assert(queue_dequeue(NULL, (void*)&front));
    // Test cleanup
    assert(!queue_dequeue(Q, (void*)&front));
    assert(queue_count(Q) == 0);

    /***************************************************************************
     * TODO: scale checking and more boundary conditions
     **************************************************************************/

    /***************************************************************************
     * Queue destroy test
     **************************************************************************/
    assert(!queue_destroy(&Q));
    assert(NULL == Q);
}