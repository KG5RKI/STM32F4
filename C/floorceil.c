#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    float x = atof(argv[1]);
    printf("floor(%f): %f\n", x, floor(x));
    printf("ceil(%f) : %f\n", x, ceil(x));
    return 0;
}
