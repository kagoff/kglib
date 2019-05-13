#include <stdio.h>

extern void test_queue(void);
extern void test_stack(void);
extern void test_hash(void);

int main() {
    test_queue();
    test_stack();
    test_hash();

    fprintf(stderr, "KGLIB TEST: SUCCESS\n");
    return 0;
}