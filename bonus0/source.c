#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* p(char* s1, char* s2)			// 0x080484b4
{
	char buf[4096];					// p+20

	puts(s2);						// p+9 - p+15
	read(0, buf, 4096);				// p+20 - p+45
	*strchr(buf, '\n') = 0;			// p+50 - p+72
	return (strncpy(s1, buf, 20));	// p+75 - p+105
}

char* pp(char* buf)					// 0x0804851e
{
	char s1[20];
	char s2[20];
	int len;

    p(s1, " - ");					// pp+8 - pp+22
	p(s2, " - ");					// pp+27 - pp+41

	strcpy(buf, s1);				// pp+46 - pp+59

	len = 0;						// ---
	while (buf[len] != '\0')		//    |
		len++;						//	  |-- pp+64 - pp+106
	buf[len] = ' ';					//	  |
	buf[len + 1] = '\0';			// ---

	return (strcat(buf, s2));		// pp+109 - pp+133
}

int main(void)
{
    char buf[42];					// 0x40 - 0x16

    pp(buf);						// main+9 - main+16
    puts(buf);						// main+21 - main+28
    return (0);						// main+33 - main+39
}