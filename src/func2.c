#include <stdio.h>

extern void foo(int x);

// Some data and bss data
char* func2_string = "func2 called\n";
int func2_values[10];

void func2(void)
{
    printf("%s\n", func2_string);
    foo(func2_values[9]);
}
