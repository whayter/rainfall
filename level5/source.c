#include <stdlib.h>
#include <stdio.h>

void o()
{
    system("/bin/sh");              // o +  6 - o + 13
    _exit(1);                       // o + 18 - o + 25
}

void n()
{
    char buf[512];                  // from -0x208(%ebp) to 0x8(%esp)
    
    fgets(buf, 512, stdin);         // n +  9 - n + 35
    printf(buf);                    // n + 40 - n + 49
    exit(1);                        // n + 54 - n + 61
}

int main(void)
{
    n();                            // main +  6
    return (0);                     // main + 11 - main + 12
}