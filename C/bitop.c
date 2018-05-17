#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int getBitCount(int);
int getBinary(int);

int main(int argc, char *argv[]) {
//     int a = atoi(argv[1]);
//     int b = atoi(argv[2]);
    
//     printf("%d OR %d: %d\n", a, b, (a | b));
//     
//     for (int i = 11; i<=16; i++) {
//         printf("%d has %d bits\n", i, getBitCount(i));
//     }
    
    /* Convert to binary */
    for (int i = 0; i <= 15; i++) {
        printf("%x in binary is %d\n", i, getBinary(i));
    }
    return 0;
}

int getBitCount(int n) {
    int count;
    if (n==0) return 0;
    else {
        for (count = 0; n > 0; ++count, n = n>>1) {};
        return count;
    }
}

int getBinary(int n) {
    int bin = 0;
    for (int i = pow(2, getBitCount(n)); i>0; i = i>>1) {
        if ((n & i) == i) bin = (bin * 10) + 1;
        else bin = (bin * 10) + 0;
    }
    return bin;
}
