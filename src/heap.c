#include"heap.h"

#define INITIAL_HEAP_SIZE 64

//******************************************************************************
//      STRUCTS
//******************************************************************************
typedef struct Node* node_t;
struct Node {
    int priority;
    void* data;
};

struct Heap {
    int count;
    int size;
    enum Type type;
    node_t nodes;
};

//******************************************************************************
//      PRIVATE FUNCTIONS
//******************************************************************************
// For build-heap
void heapify (heap_t H, int index)
{
    int left_index = ((index<<1)|0x1);
    int right_index = ((index<<1)+2);
    node_t current = H->nodes+index;
    node_t left = H->nodes+left_index;
    node_t right = H->nodes+right_index;
    struct Node temp;

    if(H->type == MAXHEAP)
    {
        if(left->priority > current->priority)
        {
            temp = *current;
            *current = *left;
            *left = temp;
        }
        if(right->priority > current->priority)
        {
            temp = *current;
            *current = *right;
            *right = temp;
        }
    }
    else //MINHEAP
    {
        if(left->priority < current->priority)
        {
            temp = *current;
            *current = *left;
            *left = temp;
        }
        if(right->priority < current->priority)
        {
            temp = *current;
            *current = *right;
            *right = temp;
        }
    }
}
// For insertions
void sift_up (heap_t H)
{
    int index = heap_count(H) - 1;
    if(index < 1)
        return;

    struct Node temp;
    node_t new, parent;

    if(H->type == MAXHEAP)
    {
        while(index > 0)
        {
            new = H->nodes+index;
            parent = H->nodes+((index-1)>>1);

            if( parent->priority < new->priority)
            {
                temp = *new;
                *new = *parent;
                *parent = temp;
            }
            else
                return;

            index = (index-1)>>1;
        }
    }

    else //MINHEAP
    {
        while(index > 0)
        {
            new = H->nodes+index;
            parent = H->nodes+((index-1)>>1);

            if( parent->priority > new->priority)
            {
                temp = *new;
                *new = *parent;
                *parent = temp;
            }
            else
                return;

            index = (index-1)>>1;
        }
    }
}

// For deletions
void sift_down (heap_t H)
{
    if(heap_count(H) < 2)
        return;

    int index = 0;
    int count = heap_count(H);

    struct Node temp;
    node_t new, left, right;
    int left_index, right_index;

    if(H->type == MAXHEAP)
    {
        while(index < count)
        {
            new = H->nodes+index;
            left_index = ((index<<1)|0x1);
            right_index = ((index<<1)+2);
            left = H->nodes+left_index;
            right = H->nodes+right_index;

            if( (right_index < count) && (new->priority < right->priority)
                && right->priority >= left->priority)
            {
                temp = *new;
                *new = *right;
                *right = temp;
                index = (index<<1)+2;
            }
            else if( (left_index < count) && (new->priority < left->priority) )
            {
                temp = *new;
                *new = *left;
                *left = temp;
                index = (index<<1)|0x1;
            }
            else
                return;
        }
    }
    else //MINHEAP
    {
        while(index < count)
        {
            new = H->nodes+index;
            left_index = ((index<<1)|0x1);
            right_index = ((index<<1)+2);
            left = H->nodes+left_index;
            right = H->nodes+right_index;

            if( (right_index < count) && (new->priority >= right->priority)
                && right->priority <= left->priority)
            {
                temp = *new;
                *new = *right;
                *right = temp;
                index = (index<<1)+2;
            }
            else if( (left_index < count) && (new->priority > left->priority) )
            {
                temp = *new;
                *new = *left;
                *left = temp;
                index = (index<<1)|0x1;
            }
            else
                return;
        }
    }
}

//******************************************************************************
//      PUBLIC FUNCTIONS
//******************************************************************************
heap_t heap_create (enum Type t)
{
    heap_t H = (heap_t)malloc(sizeof(struct Heap));
    H->count = 0;
    H->size = INITIAL_HEAP_SIZE;
    H->type = t;
    H->nodes = (node_t)malloc(INITIAL_HEAP_SIZE*sizeof(struct Node));
    return H;
}

heap_t heap_build (enum Type t, int* priorities, void** data, int count)
{
    if(count < 1 || !priorities || !data)
        return NULL;

    heap_t H = heap_create(t);

    if(count > H->size)
    {
        H->size = count+1;
        if(H->size < 1)
        {
            free(H->nodes);
            free(H);
            return NULL; //overflow
        }
        H->nodes = (node_t)realloc(H->nodes, H->size*sizeof(struct Node));
    }

    int i;
    for(i = 0; i < count; i++)
    {
        struct Node N = {priorities[i], data[i]};
        H->nodes[H->count++] = N;
    }

    for(i = (count-1)/2; i > -1; i--)
    {
        heapify(H, i);
    }

    return H;
}

int heap_destroy (heap_t H)
{
    if(!H)
        return -1;

    free(H->nodes);
    free(H);
    return 0;
}

int heap_push (heap_t H, int priority, void* data)
{
    if(!H)
        return -1;

    if(H->count + 1 == H->size)
    {
        H->size = H->size * 2;
        if(H->size < 0)
            return -2; //overflow
        H->nodes = (node_t)realloc(H->nodes, H->size*sizeof(struct Node));
    }

    struct Node N = {priority, data};
    H->nodes[H->count++] = N;
    sift_up(H);

    return 0;
}

int heap_pop (heap_t H, void** data)
{
    if( !H || (H->count == 0) )
        return -1;

    if(data)
        *data = H->nodes[0].data;

    H->nodes[0] = H->nodes[--H->count];
    sift_down(H);

    return 0;
}

int heap_replace (heap_t H, int priority, void* data, void** top)
{
    if(!H || (H->count == 0) || !top)
        return -1;

    *top = H->nodes[0].data;

    struct Node N = {priority, data};
    H->nodes[0] = N;
    sift_down(H);

    return 0;
}

int heap_peek (heap_t H, void** data)
{
    if(!H || (H->count == 0) || !data)
        return -1;

    *data = H->nodes[0].data;

    return 0;
}

int heap_count (heap_t H)
{
    if(!H)
        return -1;

    return H->count;
}

int heap_is_empty (heap_t H)
{
    if(!H)
        return 0;

    return  ((H->count == 0) ? 1 : 0);
}

void heap_print (heap_t H)
{
    if(!H)
        return;

    int i;
    for(i = 0; i < H->count; i++)
    {
        printf("%d ", H->nodes[i].priority);
    }
    printf("\n");
}
