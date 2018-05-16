#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    float p = atof(argv[1]);
    float r = atof(argv[2]);
    float t = atof(argv[3]);
    float si = (p*r*t)/100;
    printf("Simple Interest: %f\n", si);
    return 0;
}
