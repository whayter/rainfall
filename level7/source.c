#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

char c[68];                                         // 0x8049960

struct s
{
    int n;
    char *s;
};

void m(void)
{
    time_t t;

    time(&t);                                       // m +  6 - m + 13
    printf("%s - %d\n", c, t);                      // m + 18 - m + 38
    return ;                                        // m + 43 - m + 44
}

int main(int ac, char **av)
{
    struct s *a, *b;
    FILE *f;

    a = (struct s *)malloc(8);                      // main +   9 - main +  21
    a->n = 1;                                       // main +  25 - main +  29
    a->s = (char *)malloc(8);                       // main +  35 - main +  53

    b = (struct s *)malloc(8);                      // main +  56 - main +  68
    b->n = 2;                                       // main +  72 - main +  76
    b->s = (char *)malloc(8);                       // main +  82 - main + 100

    strcpy(a->s, av[1]);                            // main + 103 - main + 127
    strcpy(b->s, av[2]);                            // main + 132 - main + 156

    f = fopen("/home/user/level8/.pass", "r");      // main + 161 - main + 178
    fgets(c, 68, f);                                // main + 183 - main + 202
    printf("~~\n");                                 // main + 207 - main + 214

    return (0);                                     // main + 219 - main + 225
}