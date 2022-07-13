#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

char c[68];

struct s
{
    int n;
    char *s;
};

void m(void)
{
    time_t t;

    time(&t);
    printf("%s - %d\n", c, t);
    return ;
}

int main(int ac, char **av)
{
    struct s *a, *b;
    FILE *f;

    a = (struct s *)malloc(8);
    a->n = 1;
    a->s = (char *)malloc(8);

    b = (struct s *)malloc(8);
    b->n = 2;
    b->s = (char *)malloc(8);

    strcpy(a->s, av[1]);
    strcpy(b->s, av[2]);

    f = fopen("/home/user/level8/.pass", "r");
    fgets(c, 68, f);
    printf("~~\n");

    return (0);
}