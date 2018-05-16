#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int prod = 0;
    
    while (b > 0) {
        prod += a;
        --b;
    }
    printf("Product: %d\n", prod);
    return 0;
}
