#ifndef STACK_H
#define STACK_H

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef struct Stack* stack_t;

stack_t stack_create    (void);
int     stack_destroy   (stack_t S);
int     stack_push      (stack_t S, void* data);
int     stack_pop       (stack_t S, void** return_data);
int     stack_count     (stack_t S);
int     stack_is_empty  (stack_t S);

#endif
