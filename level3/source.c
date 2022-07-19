#include <stdlib.h>
#include <stdio.h>

int m;                                              // 0x0804988c

void v(void)
{
    char buf[512];                                  // from -0x208(%ebp) to 0x8(%esp)

    fgets(buf, 512, stdin);                         // v +   9 - v +  35
    printf(buf);                                    // v +  40 - v +  49
    if (m == 64)                                    // v +  54 - v +  62
    {
        fwrite("Wait what?!\n", 12, 1, stdout);     // v +  64 - v +  99
        system("/bin/sh");                          // v + 104 - v + 111
    }
    return;                                         // v + 116 - v + 117
}

int main(void)
{
    v();                                            // main +  6
    return (0);                                     // main + 11 - main + 12
}