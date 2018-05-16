#include <stdio.h>
#include <stdlib.h>

struct data {
//     int a;
//     int b;
    char d;
    long c;
};

union data2 {
    int a;
    int b;
    int c;
    char d;
};

int main(void) {
    printf("sizeof(int) is: %ld\n", sizeof(int));
    printf("sizeof(short int) is: %ld\n", sizeof(short int));
    printf("sizeof(long int) is: %ld\n", sizeof(long int));
    printf("sizeof(long long int) is: %ld\n", sizeof(long long int));
    
    printf("sizeof(float) is: %ld\n", sizeof(float));
    printf("sizeof(double) is: %ld\n", sizeof(double));
    
    printf("sizeof(char) is: %ld\n", sizeof(char));
    
    printf("sizeof(struct - long + char) is: %ld\n", sizeof(struct data));
    printf("sizeof(union - 3xint + char) is: %ld\n", sizeof(union data2));
    return 0;
}
