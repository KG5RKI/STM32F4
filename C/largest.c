#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int c = atoi(argv[3]);
    
    char largest = a>b ? ( a>c ? 'a':'c' ) : ( b>c ? 'b':'c' );
    printf("Largest: %c\n", largest);
    return 0;
}
