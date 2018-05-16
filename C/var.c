#include <stdio.h>
#include "vardata.h"
#include "vardata.c"

extern void fun2(void);
extern int extvar;

int glob = 1;

void fun(void);

int main(int argc, char *argv[]) {
    printf("Global : %d\n", glob);
    fun();
    printf("External Variable : %d\n", extvar);
    fun2();
    return 0;
}

void fun(void) {
    static int loc = 1;
    printf("Static Var : %d\n", loc);
    loc++;
    printf("Static Var++ : %d\n", loc);
}
