#ifndef HEAP_H
#define HEAP_H

#include<stdio.h>
#include<stdlib.h>

typedef struct Heap* heap_t;
enum Type {MINHEAP = 0, MAXHEAP = 1};

/*
    Creates a min or max heap (priority queue). Allocates memory dynamically,
    so heap_destroy() must be called to avoid memory leaks.

    INPUT:  MAXHEAP or MINHEAP
    OUTPUT: Pointer to a priority queue in memory
*/
heap_t  heap_create     (enum Type t);

/*
    Builds a min or max heap (priority queue). Allocates memory dynamically,
    so heap_destroy() must be called to avoid memory leaks. Unlike the create
    function, which returns an empty heap, this function takes arrays to the
    data to be stored and their associated priority to build the heap quickly.

    INPUT:  MAXHEAP or MINHEAP, pointers to priority-data pairs, num of elements
    OUTPUT: Pointer to a priority queue in memory, already built
            NULL on failure, NULL inputs, or bad count
*/
heap_t  heap_build      (enum Type t, int* priorities, void** data, int count);

/*
    Deletes or frees all memory associated with the heap passed in.

    INPUT:  Pointer to heap
    OUTPUT: -1 if heap does not exist
            0 otherwise
*/
int     heap_destroy    (heap_t H);

/*
    Inserts an element into the heap based on the priority. Note that if data is
    NULL, the heap will still allow the insertion.

    INPUT:  Pointer to heap, priority value, and pointer to data to store
    OUTPUT: -1 if heap does not exist
            -2 if size of heap overflows MAX_INT
            0 otherwise
*/
int     heap_push       (heap_t H, int priority, void* data);

/*
    Removes the top element (either the max or the min) in the heap. If the data
    pointer passed in is NULL, the function will still remove the element but
    will not attempt to assign the data.

    INPUT:  Pointer to heap, double pointer to be assigned to data at top
    OUTPUT: -1 if heap does not exist or heap is empty
            0 otherwise
*/
int     heap_pop        (heap_t H, void** data);

/*
    This function is great to avoid sifting up.
    Use this over a pop/push combo when possible.

    INPUT:  Pointer to heap, new priority, new data, and pointer to return root
    OUTPUT: -1 if heap does not exist, heap is empty, or "top" argument is NULL
            0 otherwise
*/
int     heap_replace    (heap_t H, int priority, void* data, void** top);

/*
    This function does not accept a NULL data pointer since the entire
    purpose is to check the data at the top. This function does not modify the
    heap in any way.

    INPUT:  Pointer to heap, double pointer to be assigned to data at top
    OUTPUT: -1 if heap does not exist, heap is empty, or if data is NULL
            0 otherwise
*/
int     heap_peek       (heap_t H, void** data);

/*
    Returns the number of nodes presently in the heap. Note that this is not
    equivalent to the memory used by the heap as it is not a static array.

    INPUT:  Pointer to heap
    OUTPUT: -1 if heap does not exist
            Count of nodes otherwise
*/
int     heap_count      (heap_t H);

/*
    Indicates whether the heap contains any elements.

    INPUT:  Pointer to heap
    OUTPUT: 0 if heap does not exist or has data
            1 otherwise
*/
int     heap_is_empty   (heap_t H);

/*
    Prints the priorities in level order.

    INPUT:  Pointer to heap
    OUTPUT: Level order representation of the heap
*/
void    heap_print      (heap_t H);

#endif
