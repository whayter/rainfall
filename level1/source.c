#include <stdlib.h>
#include <stdio.h>

int run()
{
    fwrite("Good... Wait what?\n", 19, 1, stdout);      //  run +  6 -  run + 41
	return (system("/bin/sh"));                         //  run + 46 -  run + 59
}

int main(void)
{
    char buf[64];                                       // main +  9 (0x50 - 0x10 = 64)

    gets(buf);                                          // main + 13 - main + 16
    return (0);                                         // main + 21 - main + 22
}