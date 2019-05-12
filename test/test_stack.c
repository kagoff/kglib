#include <assert.h>

#include "stack.h"

void test_stack(void) {
    /***************************************************************************
     * Exercise all APIs correctly
     **************************************************************************/
    int* top = NULL;
    int a = 1;
    kgstack_t S = stack_create();
    assert(S);
    assert(!stack_push(S, &a));
    assert(!stack_top(S, (void*)&top));
    assert(*top == a);
    top = NULL;
    assert(stack_count(S) == 1);
    assert(!stack_pop(S, (void*)&top));
    assert(*top == a);
    top = NULL;
    assert(stack_count(S) == 0);
    assert(!stack_destroy(&S));
}