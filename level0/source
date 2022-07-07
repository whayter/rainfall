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
	
	n = atoi(av[1]);
	if (n != 423)
		fwrite("No !\n", 5, 1, stderr);
	else
	{
		cmds[0] = strdup("/bin/sh");
		cmds[1] = NULL;
		gid = getegid();
		uid = geteuid();
		setresgid(gid, gid, gid);
		setresuid(uid, uid, uid);
		execv("/bin/sh", cmds);
	}
    return (0);
}