#include <stdlib.h>
#include <stdio.h>

void o()
{
    system("/bin/sh");
    _exit(1);
}

void n()
{
    char buf[520];
    
    fgets(buf, 512, stdin);
    printf(buf);
    exit(1);
}

int main(void)
{
    n();
    return (0);
}