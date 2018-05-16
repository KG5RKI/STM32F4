#include <stdio.h>
#include <stdlib.h>
#include "binary.c"

extern int getBitCount(int);
extern int getBinary(int);

int main(int argc, char *argv[]) {
    float n = atof(argv[1]);
    float k = n;
    int rev = 0;
    while (n > 0) {
        if (n / 2 == (int)n >> 1)
            rev = rev * 10 + 0;
        else
            rev = rev * 10 + 1;
        n = (int)n >> 1;
    }
    printf("Original bits: %d\n", getBinary((int)k));
    printf("Reversed bits: %d\n", rev);
    return 0;
}
