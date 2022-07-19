#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void p(void)
{
    unsigned int retaddr;
    char buf[64];                                   // 64 is the space between -0x4c(%ebp) and -0xc(%ebp)

    fflush(stdout);                                 // p +   6 - p +  14
    gets(buf);                                      // p +  19 - p +  25
    retaddr = __builtin_return_address(0);          // p +  30 - p +  33
    if ((retaddr & 0xb0000000) == 0xb0000000)       // p +  36 - p +  49
    {
        printf("(%p)\n", retaddr);                  // p +  51 - p +  66
        exit(1);                                    // p +  71 - p +  78
    }
    puts(buf);                                      // p +  83 - p +  89
    strdup(buf);                                    // p +  94 - p + 100
    return ;                                        // p + 105 - p + 106
}

int main(void)
{
    p();                                            // main +  6
    return (0);                                     // main + 11 - main + 12
}