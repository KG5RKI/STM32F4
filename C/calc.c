#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    float a = atof(argv[1]);
    char op = *argv[2];
    float b = atof(argv[3]);
    
    switch(op) {
        case '+': printf("%f\n", (a+b)); break;
        case '-': printf("%f\n", (a-b)); break;
        case 'x': printf("%f\n", (a*b)); break;
        case '/': printf("%f\n", (a/b)); break;
        default: printf("Invalid operator\n");
    }
    return 0;
}
