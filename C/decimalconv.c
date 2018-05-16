#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    
    printf("Octal %o\n", n);
    printf("Hexadecimal %x\n", n);
    return 0;
}
