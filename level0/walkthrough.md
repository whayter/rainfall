## Context

The goal of this project is to get the content, for each level, of the .pass file that is in the current directory of the upper level. We are currently at level0, so we want to get the content of the file /home/user/level1/.pass:
```
level0@RainFall:~$ cat /home/user/level1/.pass
cat: /home/user/level1/.pass: Permission denied
```
Of course, that whould be too easy.

There is an executable file named level0:
```
level0@RainFall:~$ ./level0 
Segmentation fault (core dumped)
level0@RainFall:~$ ./level0 param
No !
```

## Lead

Using gdb, we can see that the program makes a call to atoi() and then compares the resulting value with 423 (0x1a7):
```
0x08048ed4 <+20>:    call   0x8049710 <atoi>
0x08048ed9 <+25>:    cmp    $0x1a7,%eax
```

Later in the program, a call to execv with the command `/bin/sh` opens a shell after having defined the uid and the gid with setresgid() and setresuid().

## exploit

```
level0@RainFall:~$ ./level0 423
$ whoami
level1
$ cat /home/user/level1/.pass
1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
```

We can now reach the next level with the command `su level1` and fill in the flag found as a password.