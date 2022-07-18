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

		if (strncmp(buf, "auth ", 5) == 0)				// main+87 - main+217
		{
			auth = (char *)malloc(4);
			memset(auth, 0, strlen(auth));
			if (strlen(buf + 5) <= 30)
				strcpy(auth, buf + 5);
		}

		if (strncmp(buf, "reset", 5) == 0)				// main+222 - main+271
			free(auth);

		if (strncmp(buf, "service", 6) == 0)			// main+276 - main+332
			service = strdup(buf + 7);

		if (strncmp(buf, "login", 5) == 0)				// main+337 - main+446
		{
			if (auth + 32 != 0)
				system("/bin/sh");
			else
				fwrite("Password:\n", 10, 1, stdout);
		}
	}
	return (0);
}