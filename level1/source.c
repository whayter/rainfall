#include <stdlib.h>
#include <stdio.h>

int run()
{
    fwrite("Good... Wait what?\n", 19, 1, stdout);
	return (system("/bin/sh"));
}

int main(void)
{
    char buf[76];

    gets(buf);
    return (0);
}