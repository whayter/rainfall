#include <stdlib.h>
#include <stdio.h>

char *auth = NULL;
char *service = NULL;

int main(void)
{
	char buf[128];

	while (1)											// main+16 - main+451
	{
		printf("%p, %p \n", auth, service);				// main+17 - main+45

		if (!fgets(buf, 128, stdin))					// main+50 - main+81
			break ;

		if (strncmp(buf, "auth ", 5) == 0)				// main+87 - main+126
		{
			auth = (char *)malloc(4);					// main+128 - main+140

			memset(auth, 0, strlen(auth));				// main+145 - main+150
			if (strlen(buf + 5) <= 30)					// main+156 - main+196
				strcpy(auth, buf + 5);					// main+198 - main+217
		}

		if (strncmp(buf, "reset", 5) == 0)				// main+222 - main+261
			free(auth);									// main+263 - main+271

		if (strncmp(buf, "service", 6) == 0)			// main+276 - main+315
			service = strdup(buf + 7);					// main+317 - main+332

		if (strncmp(buf, "login", 5) == 0)				// main+337 - main+376
		{
			if (auth + 32 != 0)							// main+382 - main+392
				system("/bin/sh");						// main+394 - main+406
			else
				fwrite("Password:\n", 10, 1, stdout);	// main+ 411 - main+451
		}
	}
	return (0);											// main+462 - main+468
}