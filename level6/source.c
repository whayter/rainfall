#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void m(void)
{
    puts("Nope");
    return ;
}

void n(void)
{
    system("/bin/cat /home/user/level7/.pass");
    return ;
}

int main(int ac, char **av)
{
    char *param;
    void (*function)(void);

    param = (char *)malloc(64);
    function = (void *)malloc(4);

    function = (void *)m;

    strcpy(param, av[1]);
    (**function)();
    return (0);
}