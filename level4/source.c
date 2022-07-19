#include <stdlib.h>
#include <stdio.h>

int m;                                                  // 0x8049810

void p(char* param)
{
    printf(param_1);                                    // p +  6 - p + 12
    return ;                                            // p + 17 - p + 18
}

void n()
{
    char buf[512];                                      // from -0x208(%ebp) to 0x8(%esp)
    
    fgets(buf, 512, stdin);                             // n +  9 - n + 35
    p(buf);                                             // n + 40 - n + 49
    if (m == 16930116)                                  // n + 54 - n + 64
        system("/bin/cat /home/user/level5/.pass");     // n + 66 - n + 73
    return ;                                            // n + 78 - n + 79
}

int main(void)
{
    n();                                                // main +  6
    return (0);                                         // main + 11 - main + 12
}