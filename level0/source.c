#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define _GNU_SOURCE

int main(int ac, char **av)
{
    int		n;
	char	*cmds[2];
	gid_t	gid;
	uid_t	uid;
	
	n = atoi(av[1]);							// main +   9 - main +  20
	if (n != 423)								// main +  25 - main +  30
		fwrite("No !\n", 5, 1, stderr);			// main + 152 - main + 187
	else										// main + 150
	{
		cmds[0] = strdup("/bin/sh");			// main +  32 - main +  44
		cmds[1] = NULL;							// main +  48  
		gid = getegid();						// main +  56 - main +  61
		uid = geteuid();						// main +  65 - main +  70
		setresgid(gid, gid, gid);				// main +  74 - main +  97
		setresuid(uid, uid, uid);				// main + 102 - main + 125
		execv("/bin/sh", cmds);					// main + 130 - main + 145
	}
    return (0);									// main + 192 - main + 198
}