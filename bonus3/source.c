#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int ac, char** av)
{
	FILE* f;
	char buf[132];								// 0xc9 - 0x18

	f = fopen("/home/user/end/.pass", "r");		// main+14 - main+36
	bzero(buf, 132);							// main+36 - main+61
	if (!f || ac != 2)							// main+63 - main+84
		return (-1);
	fread(buf, 66, 1, f);						// main+89 - main+123
	buf[65] = 0;								// main+128
	buf[atoi(av[1])] = 0;						// main+133 - main+149
	fread(buf + 66, 41, 1, f);					// main+154 - main+191
	fclose(f);									// main+196 - main+206
	if (strcmp(buf, av[1]) == 0)				// main+211 - main+237
		execl("/bin/sh", "sh", 0);				// main+239 - main+262
	else
		puts(buf + 66);							// main+269 - main+279
    return (0);									// main+284 - main+295
}