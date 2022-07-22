#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int language;

void greetuser(char* usr)
{
	char buf[72];

	if (language == 1)														// greetuser+6 - greetuser+14
		strcpy(buf, "Hyv\303\244\303\244 p\303\244iv\303\244\303\244 ");	// greetuser+54 - greetuser+99
	else if (language == 2)													// greetuser+16 - greetuser+19
		strcpy(buf, "Goedemiddag! ");										// greetuser+101 - greetuser+129
	else if (language == 0)													// greetuser+21 - greetuser+23
		strcpy(buf, "Hello ");												// greetuser+25 - greetuser+52
	strcat(buf, usr);														// greetuser+134 - greetuser+147
	puts(buf);																// greetuser+152 - greetuser+158
	return ;																// greetuser+164
}

int main(int ac, char** av)
{
   char buf[72];
   char* lang;

	if (ac != 3)								// main+15 - main+19
		return (1);								// main+21 - main+26 && main+263 - main+270
	bzero(buf, 13);								// main+31 - main+49
	strncpy(buf, av[1], 40);					// main+51 - main+78
	strncpy(buf + 40, av[2], 32);				// main+83 - main+113
	lang = getenv("LANG");						// main+118 - main+130
	if (lang != NULL)							// main+137 - main+145
	{
		if (memcmp(lang, "fi", 2) == 0)			// main+147 - main+180
			language = 1;						// main+182 - main+192
		else if (memcmp(lang, "nl", 2) == 0)	// main+194 - main+227
			language = 2;						// main+229
	}
	greetuser(buf);								// main+239 - main+258
    return (0);									// main+263 - main+270
}