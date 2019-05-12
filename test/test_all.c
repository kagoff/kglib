#include <stdio.h>

extern void test_queue(void);
extern void test_stack(void);

int main() {
    test_queue();
    test_stack();

    fprintf(stderr, "KGLIB TEST: SUCCESS\n");
    return 0;
}