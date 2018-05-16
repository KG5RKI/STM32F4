#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int sum = a+b;
    float average = (float)sum/2;
    printf("Sum: %d\n", sum);
    printf("Average: %f\n", average);
    return 0;
}
