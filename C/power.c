#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    int x = atoi(argv[1]);
    int n = atoi(argv[2]);
    printf("%d^%d: %f\n", x, n, pow(x, n));
    return 0;
}
