#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    if (n%2==0) {
        printf("Even\n");
    }
    else {
        printf("Odd\n");
    }
    return 0;
}
