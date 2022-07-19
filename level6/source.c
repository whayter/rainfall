#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void m(void)
{
    puts("Nope");                                   // m +  6 - m + 13
    return ;                                        // m + 18 - m + 19
}

void n(void)
{
    system("/bin/cat /home/user/level7/.pass");     // n +  6 - n + 13
    return ;                                        // n + 18 - n + 19
}

int main(int ac, char **av)
{
    char *param;
    void (*function)(void);

    param = (char *)malloc(64);                     // main +  9 - main + 21
    function = (void *)malloc(4);                   // main + 25 - main + 37

    function = (void *)m;                           // main + 41 - main + 50

    strcpy(param, av[1]);                           // main + 52 - main + 73
    (**function)();                                 // majn + 78 - main + 84
    return (0);                                     // main + 86 - main + 87
}