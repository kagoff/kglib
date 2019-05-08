

int queue_test()
{
    queue_t Q = queue_create();

    int* front;
    int a = 1;
    assert(!queue_enqueue(Q, &a));
    assert(!queue_dequeue(Q, (void*)&front));
    assert(*front == a);
    assert(queue_count(Q) == 0);

    int b = 2;
    int c = 3;
    assert(!queue_enqueue(Q, &a));
    assert(!queue_enqueue(Q, &b));
    assert(!queue_enqueue(Q, &c));

    assert(queue_count(Q) == 3);
    assert(!queue_dequeue(Q, (void*)&front));
    assert(*front == a);
    assert(queue_count(Q) == 2);
    assert(!queue_dequeue(Q, (void*)&front));
    assert(*front == b);
    assert(!queue_dequeue(Q, (void*)&front));
    assert(*front == c);
    assert(queue_count(Q) == 0);

    assert(!queue_enqueue(Q, &c));
    assert(!queue_dequeue(Q, NULL));
    assert(queue_dequeue(Q, NULL));
    assert(!queue_enqueue(Q, &c));
    assert(queue_dequeue(NULL, (void*)&front));
    assert(queue_dequeue(Q, (void*)&front));
    assert(queue_count(Q) == 0);

    assert(!queue_destroy(Q));
    return 0;
}