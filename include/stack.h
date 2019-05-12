#ifndef STACK_H
#define STACK_H

#include<stdlib.h>

typedef struct Stack* kgstack_t;

/**
 *  Allocates a stack object and returns pointer to it.
 *
 *  INPUT:  None
 *  OUTPUT: Pointer to the allocated stack object data
 */
kgstack_t stack_create    (void);

/**
 *  Frees a stack object and sets the stack data to NULL when complete. This
 *  does not free the actual data stored in the stack, so be careful not to
 *  lose memory here.
 *
 *  INPUT:  Pointer to stack object data pointer to free and reset to NULL
 *  OUTPUT: 0 on success
 *.         -1 on NULL arguments
 */
int     stack_destroy   (kgstack_t* S);

/**
 *  Push a data object onto the top of the stack.
 *
 *  INPUT:  Stack object pointer
 *          Data to enqueue
 *  OUTPUT: 0 on success
 *          -1 on NULL arguments
 */
int     stack_push      (kgstack_t S, void* data);

/**
 *  Peek at the top element of the stack, but do not pop it off.
 *
 *  INPUT:  Stack object pointer
 *          Address of data object pointer to return on
 *  OUTPUT: 0 on success
 *          -1 on NULL arguments
 */
int     stack_top       (kgstack_t S, void** return_data);

/**
 *  Remove and return the top element of the stack. When return_data is NULL,
 *  still pops the front element. Careful not to lose memory here!
 *
 *  INPUT:  Stack object pointer
 *          Address of data object pointer to return on
 *  OUTPUT: 0 on success
 *          -1 on NULL stack
 */
int     stack_pop       (kgstack_t S, void** return_data);

/**
 *  Get the number of elements currently in the stack.
 *
 *  INPUT:  Queue object pointer
 *  OUTPUT: Elements of stack on success
 *          -1 on NULL pointer
 */
int     stack_count     (kgstack_t S);

#endif
