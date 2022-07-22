#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int ac, char** av)
{
    int n;
	char buf[40];

	n = atoi(av[1]);				// main+9 - main+20
	if (n > 9)						// main+25 - main+34
		return(1);					// main+36 - main+41 && main+127 - main+128
	memcpy(buf, av[2], n * 4);		// main+43 - main+79
	if (n == 0x574f4c46)			// main+84 - main+92
		execl("/bin/sh", "sh", 0);	// main+94 - main+117
    return (0);						// main+127 - main+128
}