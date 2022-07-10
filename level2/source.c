#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void p(void)
{
    unsigned int retaddr;
    char buf[76];

    fflush(stdout);
    gets(buf);
    retaddr = __builtin_return_address(0);
    if ((retaddr & 0xb0000000) == 0xb0000000)
    {
        printf("(%p)\n", retaddr);
        exit(1);
    }
    puts(buf);
    strdup(buf);
    return ; 
}

int main(void)
{
    p();
    return (0);
}